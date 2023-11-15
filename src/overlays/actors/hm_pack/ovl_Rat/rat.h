#ifndef Z_RAT_H
#define Z_RAT_H

#include "ultra64.h"
#include "global.h"

#include "assets_hm_pack/objects/object_rat/object_rat.h"

struct Rat;

typedef void (*RatActionFunc)(struct Rat*, PlayState*);

typedef struct Rat {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[GRATSKEL_NUM_LIMBS];
    Vec3s morphTable[GRATSKEL_NUM_LIMBS];
    ColliderCylinder collider;
    Vec3f targetPos;
    s16 targetYaw;
    u16 fleeTimer;
    Vec3f fleePos;
    u8 drowned;
    RatActionFunc actionFunc;
} Rat;

#endif
