#ifndef INVISIBLE_TRIGGER_SWITCH_H
#define INVISIBLE_TRIGGER_SWITCH_H

#include "ultra64.h"
#include "global.h"

struct InvisibleTriggerSwitch;

typedef void (*InvisibleTriggerSwitchActionFunc)(struct InvisibleTriggerSwitch*, PlayState*);

typedef struct InvisibleTriggerSwitch {
    Actor actor;
    InvisibleTriggerSwitchActionFunc actionFunc;
    f32 detectionRadius;
} InvisibleTriggerSwitch;

#endif
