#ifndef Z_OBJ_FAN_H
#define Z_OBJ_FAN_H

#include "ultra64.h"
#include "global.h"

struct ObjFan;

typedef void (*ObjFanActionFunc)(struct ObjFan*, PlayState*);

typedef struct {
    Actor actor;
    Vec3f relativeActorPos;
    ObjFanActionFunc actionFunc;
    s16 propellerRot;
    f32 power;
    s8 flag;
    f32 scale;
} ObjFan;

#endif