/*
 * File: z_jumptoggle_platform.c
 * Overlay: ovl_Jumptoggle_Platform
 * Description: A platform that toggles every time the player leaves the ground, from the Hylian Modding actor pack.
 */

#include "jumptoggle_platform.h"
#include "assets_hm_pack/objects/object_jumptoggle_platform/object_jumptoggle_platform.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void JumptogglePlatform_Init(Actor* thisx, PlayState* play);
void JumptogglePlatform_Destroy(Actor* thisx, PlayState* play);
void JumptogglePlatform_Update(Actor* thisx, PlayState* play);
void JumptogglePlatform_Draw(Actor* thisx, PlayState* play);

void JumptogglePlatform_RotateToTarget(JumptogglePlatform* this, PlayState* play);

void JumptogglePlatform_CheckForJump(JumptogglePlatform* this, PlayState* play);
void JumptogglePlatform_Border(JumptogglePlatform* this, PlayState* play);

const ActorInit Jumptoggle_Platform_InitVars = {
    ACTOR_JUMPTOGGLE_PLATFORM,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_JUMPTOGGLE_PLATFORM,
    sizeof(JumptogglePlatform),
    (ActorFunc)JumptogglePlatform_Init,
    (ActorFunc)JumptogglePlatform_Destroy,
    (ActorFunc)JumptogglePlatform_Update,
    (ActorFunc)JumptogglePlatform_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static f32 sSfxVol = 0.5f;

void JumptogglePlatform_Observer_Update(Actor* thisx, PlayState* play) {
}


void JumptogglePlatform_Init(Actor* thisx, PlayState* play) {
    JumptogglePlatform* this = (JumptogglePlatform*)thisx;
    CollisionHeader* colHeader = NULL;
    Actor_ProcessInitChain(thisx, sInitChain);

    // start assuming player is in the air since the toggle happens when
    // leaving the ground - prevents instantly toggling when the player is
    // entering the room in the water or falling etc
    this->prevPlayerOnGround = false;
    
    if (GET_JUMPTOGGLE_TYPE(this) == JUMPTOGGLE_TYPE_BORDER) {
        this->actionFunc = JumptogglePlatform_Border;
        return;
    }

    CollisionHeader_GetVirtual(&gJumpTogglePlatformCol_collisionHeader, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);


    Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, ACTOR_JUMPTOGGLE_PLATFORM,
        this->dyna.actor.home.pos.x, this->dyna.actor.home.pos.y, this->dyna.actor.home.pos.z,
        this->dyna.actor.home.rot.x, this->dyna.actor.home.rot.y, this->dyna.actor.home.rot.z,
        JUMPTOGGLE_TYPE_BORDER
    );

    if (GET_JUMPTOGGLE_TYPE(this) == JUMPTOGGLE_TYPE_START_RED) {
        this->currentRot = this->targetRot = this->dyna.actor.home.rot.z;
    } else {
        this->currentRot = this->targetRot = this->dyna.actor.home.rot.z + 0x7FFF;
    }

    this->actionFunc = JumptogglePlatform_RotateToTarget;
}

void JumptogglePlatform_Destroy(Actor* thisx, PlayState* play) {
    JumptogglePlatform* this = (JumptogglePlatform*)thisx;

    if (GET_JUMPTOGGLE_TYPE(this) != JUMPTOGGLE_TYPE_BORDER) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

void JumptogglePlatform_Update(Actor* thisx, PlayState* play) {
    JumptogglePlatform* this = (JumptogglePlatform*)thisx;

    this->actionFunc(this, play);
}

void JumptogglePlatform_Draw(Actor* thisx, PlayState* play) {
    JumptogglePlatform* this = (JumptogglePlatform*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    if (GET_JUMPTOGGLE_TYPE(this) == JUMPTOGGLE_TYPE_BORDER) {
        if (this->currentRot == this->dyna.actor.home.rot.z) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 68, 69, 255);
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 85, 92, 255, 255);
        }

        gSPSegment(POLY_XLU_DISP++, 0x08, Gfx_TexScroll(play->state.gfxCtx, play->gameplayFrames % 128, 0, 32, 64));
        Gfx_DrawDListXlu(play, gJumpToggleBorderDL);
    } else {
        Gfx_DrawDListOpa(play, gJumpTogglePlatformDL);
    }

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}

void JumptogglePlatform_RotateToTarget(JumptogglePlatform* this, PlayState* play) {
    JumptogglePlatform_CheckForJump(this, play);

    bool equalBeforeStep = this->currentRot == this->targetRot;
    Math_ApproachS(&this->currentRot, this->targetRot, 1, 0x800);
    bool equalAfterStep  = this->currentRot == this->targetRot;

    if (!equalBeforeStep && equalAfterStep) {
        if (Actor_WorldDistXYZToActor(&this->dyna.actor, &GET_PLAYER(play)->actor) < 1000.0f) {
            Audio_PlaySfxGeneral(NA_SE_EV_BLOCK_BOUND, &this->dyna.actor.projectedPos, 4,
                &gSfxDefaultFreqAndVolScale, &sSfxVol, &gSfxDefaultReverb);
        }
    }

    this->dyna.actor.world.rot.z = this->dyna.actor.shape.rot.z = this->currentRot;
}

void JumptogglePlatform_CheckForJump(JumptogglePlatform* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    bool playerOnGround = player->actor.bgCheckFlags & BGCHECKFLAG_GROUND;

    if ((this->prevPlayerOnGround) && (!playerOnGround)) {
        if (this->targetRot == this->dyna.actor.home.rot.z) {
            this->targetRot += 0x7FFF;
        } else {
            this->targetRot = this->dyna.actor.home.rot.z;
        }
        
        if (Actor_WorldDistXYZToActor(&this->dyna.actor, &GET_PLAYER(play)->actor) < 1000.0f) {
            Audio_PlaySfxGeneral(NA_SE_EV_BOMB_BOUND, &this->dyna.actor.projectedPos, 4,
                &gSfxDefaultFreqAndVolScale, &sSfxVol, &gSfxDefaultReverb);
        }
    }

    this->prevPlayerOnGround = playerOnGround;
}

void JumptogglePlatform_Border(JumptogglePlatform* this, PlayState* play) {
    JumptogglePlatform* parent = (JumptogglePlatform*)this->dyna.actor.parent;
    if (parent != NULL) {
        this->currentRot = parent->targetRot;
    }
}
