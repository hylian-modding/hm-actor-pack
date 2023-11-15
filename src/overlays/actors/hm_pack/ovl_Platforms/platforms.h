#ifndef Z_PLATFORMS_H
#define Z_PLATFORMS_H

#include "ultra64.h"
#include "global.h"

struct Platforms;

typedef void (*PlatformsActionFunc)(struct Platforms*, PlayState*);

typedef struct Platforms {
    DynaPolyActor dyna;
    PlatformsActionFunc actionFunc;
    Vec3f targetPos;
    u16 timer;
    s16 alphaTarget;
    s16 alpha;
    u8 coneDipPlayer;
    u8 coneDipReturn;
    u8 playerOn;
} Platforms;

#endif