/*
 * File: z_floor_spikes.c
 * Overlay: ovl_Floor_Spikes
 * Description: Retractable floor spikes by hiisuya, from the Hylian Modding actor pack.
 */

#include "floor_spikes.h"
#include "assets_hm_pack/objects/object_floor_spikes/object_floor_spikes.h"

#define SPIKE_TYPE(this)    ((this->dyna.actor.params >> 0xC) & 0xF) // 0xF000
#define SPIKE_SIZE(this)    ((this->dyna.actor.params >> 0x8) & 0xF) // 0x0F00
#define SWITCH_FLAG(this)   (this->dyna.actor.params & 0x3F) // 0x00FF
#define USE_SWITCH(this)    (this->dyna.actor.home.rot.x)
#define USE_VOID(this)      (this->dyna.actor.home.rot.z)

/**
 * Params:
 *  0xF000 = Type
 *     0x0 = Player Triggered
 *     0x1 = Cyclic
 *     0x2 = Start On
 *     0x3 = Start Off
 *  
 *  0x0F00 = Size
 *     0x0 = Small
 *     0x1 = Medium
 *     0x2 = Large
 * 
 *  0x00FF = Switch Flag
 * 
 *  Rot X > 0 = React to Switch Flags
 *  Rot Z > 0 = Void out on touch
 * 
 *  Ex: 0x3104, rot.x = 1, rot.z = 0 | Medium sized spikes that start turned off. Will switch states when flag (0x4) is set/unset. Will not Void.
 *  Ex: 0x1200, rot.x = 0, rot.z = 1 | Large spikes that go up and down cyclicly. Will not react to switch flags. Will Void on touch.
 * 
 *  Notes:
 *      The types "Switch Start On/Off" will ALWAYS react to switch flags. They will override if you say not to.
 *      There is an ON and OFF state which is controlled by Switch Flags for every type. If you don't allow Switch Flag reaction, then the state is always ON.
 *      All types will maintain their ON/OFF position based on their parameters (and switch status) on room reload.
 *          Aka: If a Cyclic Spike that reacts to Switch Flag has that flag set, it will retract and be turned OFF. It will then remain OFF until that flag is unset.
 *      If you need to change timings, use the defines labeled below, though the results may not be perfect.
*/

#define SPIKE_RETRACT_TIME 7
#define SPIKE_WAIT_TIME 20

#define FLAGS (ACTOR_FLAG_4)

void FloorSpikes_Init(Actor* thisx, PlayState* play);
void FloorSpikes_Destroy(Actor* thisx, PlayState* play);
void FloorSpikes_Update(Actor* thisx, PlayState* play);
void FloorSpikes_Draw(Actor* thisx, PlayState* play);

void FloorSpikes_UpdateRetracted(Actor* thisx, PlayState* play);

void FloorSpikes_SetupWaitForTrigger(FloorSpikes* this, PlayState* play);
void FloorSpikes_WaitForTrigger(FloorSpikes* this, PlayState* play);
void FloorSpikes_SetupTrigger(FloorSpikes* this, PlayState* play);
void FloorSpikes_Trigger(FloorSpikes* this, PlayState* play);
void FloorSpikes_SetupReturnToWait(FloorSpikes* this, PlayState* play);
void FloorSpikes_ReturnToWait(FloorSpikes* this, PlayState* play);

void FloorSpikes_SetupRunCyclic(FloorSpikes* this, PlayState* play);
void FloorSpikes_RunCyclic(FloorSpikes* this, PlayState* play);

void FloorSpikes_SetupWaitForSwitch(FloorSpikes* this, PlayState* play);
void FloorSpikes_WaitForSwitchOn(FloorSpikes* this, PlayState* play);
void FloorSpikes_WaitForSwitchOff(FloorSpikes* this, PlayState* play);

void FloorSpikes_SetupExtend(FloorSpikes* this, PlayState* play);
void FloorSpikes_Extend(FloorSpikes* this, PlayState* play);
void FloorSpikes_SetupRetract(FloorSpikes* this, PlayState* play);
void FloorSpikes_Retract(FloorSpikes* this, PlayState* play);

void FloorSpikes_DoNothing(FloorSpikes* this, PlayState* play);

typedef enum {
    SPIKE_TYPE_PLAYER_TRIGGERED = 0,
    SPIKE_TYPE_CYCLIC,
    SPIKE_TYPE_SWITCH_START_ON,
    SPIKE_TYPE_SWITCH_START_OFF,
} FloorSpikesType;
typedef enum {
    SPIKE_SIZE_SMALL = 0,
    SPIKE_SIZE_MEDIUM,
    SPIKE_SIZE_LARGE,
} FloorSpikesSize;

typedef enum {
    CYCLIC_GO_DOWN = 0,
    CYCLIC_WAIT_DOWN,
    CYCLIC_GO_UP,
    CYCLIC_WAIT_UP
} FloorSpikesCyclicState;

const ActorInit Floor_Spikes_InitVars = {
    ACTOR_FLOOR_SPIKES,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FLOOR_SPIKES,
    sizeof(FloorSpikes),
    (ActorFunc)FloorSpikes_Init,
    (ActorFunc)FloorSpikes_Destroy,
    (ActorFunc)FloorSpikes_Update,
    (ActorFunc)FloorSpikes_Draw,
};

static ColliderQuadInit sDmgPlayerQuadInit = {
    .base = {
        .colType = COLTYPE_NONE,
        .atFlags = AT_ON | AT_TYPE_ENEMY,
        .shape = COLSHAPE_QUAD,
    },
    .info = {
        .toucher = { .dmgFlags = DMG_UNBLOCKABLE, .damage = 16 },
        .toucherFlags = TOUCH_ON,
    }
};

static ColliderQuadInit sDmgOthersQuadInit = {
    .base = {
        .colType = COLTYPE_NONE,
        .atFlags = AT_ON | AT_TYPE_PLAYER | AT_TYPE_OTHER,
        .shape = COLSHAPE_QUAD,
    },
    .info = {
        .toucher = { .dmgFlags = DMG_SLASH_MASTER, .damage = 16 },
        .toucherFlags = TOUCH_ON,
    }
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

void FloorSpikes_Init(Actor* thisx, PlayState* play) {
    FloorSpikes* this = (FloorSpikes*)thisx;
    CollisionHeader* colHeader = NULL;

    u8 flagActive = Flags_GetSwitch(play, SWITCH_FLAG(this));

    Actor_ProcessInitChain(thisx, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);

    this->useSwitchFlag = !!USE_SWITCH(this);
    this->useVoidOut = !!USE_VOID(this);
    this->spikeProgress = 0.0f;
    this->spikesActive = false; // always start spikes off no matter what

    this->dyna.actor.shape.rot.x = this->dyna.actor.home.rot.x = 0.0f;
    this->dyna.actor.shape.rot.z = this->dyna.actor.home.rot.z = 0.0f;

    switch (SPIKE_SIZE(this)) {
        case SPIKE_SIZE_SMALL:
            CollisionHeader_GetVirtual(&gSpikePadSmallCol_collisionHeader, &colHeader);
            break;
        case SPIKE_SIZE_MEDIUM:
            CollisionHeader_GetVirtual(&gSpikePadMediumCol_collisionHeader, &colHeader);
            break;
        case SPIKE_SIZE_LARGE:
            CollisionHeader_GetVirtual(&gSpikePadLargeCol_collisionHeader, &colHeader);
            break;
    }
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    Collider_InitQuad(play, &this->playerCollider);
    Collider_InitQuad(play, &this->othersCollider);
    Collider_SetQuad(play, &this->playerCollider, &this->dyna.actor, &sDmgPlayerQuadInit);
    Collider_SetQuad(play, &this->othersCollider, &this->dyna.actor, &sDmgOthersQuadInit);

    switch (SPIKE_TYPE(this)) {
        case SPIKE_TYPE_PLAYER_TRIGGERED:
            FloorSpikes_SetupWaitForTrigger(this, play);
            break;
        case SPIKE_TYPE_CYCLIC:
            FloorSpikes_SetupRunCyclic(this, play);
            break;
        case SPIKE_TYPE_SWITCH_START_ON: // Set their states for the appropriate spot based on type and switch flag activation.
            if (flagActive) { 
                this->spikeProgress = 0.0f;
                this->spikesActive = false;
            } else {
                this->spikeProgress = 1.0f;
                this->spikesActive = true;
            }
            this->useSwitchFlag = true;
            FloorSpikes_SetupWaitForSwitch(this, play);
            break;
        case SPIKE_TYPE_SWITCH_START_OFF:
            if (flagActive) {
                this->spikeProgress = 1.0f;
                this->spikesActive = true;
            } else {
                this->spikeProgress = 0.0f;
                this->spikesActive = false;
            }
            this->useSwitchFlag = true;
            FloorSpikes_SetupWaitForSwitch(this, play);
            break;
    }

    Actor_SetScale(&this->dyna.actor, 0.01f);
}

void FloorSpikes_Destroy(Actor* thisx, PlayState* play) {
    FloorSpikes* this = (FloorSpikes*)thisx;

    Collider_DestroyQuad(play, &this->playerCollider);
    Collider_DestroyQuad(play, &this->othersCollider);
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void FloorSpikes_Update(Actor* thisx, PlayState* play) {
    FloorSpikes* this = (FloorSpikes*)thisx;
    Player* player = GET_PLAYER(play);

    if (this->playerCollider.base.atFlags & AT_HIT) {
        this->playerCollider.base.atFlags &= ~AT_HIT;

        if ((this->useVoidOut) && (this->playerCollider.base.at->id == ACTOR_PLAYER)) {
            player->actor.freezeTimer = 50;
            play->damagePlayer(play, -16);
            Play_TriggerRespawn(play);
            gSaveContext.respawnFlag = -2;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM_MAIN, 0);
            play->transitionType = TRANS_TYPE_FADE_BLACK;
            Sfx_PlaySfxCentered2(NA_SE_OC_ABYSS);
        }
    }

    this->actionFunc(this, play);

    if ((this->useSwitchFlag) && (SPIKE_TYPE(this) <= SPIKE_TYPE_CYCLIC)) {
        if (Flags_GetSwitch(play, SWITCH_FLAG(this))) {
            if (this->spikesActive) {
                this->timer = SPIKE_RETRACT_TIME;
                this->actionFunc = FloorSpikes_Retract;
                this->dyna.actor.update = FloorSpikes_UpdateRetracted;
            } else if (!this->spikesActive) {
                this->actionFunc = FloorSpikes_DoNothing;
                this->dyna.actor.update = FloorSpikes_UpdateRetracted;
            }
        }
    }

    if ((this->spikesActive) && (this->spikeProgress > 0.5f)) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->othersCollider.base);
        if (player->actor.freezeTimer == 0) {
            if (player->invincibilityTimer == 0) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->playerCollider.base);
            }

            if (DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
                player->speedXZ = CLAMP_MAX(player->speedXZ, 3.0f);
            }
        }
    }
}

void FloorSpikes_UpdateRetracted(Actor* thisx, PlayState* play) {
    FloorSpikes* this = (FloorSpikes*)thisx;

    if (!Flags_GetSwitch(play, SWITCH_FLAG(this))) {
        switch (SPIKE_TYPE(this)) {
            case SPIKE_TYPE_PLAYER_TRIGGERED:
                FloorSpikes_SetupWaitForTrigger(this, play);
                break;
            case SPIKE_TYPE_CYCLIC:
                FloorSpikes_SetupRunCyclic(this, play);
                
                break;
        }
        this->dyna.actor.update = FloorSpikes_Update;
    }

    this->actionFunc(this, play);
}

static Gfx* sBaseDLists[3] = { gSpikePadSmallDL, gSpikePadMediumDL, gSpikePadLargeDL };
static Gfx* sSpikesDLists[3] = { gSpikesSmallDL, gSpikesMediumDL, gSpikesLargeDL };

                                    //small                               medium                       large
static Vec3f sQuad1Pos[3] = { { 4000.0f,  3200.0f, 4000.0f  },  { 8000.0f, 3200.0f,  8000.0f  }, { 16000.0f, 3200.0f, 16000.0f    } };
static Vec3f sQuad2Pos[3] = { { -4000.0f, 3200.0f, 4000.0f  },  { -8000.0f, 3200.0f, 8000.0f  }, { -16000.0f, 3200.0f, 16000.0f   } };
static Vec3f sQuad3Pos[3] = { { -4000.0f, 3200.0f, -4000.0f },  { -8000.0f, 3200.0f, -8000.0f }, { -16000.0f, 3200.0f, -16000.0f  } };
static Vec3f sQuad4Pos[3] = { { 4000.0f,  3200.0f, -4000.0f },  { 8000.0f,  3200.0f, -8000.0f }, { 16000.0f, 3200.0f, -16000.0f   } };

void FloorSpikes_Draw(Actor* thisx, PlayState* play) {
    FloorSpikes* this = (FloorSpikes*)thisx;
    static Vec3f sZeroVec = { 0.0f, 0.0f, 0.0f };

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_DrawDListOpa(play, sBaseDLists[SPIKE_SIZE(this)]);

    if (this->spikesActive) {
        Matrix_Push();

        Matrix_MultVec3f(&sQuad1Pos[SPIKE_SIZE(this)], &this->playerCollider.dim.quad[0]);
        Matrix_MultVec3f(&sQuad2Pos[SPIKE_SIZE(this)], &this->playerCollider.dim.quad[1]);
        Matrix_MultVec3f(&sQuad3Pos[SPIKE_SIZE(this)], &this->playerCollider.dim.quad[3]);
        Matrix_MultVec3f(&sQuad4Pos[SPIKE_SIZE(this)], &this->playerCollider.dim.quad[2]);
        Collider_SetQuadVertices(&this->playerCollider, &this->playerCollider.dim.quad[0], &this->playerCollider.dim.quad[1],
                                  &this->playerCollider.dim.quad[2], &this->playerCollider.dim.quad[3]);
        Collider_SetQuadVertices(&this->othersCollider, &this->playerCollider.dim.quad[0], &this->playerCollider.dim.quad[1],
                                  &this->playerCollider.dim.quad[2], &this->playerCollider.dim.quad[3]);

        Matrix_Scale(1.0f, this->spikeProgress, 1.0f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        Gfx_DrawDListOpa(play, sSpikesDLists[SPIKE_SIZE(this)]);
        Matrix_Pop();
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void FloorSpikes_SetupWaitForTrigger(FloorSpikes* this, PlayState* play) {
    this->spikesActive = false;
    this->spikeProgress = 0.0f;
    this->timer = 5;
    this->actionFunc = FloorSpikes_WaitForTrigger;
}

void FloorSpikes_WaitForTrigger(FloorSpikes* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        if (DynaPolyActor_IsPlayerOnTop(&this->dyna) || DynaPolyActor_IsActorOnTop(&this->dyna)) {
            FloorSpikes_SetupTrigger(this, play);
        }
    }
}

void FloorSpikes_SetupTrigger(FloorSpikes* this, PlayState* play) {
    this->timer = SPIKE_WAIT_TIME;
    this->spikesActive = true;
    this->actionFunc = FloorSpikes_Trigger;
}

void FloorSpikes_Trigger(FloorSpikes* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        this->spikeProgress = 1.0f;
        FloorSpikes_SetupReturnToWait(this, play);
    } else {
        if (this->timer <= SPIKE_RETRACT_TIME) {
            Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
            this->spikeProgress = CLAMP_MAX(this->spikeProgress + 0.65f, 1.0f);
        } else {
            this->spikeProgress = 0.3f;
        }
    }
}

void FloorSpikes_SetupReturnToWait(FloorSpikes* this, PlayState* play) {
    this->timer = SPIKE_WAIT_TIME;
    this->actionFunc = FloorSpikes_ReturnToWait;
}

void FloorSpikes_ReturnToWait(FloorSpikes* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        this->spikesActive = false;
        this->spikeProgress = 0.0f;
        FloorSpikes_SetupWaitForTrigger(this, play);
    } else {
        if (this->timer <= SPIKE_RETRACT_TIME) {
            Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
            this->spikeProgress = CLAMP_MIN(this->spikeProgress - 0.55f, 0.0f);
        }
    }
}

void FloorSpikes_SetupRunCyclic(FloorSpikes* this, PlayState* play) {
    this->timer = SPIKE_WAIT_TIME;
    this->spikesActive = false;
    this->spikeProgress = 0.0f;
    this->cyclicState = CYCLIC_WAIT_DOWN;
    this->actionFunc = FloorSpikes_RunCyclic;
}

void FloorSpikes_RunCyclic(FloorSpikes* this, PlayState* play) {

    if (DECR(this->timer) == 0) {
        switch (this->cyclicState) {
            case CYCLIC_WAIT_DOWN:
                this->timer = SPIKE_RETRACT_TIME;
                this->cyclicState = CYCLIC_GO_UP;
                break;
            case CYCLIC_GO_UP:
                this->timer = SPIKE_WAIT_TIME;
                this->cyclicState = CYCLIC_WAIT_UP;
                break;
            case CYCLIC_WAIT_UP:
                this->timer = SPIKE_RETRACT_TIME;
                this->cyclicState = CYCLIC_GO_DOWN;
                break;
            case CYCLIC_GO_DOWN:
                this->spikesActive = false;
                this->timer = SPIKE_WAIT_TIME;
                this->cyclicState = CYCLIC_WAIT_DOWN;
                break;
        }
    } else {
        switch (this->cyclicState) {
            case CYCLIC_WAIT_DOWN:
                if (this->timer <= SPIKE_RETRACT_TIME) {
                    this->spikesActive = true;
                    this->spikeProgress = 0.3f;
                } else {
                    this->spikeProgress = 0.0f;
                }
                break;
            case CYCLIC_WAIT_UP:
                this->spikeProgress = 1.0f;
                break;
            case CYCLIC_GO_DOWN:
                Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
                this->spikeProgress = CLAMP_MIN(this->spikeProgress - 0.55f, 0.0f);
                break;
            case CYCLIC_GO_UP:
                Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
                this->spikeProgress = CLAMP_MAX(this->spikeProgress + 0.65f, 1.0f);
                break;
        }
    }
}


void FloorSpikes_SetupWaitForSwitch(FloorSpikes* this, PlayState* play) {
    if (Flags_GetSwitch(play, SWITCH_FLAG(this))) {
        this->actionFunc = FloorSpikes_WaitForSwitchOn;
    } else {
        this->actionFunc = FloorSpikes_WaitForSwitchOff;
    }
}

void FloorSpikes_WaitForSwitchOn(FloorSpikes* this, PlayState* play) {
    if (!Flags_GetSwitch(play, SWITCH_FLAG(this))) {
        if (this->spikesActive) {
            FloorSpikes_SetupRetract(this, play);
        } else {
            FloorSpikes_SetupExtend(this, play);
        }
    }
}

void FloorSpikes_WaitForSwitchOff(FloorSpikes* this, PlayState* play) {
    if (Flags_GetSwitch(play, SWITCH_FLAG(this))) {
        if (this->spikesActive) {
            FloorSpikes_SetupRetract(this, play);
        } else {
            FloorSpikes_SetupExtend(this, play);
        }
    }
}

void FloorSpikes_SetupExtend(FloorSpikes* this, PlayState* play) {
    this->timer = SPIKE_RETRACT_TIME;
    this->spikesActive = true;
    this->actionFunc = FloorSpikes_Extend;
}

void FloorSpikes_Extend(FloorSpikes* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        this->spikeProgress = 1.0f;

        if (SPIKE_TYPE(this) <= SPIKE_TYPE_CYCLIC) {
            this->actionFunc = FloorSpikes_DoNothing;
        } else {
            FloorSpikes_SetupWaitForSwitch(this, play);
        }
    } else {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
        this->spikeProgress = CLAMP_MIN(this->spikeProgress - 0.55f, 0.0f);
    }
}

void FloorSpikes_SetupRetract(FloorSpikes* this, PlayState* play) {
    this->timer = SPIKE_RETRACT_TIME;
    this->actionFunc = FloorSpikes_Retract;
}

void FloorSpikes_Retract(FloorSpikes* this, PlayState* play) {

    if (DECR(this->timer) == 0) {
        this->spikesActive = false;
        this->spikeProgress = 0.0f;

        if (SPIKE_TYPE(this) <= SPIKE_TYPE_CYCLIC) {
            this->dyna.actor.update = FloorSpikes_UpdateRetracted;
            this->actionFunc = FloorSpikes_DoNothing;
        } else {
            FloorSpikes_SetupWaitForSwitch(this, play);
        }
    } else {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_IT_SWORD_PICKOUT - SFX_FLAG);
        this->spikeProgress = CLAMP_MIN(this->spikeProgress - 0.55f, 0.0f);
    }
}

void FloorSpikes_DoNothing(FloorSpikes* this, PlayState* play) {

}
