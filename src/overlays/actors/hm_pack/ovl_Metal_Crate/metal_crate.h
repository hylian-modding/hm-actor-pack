#ifndef Z_METAL_CRATE_H
#define Z_METAL_CRATE_H

#include "ultra64.h"
#include "actor.h"
#include "collision_check.h"
#include "play_state.h"

struct MetalCrate;

typedef void (*MetalCrateActionFunc)(struct MetalCrate*, PlayState*);

typedef struct MetalCrate {
    DynaPolyActor dyna;
    MetalCrateActionFunc actionFunc;
    ColliderCylinder collider;
    s16 collectibleFlag;
} MetalCrate;

#endif
