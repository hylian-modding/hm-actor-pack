#ifndef Z_HAMMER_PEG_H
#define Z_HAMMER_PEG_H

#include "ultra64.h"
#include "actor.h"
#include "collision_check.h"
#include "play_state.h"

#include "assets/objects/hm_pack/object_hammer_peg/object_hammer_peg.h"

struct HammerPeg;

typedef void (*HammerPegActionFunc)(struct HammerPeg*, PlayState*);

typedef struct HammerPeg {
    DynaPolyActor dyna;
    ColliderCylinder colliderBase;
    ColliderCylinder colliderTop;
    HammerPegActionFunc actionFunc;
    s32 percentUp;
} HammerPeg;

#endif
