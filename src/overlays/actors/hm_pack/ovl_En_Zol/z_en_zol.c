/*
 * File: z_en_zol.c
 * Overlay: ovl_En_Zol
 * Description: Zol enemy from the Hylian Modding actor pack.
 *  * Params: XXYY
 *      -- XX: Spawn appearance - 0x00 None, 0x01 Floor, 0x02 Ceiling
 *      -- YY: Type - 0x00 Green, 0x01 Red
 */

#define ENZOL_SPAWN ((this->actor.params & 0xFF00) >> 8)
#define ENZOL_TYPE (this->actor.params & 0xFF)

#include "z_en_zol.h"
#include "assets_hm_pack/objects/object_zol/object_zol.h"
#include "overlays/effects/ovl_Effect_Ss_Dead_Sound/z_eff_ss_dead_sound.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4)

void EnZol_Init(Actor* thisx, PlayState* play);
void EnZol_Destroy(Actor* thisx, PlayState* play);
void EnZol_Update(Actor* thisx, PlayState* play);
void EnZol_Draw(Actor* thisx, PlayState* play);

void EnZol_SetupWaitForPlayer(EnZol* this);
void EnZol_SetupWaitForPlayerCeiling(EnZol* this);
void EnZol_SetupGrow(EnZol* this);
void EnZol_SetupEmerge(EnZol* this);
void EnZol_SetupIdle(EnZol* this);
void EnZol_SetupTurnTowardPlayer(EnZol* this);
void EnZol_SetupJumpTowardPlayer(EnZol* this);
void EnZol_SetupRecoil(EnZol* this);
void EnZol_SetupFrozen(EnZol* this);
void EnZol_SetupDeathCry(EnZol* this);

void EnZol_WaitForPlayer(EnZol* this, PlayState* play);
void EnZol_WaitForPlayerCeiling(EnZol* this, PlayState* play);
void EnZol_Grow(EnZol* this, PlayState* play);
void EnZol_Idle(EnZol* this, PlayState* play);
void EnZol_TurnTowardPlayer(EnZol* this, PlayState* play);
void EnZol_JumpTowardPlayer(EnZol* this, PlayState* play);
void EnZol_Recoil(EnZol* this, PlayState* play);
void EnZol_Frozen(EnZol* this, PlayState* play);
void EnZol_DeathCry(EnZol* this, PlayState* play);

typedef enum {
    ZOL_IDLE,
    ZOL_AIR,
    ZOL_LANDED,
    ZOL_EMERGE,
    ZOL_WAIT,
    ZOL_FROZEN,
    ZOL_DEATH
} EnZolState;

const ActorInit En_Zol_InitVars = {
    ACTOR_EN_ZOL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_ZOL,
    sizeof(EnZol),
    (ActorFunc)EnZol_Init,
    (ActorFunc)EnZol_Destroy,
    (ActorFunc)EnZol_Update,
    (ActorFunc)EnZol_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
            { 0xFFCFFFFE, 0x00, 0x08 },
            { 0xFFCFFFFE, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 54, 60, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ ZOL_DMGEFF_DEFAULT,
    /* 0xF */ ZOL_DMGEFF_ICE = 0xF
} ZolDamageEffect;

static DamageTable sDamageTable[] = {
    /* Deku nut      */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Deku stick    */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Slingshot     */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Explosive     */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Boomerang     */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Normal arrow  */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Hammer swing  */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Hookshot      */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Kokiri sword  */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Master sword  */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Giant's Knife */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Fire arrow    */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Ice arrow     */ DMG_ENTRY(4, ZOL_DMGEFF_ICE),
    /* Light arrow   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Unk arrow 1   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Unk arrow 2   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Unk arrow 3   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Fire magic    */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Ice magic     */ DMG_ENTRY(3, ZOL_DMGEFF_ICE),
    /* Light magic   */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Shield        */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Mirror Ray    */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Kokiri spin   */ DMG_ENTRY(1, ZOL_DMGEFF_DEFAULT),
    /* Giant spin    */ DMG_ENTRY(4, ZOL_DMGEFF_DEFAULT),
    /* Master spin   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Kokiri jump   */ DMG_ENTRY(2, ZOL_DMGEFF_DEFAULT),
    /* Giant jump    */ DMG_ENTRY(8, ZOL_DMGEFF_DEFAULT),
    /* Master jump   */ DMG_ENTRY(4, ZOL_DMGEFF_DEFAULT),
    /* Unknown 1     */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Unblockable   */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
    /* Hammer jump   */ DMG_ENTRY(4, ZOL_DMGEFF_DEFAULT),
    /* Unknown 2     */ DMG_ENTRY(0, ZOL_DMGEFF_DEFAULT),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, -40, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

// sine func for decreasing wobble effect
void EnZol_Wobble(EnZol* this) {
    Math_SmoothStepToF(&this->wobbleScale, 0.0f, 0.04f, 0.05f, 0.0f);
    this->actor.scale.x = this->actor.scale.z = (sinf((f32)this->wobbletimerMax * (M_PI / 4)) * this->wobbleScale) + this->wobbleScale + this->scale;
}

// changes scaling during different states for zol deformation
void EnZol_Scale(EnZol* this) {
    if (this->state == ZOL_LANDED) {
        if (this->timer2 > 0) {
            this->timer2--;
        } else {
            this->timer2 = 5;
            this->state = ZOL_IDLE;
        }
    }

    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actionFunc == EnZol_JumpTowardPlayer || this->actionFunc ==  EnZol_Recoil)) {
        this->state = ZOL_AIR;
    }

    switch (this->state) {
        case ZOL_EMERGE:
            Math_SmoothStepToF(&this->actor.scale.x, 0.02f, 0.1f, 0.2f, 0.0f);
            Math_SmoothStepToF(&this->actor.scale.y, 0.2f, 0.1f, 0.2f, 0.0f);
            this->actor.scale.z = this->actor.scale.x;
        break;
        case ZOL_IDLE:
            Math_SmoothStepToF(&this->actor.scale.y, this->scale, 0.5f, 0.2f, 0.0f);
        break;
        case ZOL_AIR:
            Math_SmoothStepToF(&this->actor.scale.x, 0.02f, 0.1f, 0.1f, 0.0f);
            Math_SmoothStepToF(&this->actor.scale.y, 0.2f, 0.1f, 0.1f, 0.0f);
            this->actor.scale.z = this->actor.scale.x;
        break;
        case ZOL_LANDED:
            Math_SmoothStepToF(&this->actor.scale.y, 0.01f, 0.6f, 0.5f, 0.0f);
        break;
    }
}

void EnZol_Init(Actor* thisx, PlayState* play) {
    EnZol* this = (EnZol*)thisx;

    Actor_ProcessInitChain(thisx, sInitChain);
    if (this->actor.params == ZOL_SPLIT) {
        this->scale = 0.04f;
    } else {
        this->scale = 0.08f;
    }
    Actor_SetScale(thisx, this->scale);
    ActorShape_Init(&thisx->shape, -200.0f, ActorShadow_DrawCircle, 8.0f);
    this->wobbleScale = 0.0f;
    this->timer2 = 5;
    this->timer = 0;

    thisx->focus.pos = thisx->world.pos;
    thisx->focus.pos.y += 20.0f;
    thisx->targetMode = 3;
    
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    thisx->colChkInfo.damageTable = sDamageTable;
    thisx->colChkInfo.health = 2;
    thisx->colChkInfo.mass = MASS_HEAVY;
    this->bgcheckinfo = UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2;

    switch (ENZOL_TYPE) {
        case ZOL_GREEN:
        break;
        case ZOL_RED:
            this->collider.base.colType = COLTYPE_HIT7; // red blood hit effect
        break;
        case ZOL_SPLIT:
            this->collider.base.colType = COLTYPE_HIT7; // red blood hit effect
            this->collider.dim.radius = 26;
            this->collider.dim.height = 35;
            this->actor.shape.rot.y += 0x4000; 
            EnZol_SetupRecoil(this);
        break;
    }

    if (ENZOL_TYPE != ZOL_SPLIT) {
        switch (ENZOL_SPAWN) {
            case ZOL_NONE:
                EnZol_SetupIdle(this);
                break;
            case ZOL_FLOOR:
                this->scale = 0.0f;
                this->actor.scale.x = this->actor.scale.z  = 0.0f;
                this->actor.scale.y = 0.01f;

                this->actor.flags &= ~ACTOR_FLAG_0; // navi target disabled
                EnZol_SetupWaitForPlayer(this);
                break;
            case ZOL_CEILING:
                this->scale = 0.0f;
                Actor_SetScale(thisx, this->scale);
                EnZol_SetupWaitForPlayerCeiling(this);
                break;
        }    
    }
    
}

void EnZol_Destroy(Actor* thisx, PlayState* play) {
    EnZol* this = (EnZol*)thisx;

    Collider_DestroyCylinder(play, &this->collider);
}

// setups and action funcs
// zol is invisible and waiting for player to come closer
void EnZol_SetupWaitForPlayer(EnZol* this) {
    this->state = ZOL_WAIT;
    this->actionFunc = EnZol_WaitForPlayer;
}

void EnZol_WaitForPlayer(EnZol* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 250.0f) && (this->actor.yDistToPlayer <= 80.0f)) {
        this->wobbletimerMax = 120;
        this->wobbleScale = 0.03f;
        EnZol_SetupGrow(this);
    } 
}

// zol is invisible and waiting for player to come closer
void EnZol_SetupWaitForPlayerCeiling(EnZol* this) {
    this->state = ZOL_WAIT;
    this->actor.gravity = 0.0f;
    this->actionFunc = EnZol_WaitForPlayerCeiling;
}

void EnZol_WaitForPlayerCeiling(EnZol* this, PlayState* play) {
    if ((this->actor.xzDistToPlayer < 250.0f)) {
        this->scale = 0.08f;
        // Actor_SetScale(&this->actor, this->scale);
        EnZol_SetupIdle(this);
    } 
}

// zol appears
void EnZol_SetupGrow(EnZol* this) {
    this->timer = 18;
    this->actor.flags |= ACTOR_FLAG_0; // targetable
    this->actionFunc = EnZol_Grow;
}

void EnZol_Grow(EnZol* this, PlayState* play) {
    Sfx_PlaySfxAtPos(&this->actor.world.pos, NA_SE_EN_MOFER_CORE_ROLL - SFX_FLAG); // play sound continuously, every frame
    Math_SmoothStepToF(&this->scale, 0.08f, 0.1f, 0.4f, 0.0f);
    if (this->timer < 10) {
        Math_SmoothStepToF(&this->actor.scale.y, 0.08, 0.1f, 0.2f, 0.0f);
    }
    if (this->timer > 0) {
        this->timer--;
    } else {
        EnZol_SetupEmerge(this);
    }
}

// zol jumps after appearing
void EnZol_SetupEmerge(EnZol* this) {
    this->actor.velocity.y = 12.0f;
    this->actor.gravity = -1.0f;
    this->timer = 30;
    Actor_PlaySfx(&this->actor, NA_SE_EN_AWA_BOUND);
    this->actionFunc = EnZol_JumpTowardPlayer;
}

// zol idle
void EnZol_SetupIdle(EnZol* this) {
    this->actor.speed = 0.0f;
    this->timer = Rand_S16Offset(10, 25); // base, range
    this->actionFunc = EnZol_Idle;
}

void EnZol_Idle(EnZol* this, PlayState* play) {
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 0.5f, 0.0f);

    this->actor.gravity = -1.0f;

    if ((this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH)) &&
        (this->actor.velocity.y <= 0.0f)) {
        this->actor.velocity.y = 0.0f;
    }

    if (this->timer > 0) {
        this->timer--;
    } else if ((this->actor.xzDistToPlayer < 350.0f) && (this->actor.yDistToPlayer <= 80.0f)) {
        EnZol_SetupTurnTowardPlayer(this);
    }
}

// zol rotates towards player
void EnZol_SetupTurnTowardPlayer(EnZol* this) {
    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH)) {
        if (this->actor.velocity.y <= 0.0f) {
            this->actor.gravity = 0.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.speed = 0.0f;
        }
    }
    this->actionFunc = EnZol_TurnTowardPlayer;
}

void EnZol_TurnTowardPlayer(EnZol* this, PlayState* play) {
    s16 angleToPlayer;
    s16 turnVelocity;

    Math_SmoothStepToF(&this->actor.scale.y, this->scale, 0.4f, 0.2f, 0.0f);

    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH)) {
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.speed = 0.0f;
    }

    // Calculate turn velocity based on angle to player
    angleToPlayer = Actor_WorldYawTowardActor(&this->actor, &GET_PLAYER(play)->actor) - this->actor.world.rot.y;
    if (angleToPlayer > 0) {
        turnVelocity = (angleToPlayer / 42.0f) + 10.0f;
        this->actor.world.rot.y += (turnVelocity * 4);
    } else {
        turnVelocity = (angleToPlayer / 42.0f) - 10.0f;
        this->actor.world.rot.y += (turnVelocity * 4);
    }

    // Idle if player is far enough away from the zol, move or attack if almost facing player
    this->actor.shape.rot.y = this->actor.world.rot.y;
    if ((this->actor.xzDistToPlayer > 350.0f) && (this->actor.yDistToPlayer > 80.0f)) {
        EnZol_SetupIdle(this);
    } else if (Actor_IsFacingPlayer(&this->actor, 3640)) {
        EnZol_SetupJumpTowardPlayer(this);
    }
}

// zol jumps towards player
void EnZol_SetupJumpTowardPlayer(EnZol* this) {
    this->timer = 25;
    this->actor.velocity.y = 10.0f;
    this->actor.gravity = -1.0f;
    this->actor.speed = 6.0f;
    Actor_PlaySfx(&this->actor, NA_SE_EN_AWA_BOUND);
    this->actionFunc = EnZol_JumpTowardPlayer;
}

void EnZol_JumpTowardPlayer(EnZol* this, PlayState* play) {
    this->timer--;
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 0.1f, 1.0f, 0.0f);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 1000, 0);

    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND_TOUCH)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_DODO_M_GND);
        this->state = ZOL_LANDED;
        this->wobbletimerMax = 120;
        this->wobbleScale = 0.03f;
    }

    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH) && (this->actor.velocity.y <= 0.0f)) {
        // slightly turn toward player upon landing
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 1, 4000, 0);
        this->actor.world.rot.y = this->actor.shape.rot.y;

        if (this->actor.floorHeight > BGCHECK_Y_MIN) {
            this->actor.world.pos.y = this->actor.floorHeight;
        }

        if (this->timer <= 0) {
            EnZol_SetupIdle(this);
        }
    }
}

// zol recoils after being hit
void EnZol_SetupRecoil(EnZol* this) {
    this->timer = 7;
    this->actor.speed = -6.0f;
    this->actor.gravity = -1.0f;
    this->actionFunc = EnZol_Recoil;
}

void EnZol_Recoil(EnZol* this, PlayState* play) {
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 0.5f, 0.0f);
    
    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND_TOUCH)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_DODO_M_GND);
        this->state = ZOL_LANDED;
        this->wobbletimerMax = 120;
        this->wobbleScale = 0.03f;
    }

    if (this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH) && (this->actor.velocity.y <= 0.0f)) {
        if (this->actor.floorHeight > BGCHECK_Y_MIN) {
            this->actor.world.pos.y = this->actor.floorHeight;
        }
    }

    if ((this->actor.speed == 0.0f) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        if (this->timer > 0) {
            this->timer--;
        } else {
            this->actor.world.rot.y = this->actor.shape.rot.y;
            this->collider.base.atFlags &= ~AT_HIT;

            EnZol_SetupJumpTowardPlayer(this); 
        }
    }
}

// zol frozen
void EnZol_SetupFrozen(EnZol* this) {
    this->state = ZOL_FROZEN;
    this->actor.velocity.y = 0.0f;
    this->actor.speed = 0.0f;
    this->actor.gravity = 0.0f;
    Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_BLUE, 255, COLORFILTER_BUFFLAG_XLU, 36);
    this->timer = 50;
    this->actionFunc = EnZol_Frozen;
}

void EnZol_Frozen(EnZol* this, PlayState* play) {
    Vec3f pos;
    s16 iceChunkVar;
    s16 iceChunkTimer;

    if (this->timer != 0) {
        this->timer--;
    }

    iceChunkTimer = this->timer - 34;
    this->actor.colorFilterTimer = 36;

    if (iceChunkTimer > 0) {
        iceChunkVar = iceChunkTimer >> 1;

        if ((this->timer % 2) != 0) {
            pos.y = this->actor.world.pos.y + ((Rand_ZeroOne() * 45.0f) * (this->actor.scale.y * 10));
            pos.x = this->actor.world.pos.x + ((iceChunkVar & 2) ? 18.0f : -18.0f);
            pos.z = this->actor.world.pos.z + ((iceChunkVar & 1) ? 18.0f : -18.0f);

            EffectSsEnIce_SpawnFlyingVec3f(play, &this->actor, &pos, 150, 150, 150, 250, 235, 245, 255,
                                           (Rand_ZeroOne() * this->scale) + 1.8f);
        }
    } else if (this->timer == 0) {
        this->actor.gravity = -1.0f;
        if ((this->actor.speed == 0.0f) && (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
            Actor_PlaySfx(&this->actor, NA_SE_PL_ICE_BROKEN);
            EnZol_SetupJumpTowardPlayer(this);
            this->actor.colorFilterTimer = 0;
        }
    }
}

// zol dies
void EnZol_SetupDeathCry(EnZol* this) {
    this->state = ZOL_DEATH;
    this->actor.colorFilterTimer = 0;
    this->actor.speed = 0.0f;
    this->actionFunc = EnZol_DeathCry;
}

static Vec3f sEffectAccel = { 0.0f, -0.5f, 0.0f };
static Color_RGBA8 sEffectPrimColor = { 180, 255, 180, 255 };
static Color_RGBA8 sEffectEnvColor = { 0, 70, 0, 0 };

void EnZol_DeathCry(EnZol* this, PlayState* play) {
    u32 i;
    Vec3f effectAccel;
    Vec3f effectVel;
    Vec3f effectPos;
    Color_RGBA8 effectPrimColor;
    Color_RGBA8 effectEnvColor;
    u8 effectScale;

    Actor_SetScale(&this->actor, this->actor.scale.x * 1.185f);
    if (this->actor.scale.y >= this->scale + 0.08f) {
        EffectSsDeadSound_SpawnStationary(play, &this->actor.projectedPos, NA_SE_EN_AWA_BREAK, true,
                                        DEADSOUND_REPEAT_MODE_OFF, 40);
        effectPrimColor = sEffectPrimColor;
        effectEnvColor = sEffectEnvColor;
        if (ENZOL_TYPE == ZOL_SPLIT || ENZOL_TYPE == ZOL_RED) { // red one, split
            effectScale = 100;
            effectPrimColor.r = 255;
            effectPrimColor.g = 180;
            effectEnvColor.r = 70;
            effectEnvColor.g = 0;
            Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0x10);
        } else { // green
            effectScale = 150;
            Item_DropCollectibleRandom(play, &this->actor, &this->actor.world.pos, 0x10);
        }
        effectAccel = sEffectAccel;

        effectPos.x = this->actor.world.pos.x;
        effectPos.y = this->actor.world.pos.y;
        effectPos.z = this->actor.world.pos.z;

        for (i = 0; i < 20; i++) {
            effectVel.x = (Rand_ZeroOne() - 0.5f) * 10.0f;
            effectVel.y = Rand_ZeroOne() * 10.0f;
            effectVel.z = (Rand_ZeroOne() - 0.5f) * 10.0f;
            EffectSsDtBubble_SpawnCustomColor(play, &effectPos, &effectVel, &effectAccel, &effectPrimColor,
                                              &effectEnvColor, Rand_S16Offset(effectScale, 50), 0x19, 0);
        }
        Actor_Kill(&this->actor);
    }
}

// water check
void EnZol_CheckDrowned(EnZol* this) {
    if (this->state != ZOL_DEATH && (this->actor.bgCheckFlags & BGCHECKFLAG_WATER) && (this->actor.yDistToWater > 5.0f)) {
        this->actor.gravity = -0.1f;
        EnZol_SetupDeathCry(this);
        return;
    }
}

// damage check
void EnZol_CheckDamage(Actor* thisx, PlayState* play) {
    EnZol* this = (EnZol*)thisx;

    EnZol_CheckDrowned(this);

    if (this->collider.base.acFlags & AC_HIT && this->actionFunc != EnZol_Recoil && this->state != ZOL_WAIT  && this->state != ZOL_DEATH) {
        this->collider.base.acFlags &= ~AC_HIT;
        this->damageEffect = thisx->colChkInfo.damageEffect;

        if ((thisx->colorFilterTimer == 0) || ((thisx->colorFilterParams & 0x4000) == 0)) {
            if (this->actor.colChkInfo.damageEffect == ZOL_DMGEFF_ICE && this->state != ZOL_FROZEN) {
                EnZol_SetupFrozen(this);
            } else {
                Actor_SetColorFilter(thisx, 0x4000, 0xFF, 0, 8);
                Actor_ApplyDamage(thisx);
                this->wobbletimerMax = 120;
                this->wobbleScale = 0.03f;

                this->actor.world.rot.y = this->actor.yawTowardsPlayer;
                EnZol_SetupRecoil(this);

                // split into two mini zols via actor spawn
                if (ENZOL_TYPE == ZOL_RED) {
                    Actor* childZol;

                    this->actor.params = ZOL_SPLIT;
                    this->scale = 0.04f;
                    Actor_SetScale(&this->actor, this->scale);
                    this->collider.dim.radius = 26;
                    this->collider.dim.height = 35;

                    Actor_PlaySfx(thisx, NA_SE_EN_AWA_BREAK);

                    childZol = Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_ZOL,
                                                    thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z,
                                                    thisx->world.rot.x, this->actor.yawTowardsPlayer - 0x4000, thisx->world.rot.z, ZOL_SPLIT);

                    this->actor.world.rot.y = this->actor.yawTowardsPlayer + 0x4000;

                    if (childZol != NULL) {
                        childZol->colChkInfo.health = thisx->colChkInfo.health;
                    }
                }
            }
        }
        if (thisx->colChkInfo.health == 0) {
            EnZol_SetupDeathCry(this);
        }
    }
}

void EnZol_Update(Actor* thisx, PlayState* play) {
    EnZol* this = (EnZol*)thisx;
    Player* player = GET_PLAYER(play);

    EnZol_CheckDamage(thisx, play);

    this->actionFunc(this, play);

    Actor_MoveXZGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 20.0f,this->bgcheckinfo);

    if (this->wobbletimerMax > 0) {
        this->wobbletimerMax--;
    }
    
    EnZol_Scale(this);
    if (this->state < ZOL_FROZEN) {
        EnZol_Wobble(this);
    }

    thisx->focus.pos = thisx->world.pos;
    thisx->focus.pos.y = thisx->world.pos.y + 20.0f;

    Collider_UpdateCylinder(thisx, &this->collider);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    if (player->invincibilityTimer == 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base); // add check for player damagetimer
    }
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnZol_Draw(Actor* thisx, PlayState* play) {
    EnZol* this = (EnZol*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    func_8002ED80(&this->actor, play, 0); // hilite
    Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y,
                                 this->actor.world.pos.z, &this->actor.shape.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx, __FILE__, __LINE__),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    switch (ENZOL_TYPE) {
        case ZOL_GREEN:
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 70, 0, 255);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x00, 0x80, 180, 255, 180, 255);
        break;
        case ZOL_SPLIT:
        case ZOL_RED:
            gDPSetEnvColor(POLY_XLU_DISP++, 70, 0, 0, 255);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x00, 0x80, 255, 180, 180, 255);
        break;
    }

    gSPDisplayList(POLY_XLU_DISP++, gZolNormalDL);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_DrawDListOpa(play, gZolEyesDL);
}
