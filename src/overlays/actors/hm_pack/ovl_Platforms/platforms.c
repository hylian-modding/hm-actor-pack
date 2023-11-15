/*
 * File: z_platforms.c
 * Overlay: ovl_Platforms
 * Description: Various floating platforms, from the Hylian Modding actor pack.
 */

#include "platforms.h"
#include "assets_hm_pack/objects/object_platforms/object_platforms.h"

#define PLATFORM_TYPE(this) ((this->dyna.actor.params >> 0xC) & 0xF) // 0xF000
#define SWITCH_FLAG(this) (this->dyna.actor.params & 0x3F) // 0x00FF
#define TIMER_DURATION(this) (this->dyna.actor.home.rot.x) // <= 10 minutes (600)

/**
 * Params:
 *  0xF000 = Type
 *     0x0 = Square Wooden Platform 
 *     0x1 = Square Wooden Platform (Checkered Pattern)
 *     0x2 = Square Stone Platform
 *     0x3 = Square Stone Platform (Checkered Pattern)
 *     0x4 = Square Grass Platform 
 *     0x5 = Square Ice Platform
 *     0x6 = Hexagonal Grass Platform
 *     0x7 = Hexagonal Ice Platform
 *     0x8 = Cone Floating Grass Platform
 * 
 *  0x00FF = Switch Flag
 *  
 *  Rot X > 0 = Duration timer for spawned platforms (in seconds)
 * 
 *  All platform types (except for the Cone Floating Type) will spawn on switch flag activation. After the specified timer amount, they unset the switch
 *  and disappear again until the flag is once again set.
 *  
 *  Default (Rot X = 0) timer is 10 seconds. You can go up to 10 minutes (600).
 * 
 *  Square platforms = 200 units
 *  Hex platforms    = 328 units
 *  Cone platform    = 206 units
*/

#define FLAGS (ACTOR_FLAG_4)

#define SECONDS_TO_FRAMES(sec) (sec * (60 / R_UPDATE_RATE))
static u8 sPlayerOn = false;
static u16 sTimer = 0;

void Platforms_Init(Actor* thisx, PlayState* play);
void Platforms_Destroy(Actor* thisx, PlayState* play);
void Platforms_Update(Actor* thisx, PlayState* play);
void Platforms_Draw(Actor* thisx, PlayState* play);

void Platforms_SetupWaitForSwitch(Platforms* this, PlayState* play);
void Platforms_WaitForSwitch(Platforms* this, PlayState* play);
void Platforms_SetupAppear(Platforms* this, PlayState* play);
void Platforms_Appear(Platforms* this, PlayState* play);
void Platforms_SetupDisappear(Platforms* this, PlayState* play);
void Platforms_Disappear(Platforms* this, PlayState* play);

void Platforms_SetupConeFloat(Platforms* this, PlayState* play);
void Platforms_ConeFloat(Platforms* this, PlayState* play);
void Platforms_SetupConeDip(Platforms* this, PlayState* play);
void Platforms_ConeDip(Platforms* this, PlayState* play);

void Platforms_DoNothing(Platforms* this, PlayState* play);

typedef enum {
    PLATFORM_TYPE_SQ_WOOD = 0,
    PLATFORM_TYPE_SQ_WOOD_CHECKER,
    PLATFORM_TYPE_SQ_STONE,
    PLATFORM_TYPE_SQ_STONE_CHECKER,
    PLATFORM_TYPE_SQ_GRASS,
    PLATFORM_TYPE_SQ_ICE,
    PLATFORM_TYPE_HEX_GRASS,
    PLATFORM_TYPE_HEX_ICE,
    PLATFORM_TYPE_CONE_GRASS
} PlatformType;

const ActorInit Platforms_InitVars = {
    ACTOR_PLATFORMS,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_PLATFORMS,
    sizeof(Platforms),
    (ActorFunc)Platforms_Init,
    (ActorFunc)Platforms_Destroy,
    (ActorFunc)Platforms_Update,
    (ActorFunc)Platforms_Draw,
};


static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

void Platforms_Init(Actor* thisx, PlayState* play) {
    Platforms* this = (Platforms*)thisx;
    CollisionHeader* colHeader = NULL;
    u16 seconds;

    Actor_ProcessInitChain(thisx, sInitChain);
    DynaPolyActor_Init(&this->dyna, (DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y));

    switch (PLATFORM_TYPE(this)) {
        case PLATFORM_TYPE_SQ_WOOD:
        case PLATFORM_TYPE_SQ_WOOD_CHECKER:
            CollisionHeader_GetVirtual(&gPlatform_WoodDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_SQ_STONE:
        case PLATFORM_TYPE_SQ_STONE_CHECKER:
            CollisionHeader_GetVirtual(&gPlatform_StoneDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_SQ_GRASS:
            CollisionHeader_GetVirtual(&gPlatform_GrassDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_SQ_ICE:
            CollisionHeader_GetVirtual(&gPlatform_IceDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_HEX_GRASS:
            CollisionHeader_GetVirtual(&gPlatform_HexGrassDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_HEX_ICE:
            CollisionHeader_GetVirtual(&gPlatform_HexIceDL_collisionHeader, &colHeader);
            break;
        case PLATFORM_TYPE_CONE_GRASS:
            CollisionHeader_GetVirtual(&gPlatform_FloatingConeDL_collisionHeader, &colHeader);
            break;
    }

    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);

    seconds = (TIMER_DURATION(this) == 0) ? 10 : CLAMP_MAX(TIMER_DURATION(this), 600);
    sTimer = this->timer = SECONDS_TO_FRAMES(seconds); // Clamped to max of 10 minutes, default of 10 seconds

    this->dyna.actor.shape.rot.x = this->dyna.actor.home.rot.x = 0.0f;
    this->dyna.actor.shape.rot.z = this->dyna.actor.home.rot.z = 0.0f;
    
    Actor_SetScale(&this->dyna.actor, 0.035f);

    if (PLATFORM_TYPE(this) != PLATFORM_TYPE_CONE_GRASS) {
        Platforms_SetupWaitForSwitch(this, play);
    } else {
        this->coneDipPlayer = false;
        this->coneDipReturn = false;
        Platforms_SetupConeFloat(this, play);
    } 
}

void Platforms_Destroy(Actor* thisx, PlayState* play) {
    Platforms* this = (Platforms*)thisx;

    if (PLATFORM_TYPE(this) != PLATFORM_TYPE_CONE_GRASS) {
        Flags_UnsetSwitch(play, SWITCH_FLAG(this));
    }

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void Platforms_Update(Actor* thisx, PlayState* play) {
    Platforms* this = (Platforms*)thisx;

    if (PLATFORM_TYPE(this) == PLATFORM_TYPE_CONE_GRASS) {
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y += 0x50; // slowly rotate
    }

    Math_SmoothStepToS(&this->alpha, this->alphaTarget, 1, 24, 1);

    this->actionFunc(this, play);
}

Gfx* Platforms_SetupTransparent(GraphicsContext* gfxCtx) {
    Gfx* dList;
    Gfx* dListHead;

    dListHead = Graph_Alloc(gfxCtx, 2 * sizeof(Gfx));

    dList = dListHead;
    gDPSetRenderMode(dListHead++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA),
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gSPEndDisplayList(dListHead++);

    return dList;
}

Gfx* Platforms_SetupOpaque(GraphicsContext* gfxCtx) {
    Gfx* dList;
    Gfx* dListHead;

    dListHead = Graph_Alloc(gfxCtx, 2 * sizeof(Gfx));

    dList = dListHead;
    gDPSetRenderMode(dListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gSPEndDisplayList(dListHead++);

    return dList;
}

void Platforms_Draw(Actor* thisx, PlayState* play) {
    Platforms* this = (Platforms*)thisx;
    Gfx* dlist = NULL;
    void (*drawFunc)(PlayState*, Gfx*);

    if (PLATFORM_TYPE(this) == PLATFORM_TYPE_CONE_GRASS) {
        Gfx_DrawDListOpa(play, gPlatform_FloatingConeDL);
        return;
    }

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    if (this->alpha == 255) {
        gDPPipeSync(POLY_OPA_DISP++);
        Gfx_SetupDL_25Opa(play->state.gfxCtx);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        gSPSegment(POLY_OPA_DISP++, 0x08, Platforms_SetupOpaque(play->state.gfxCtx));
        drawFunc = Gfx_DrawDListOpa;
        // Gfx_DrawDListOpa(play, dlist);
    } else {
        gDPPipeSync(POLY_XLU_DISP++);
        Gfx_SetupDL_25Xlu(play->state.gfxCtx);
        gSPSegment(POLY_XLU_DISP++, 0x08, Platforms_SetupTransparent(play->state.gfxCtx));
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, this->alpha);
        drawFunc = Gfx_DrawDListXlu;
        // Gfx_DrawDListXlu(play, dlist);
    }
    
    if (this->alpha > 0) {
        switch (PLATFORM_TYPE(this)) {
            case PLATFORM_TYPE_SQ_WOOD:
                drawFunc(play, gPlatform_WoodDL);
                break;
            case PLATFORM_TYPE_SQ_WOOD_CHECKER:
                drawFunc(play, gPlatform_CheckWoodDL);
                break;
            case PLATFORM_TYPE_SQ_STONE:
                drawFunc(play, gPlatform_StoneDL);
                break;
            case PLATFORM_TYPE_SQ_STONE_CHECKER:
                drawFunc(play, gPlatform_CheckStoneDL);
                break;
            case PLATFORM_TYPE_SQ_GRASS:
                drawFunc(play, gPlatform_GrassDL);
                break;
            case PLATFORM_TYPE_SQ_ICE:
                drawFunc(play, gPlatform_IceDL);
                break;
            case PLATFORM_TYPE_HEX_GRASS:
                drawFunc(play, gPlatform_HexGrassDL);
                break;
            case PLATFORM_TYPE_HEX_ICE:
                drawFunc(play, gPlatform_HexIceDL);
                break;
        }
    }
    
    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

}

void Platforms_SetupWaitForSwitch(Platforms* this, PlayState* play) {
    DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
    this->actionFunc = Platforms_WaitForSwitch;
}

void Platforms_WaitForSwitch(Platforms* this, PlayState* play) {
    if (Flags_GetSwitch(play, SWITCH_FLAG(this))) {
        Platforms_SetupAppear(this, play);
    }
}

void Platforms_SetupAppear(Platforms* this, PlayState* play) {
    DynaPoly_EnableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
    this->timer = sTimer;
    this->alphaTarget = 255;
    this->actionFunc = Platforms_Appear;
}

void Platforms_Appear(Platforms* this, PlayState* play) {
    if (DECR(this->timer) == 0) {
        Flags_UnsetSwitch(play, SWITCH_FLAG(this));
        Platforms_SetupWaitForSwitch(this, play);
    } else if (this->timer == 10) {
        this->alphaTarget = 0;
    }
}

void Platforms_SetupConeFloat(Platforms* this, PlayState* play) {
    this->actionFunc = Platforms_ConeFloat;
}

void Platforms_ConeFloat(Platforms* this, PlayState* play) {
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 20.0f * (Math_SinS(play->gameplayFrames * 0x200)); // float up and down


    if (DynaPolyActor_IsPlayerAbove(&this->dyna)) {
        this->coneDipPlayer = false;
        if (DynaPolyActor_IsPlayerOnTop(&this->dyna) && !this->playerOn) {
            this->playerOn = true;
            Math_Vec3f_Copy(&this->targetPos, &this->dyna.actor.world.pos);
            this->targetPos.y -= 35.0f;
            Platforms_SetupConeDip(this, play);
            return;
        }
    } else if (!DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
        this->playerOn = false;
    }
}

void Platforms_SetupConeDip(Platforms* this, PlayState* play) {
    this->coneDipPlayer = true;
    this->coneDipReturn = false;
    this->actionFunc = Platforms_ConeDip;
}

void Platforms_ConeDip(Platforms* this, PlayState* play) {
    if (!DynaPolyActor_IsPlayerOnTop(&this->dyna)) {
        this->playerOn = false;
        Math_ApproachF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 0.1f, 5.0f);
        if (this->dyna.actor.world.pos.y >= this->dyna.actor.home.pos.y) {
            this->coneDipReturn = false;
            Platforms_SetupConeFloat(this, play);
            return;
        }
    }
    
    if (this->coneDipPlayer) {
        Math_ApproachF(&this->dyna.actor.world.pos.y, this->targetPos.y, 0.1f, 5.0f);

        if (this->dyna.actor.world.pos.y == this->targetPos.y) {
            this->coneDipPlayer = false;
            this->coneDipReturn = true;
        }
    } else {
        if (this->coneDipReturn) {
            Math_ApproachF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, 0.1f, 5.0f);
            if (this->dyna.actor.world.pos.y == this->dyna.actor.home.pos.y) {
                this->coneDipReturn = false;
                Platforms_SetupConeFloat(this, play);
            }
        }
    }
}


void Platforms_DoNothing(Platforms* this, PlayState* play) {

}