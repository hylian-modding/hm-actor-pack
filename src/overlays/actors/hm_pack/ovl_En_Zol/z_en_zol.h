#ifndef Z_EN_ZOL_H
#define Z_EN_ZOL_H

#include "ultra64.h"
#include "global.h"

struct EnZol;

typedef void (*EnZolActionFunc)(struct EnZol*, PlayState*);

typedef enum {
    /* 0 */ ZOL_GREEN,  // 0x0000
    /* 1 */ ZOL_RED,    // 0x0001
    /* 2 */ ZOL_SPLIT   // 0x0002
} ZolType;

typedef enum {
    /* 0 */ ZOL_NONE,       // 0x0000
    /* 1 */ ZOL_FLOOR,      // 0x0100
    /* 2 */ ZOL_CEILING     // 0x0200
} ZolSpawn;

typedef struct EnZol {
    Actor actor;
    EnZolActionFunc actionFunc;
    ColliderCylinder collider;
    s32 bgcheckinfo;
    u8 damageEffect;
    f32 scale;
    f32 wobbleScale;
    s32 wobbletimerMax;
    s32 timer;
    s32 timer2;
    s16 state;
} EnZol;

#endif
