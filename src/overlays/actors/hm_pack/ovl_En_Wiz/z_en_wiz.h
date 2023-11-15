#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "ultra64.h"
#include "global.h"
#include "assets_hm_pack/objects/object_wiz/object_wiz.h"

struct EnWiz;

typedef void (*EnWizActionFunc)(struct EnWiz*, PlayState*);

typedef enum {
    /* 0 */ ENWIZ_TYPE_MASTER,  // master wizzrobe
    /* 1 */ ENWIZ_TYPE_FIRE,    // fire wizzrobe
    /* 2 */ ENWIZ_TYPE_ICE      // ice wizzrobe
} EnWizType;

typedef struct EnWiz {
    Actor actor;
    SkelAnime skelAnime;
    EnWizActionFunc actionFunc;
    ColliderCylinder collider;
    s16 type;
    s16 alpha;
    s16 timer;
    Actor* spawnedActor[2];
    u8 spawnCount[2];
    u8 enemySpawnSet;
    s16 hasActiveProjectile;
    s8 dropboomerang;
    Vec3f staffFlamePos;
    u8 castMagicType;
    Color_RGBA8 castColor;
    Color_RGBA8 typeColor;
    u8 EnemyAnim;
    u8 spawnIceTimer;
    s16 teleportTimer;
    f32 floatPosY;
    Vec3s bodyPartsPos[10];
    Vec3s jointTable[12];
    Vec3s morphTable[12];
} EnWiz;

#endif
