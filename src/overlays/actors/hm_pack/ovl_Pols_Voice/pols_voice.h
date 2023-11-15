#ifndef Z_POLSVOICE_H
#define Z_POLSVOICE_H

#include "ultra64.h"
#include "global.h"

#include "assets_hm_pack/objects/object_pols_voice/object_pols_voice.h"

struct PolsVoice;

typedef void (*PolsVoiceActionFunc)(struct PolsVoice*, PlayState*);

typedef struct PolsVoice {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[GPOLSVOICESKEL_NUM_LIMBS];
    Vec3s morphTable[GPOLSVOICESKEL_NUM_LIMBS];
    s32 invincibilityTimer;
    ColliderCylinder collider;
    s16 targetYaw;
    u8 drowned;
    u8 gnawTimer;
    u8 isGnawing;
    u8 aggroTimer;
    PolsVoiceActionFunc actionFunc;
} PolsVoice;

#endif
