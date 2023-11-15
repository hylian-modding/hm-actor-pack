/*
 * File: z_Obj_Fan.c
 * Overlay: ovl_Obj_Fan
 * Description: Spinning fan actor that can push the player and bombs, from the Hylian Modding actor pack.
 * Params: XXYY
 *      -- XX: Scale multiplier in 0.1f increments, 0 = 1.0f scale, 1 = 1.1f scale, etc.
 *          -- 1.0f scale has a 114 unit push radius
 *          -- Scale also affects how far the fan's push reaches
 *      -- YY: Switch flag
 *          -- A flag of 0xFF (-1) will make the fan always on
 */

#include "z_obj_fan.h"
#include "assets_hm_pack/objects/object_fan/object_fan.h"
#include "assets_hm_pack/objects/object_fan/gWindDL.h"

#define FLAGS ACTOR_FLAG_4 | ACTOR_FLAG_5
#define FAN_REACH 500.0f
#define FAN_RADIUS 114.0f
#define FAN_POWER 20.0f
#define FAN_THRESHOLD 0.5f

void ObjFan_Init(Actor* thisx, PlayState* play);
void ObjFan_Destroy(Actor* thisx, PlayState* play);
void ObjFan_Update(Actor* thisx, PlayState* play);
void ObjFan_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Fan_InitVars = {
    ACTOR_OBJ_FAN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FAN,
    sizeof(ObjFan),
    (ActorFunc)ObjFan_Init,
    (ActorFunc)ObjFan_Destroy,
    (ActorFunc)ObjFan_Update,
    (ActorFunc)ObjFan_Draw,
};

void ObjFan_Init(Actor* thisx, PlayState* play) {
    ObjFan* this = (ObjFan*)thisx;
    this->scale = 1.0f + (((((u16)thisx->params) >> 8) & 0xFF) * 0.1f);
    this->flag = (((u16)thisx->params) & 0xFF);

    if (this->flag == -1 || Flags_GetSwitch(play, this->flag & 0x3F)) {
        this->power = FAN_POWER;
    }
}

void ObjFan_Destroy(Actor* thisx, PlayState* play) {
    
}

void ObjFan_SetRelativePos(Actor* target, ObjFan* this) {
    MtxF rotationMatrix;
    Vec3f temp;

    Math_Vec3f_Diff(&target->world.pos, &this->actor.world.pos, &temp);
    SkinMatrix_SetRotateZYX(&rotationMatrix, -this->actor.world.rot.x, -this->actor.world.rot.y, -this->actor.world.rot.z);
    SkinMatrix_Vec3fMtxFMultXYZ(&rotationMatrix, &temp, &this->relativeActorPos);
}

u8 ObjFan_ActorInRange(Actor* target, ObjFan* this) {
    f32 dist;
    f32 reach = (FAN_REACH * (this->power / FAN_POWER)) * this->scale;

    ObjFan_SetRelativePos(target, this);

    if (this->relativeActorPos.z < 0 || this->relativeActorPos.z > reach) {
        return 0;
    }

    dist = sqrtf(SQ(this->relativeActorPos.x) + SQ(this->relativeActorPos.y)); // target dist from intercept

    if (dist > (FAN_RADIUS * this->scale)) {
        return 0;
    }

    return 1;
}

void ObjFan_PushPlayer(Player* player, ObjFan* this, f32 distRatio, PlayState* play) {
    // Scale down power based on distance
    // XZ power is scaled up slightly to make Y power relatively weaker, helps accentuate effect of gravity
    f32 powerXZ = Math_CosS(this->actor.shape.rot.x) * this->power * distRatio * 1.25f;
    f32 powerY = -Math_SinS(this->actor.shape.rot.x) * this->power * distRatio;

    player->pushedYaw = this->actor.shape.rot.y;
    player->pushedSpeed = powerXZ;
    if (powerY > 0 || powerY <= player->actor.minVelocityY) {
        player->actor.velocity.y = powerY + (3.0f * Math_SinS(play->gameplayFrames * DEG_TO_BINANG(22.5f)));
    }
}


void ObjFan_PushActor(Actor* actor, ObjFan* this, PlayState* play) {
    f32 dist = sqrtf(SQ(this->relativeActorPos.x) + SQ(this->relativeActorPos.y) + SQ(this->relativeActorPos.z));
    f32 maxDist = FAN_REACH * this->scale;
    f32 scaledThreshold = maxDist * FAN_THRESHOLD;
    f32 distRatio;

    // Calculate the distance ratio based on the threshold
    if (dist <= scaledThreshold) {
        distRatio = 1.0f; // Full power within the threshold
    } else if (dist > scaledThreshold && dist < maxDist) {
        distRatio = 1.0f - ((dist - scaledThreshold) / (maxDist - scaledThreshold));
    } else {
        distRatio = 0.0f; // No power beyond max distance
    }

    if (actor->id == ACTOR_PLAYER) {
        ObjFan_PushPlayer((Player*)actor, this, distRatio, play);
        return;
    }

    // XZ power is scaled up slightly to make Y power relatively weaker, helps accentuate effect of gravity
    f32 powerXZ = Math_CosS(this->actor.shape.rot.x) * this->power * distRatio * 1.25;
    f32 powerY = -Math_SinS(this->actor.shape.rot.x) * this->power * distRatio;
    
    if (powerXZ > 0) {
        actor->speed = powerXZ;
        actor->world.rot.y = this->actor.shape.rot.y;
    }
    if (powerY > 0 || powerY <= actor->minVelocityY) {
        actor->velocity.y = powerY + (3.0f * Math_SinS(play->gameplayFrames * DEG_TO_BINANG(22.5f)));
    }
}

void ObjFan_Update(Actor* thisx, PlayState* play) {
    ObjFan* this = (ObjFan*)thisx;
    Actor* actor = &GET_PLAYER(play)->actor;
    Actor* explosive;

    if (this->power != 0) {
        if (ObjFan_ActorInRange(actor, this)) {
            ObjFan_PushActor(actor, this, play);
        }

        explosive = play->actorCtx.actorLists[ACTORCAT_EXPLOSIVE].head;
        while (explosive != NULL) {
            if (ObjFan_ActorInRange(explosive, this)) {
                ObjFan_PushActor(explosive, this, play);
            }
            explosive = explosive->next;
        }

        Actor_PlaySfx(&this->actor, NA_SE_EV_WIND_TRAP - SFX_FLAG);
    }

    if (this->flag == -1 || Flags_GetSwitch(play, this->flag & 0x3F)) {
        Math_SmoothStepToF(&this->power, FAN_POWER, 1.0f, 0.5f, 0.0f);
    } else {
        Math_SmoothStepToF(&this->power, 0.0f, 1.0f, 0.5f, 0.0f);
    }

    this->propellerRot += DEG_TO_BINANG((this->power / FAN_POWER) * 45.0f);
}

void ObjFan_Draw(Actor* thisx, PlayState* play) {
    ObjFan* this = (ObjFan*)thisx;
    MtxF curMatrix;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Matrix_Scale(this->scale, this->scale, this->scale, MTXMODE_APPLY);

    Matrix_Get(&curMatrix);
    Matrix_RotateZYX(0, 0, this->propellerRot, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, gFanDL);

    Matrix_Put(&curMatrix);

    Matrix_Scale(1.0f, 1.0f, 1.2f * this->power, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, 0, (play->gameplayFrames * 10) % 128, 64, 16,
                                1, 0, (play->gameplayFrames * 5) % 128, 64, 64));

    gSPDisplayList(POLY_XLU_DISP++, gWindDL);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}





