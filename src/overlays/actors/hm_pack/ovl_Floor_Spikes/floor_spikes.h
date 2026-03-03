#ifndef Z_FLOOR_SPIKES_H
#define Z_FLOOR_SPIKES_H

#include "ultra64.h"
#include "actor.h"
#include "collision_check.h"
#include "play_state.h"

struct FloorSpikes;

typedef void (*FloorSpikesActionFunc)(struct FloorSpikes*, PlayState*);

typedef struct FloorSpikes {
    DynaPolyActor dyna;
    FloorSpikesActionFunc actionFunc;
    ColliderQuad playerCollider;
    ColliderQuad othersCollider;
    f32 spikeProgress;
    u8 timer;
    u8 useSwitchFlag;
    u8 useVoidOut;
    u8 spikesActive;
    u8 cyclicState;
} FloorSpikes;

#endif
