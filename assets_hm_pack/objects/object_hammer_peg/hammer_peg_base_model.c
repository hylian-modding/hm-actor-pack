#include "ultra64.h"
#include "global.h"

u64 gHammerPegBaseDL_Hammer_Peg_02_ci8[] = {
	0x0001000002030401, 0x0005060703080609, 0x0a030a0a0a060600, 0x0b00000100070000, 0x0c0d0c0e0c0f100e, 0x11111112130f0e14, 0x1516170e0e0e1518, 0x161419121312111a, 
	0x1b1b1b1b1c1c1d05, 0x011d011c1c051d1e, 0x01011405051f1f20, 0x0501010105212101, 0x1b2120011c221c05, 0x1c1f01011c1c051b, 0x2221080105011b01, 0x2101210121011c01, 
	0x20191b231c220114, 0x011c1c1c01052114, 0x01211414011c2424, 0x0124011c051c1c14, 0x192020141c241c05, 0x251c08051c011c01, 0x2401141c24010501, 0x05011c0505010501, 
	0x1925141c1c1c051c, 0x1c0501141c140521, 0x0514221405262126, 0x2105052705141401, 0x191c08281c051401, 0x15011c211c151501, 0x051c22211c052605, 0x21011c011c1c2801, 
	0x271c051405191405, 0x142601251427281c, 0x26140527251c1c05, 0x012121210121051c, 0x251c140515152205, 0x19051c01191c1c05, 0x151c150525212105, 0x1c211c0121210501, 
	0x1c15271414141c1c, 0x1c271c2614151c25, 0x0522151c05212114, 0x2105012121142105, 0x151521151c1c2805, 0x1425141414011914, 0x1c05211c051c1c21, 0x05211c211c212101, 
	0x15151c231c231c1c, 0x15291422191c151c, 0x251c1c151c222126, 0x1c1c1c141c140505, 0x222a2a2a1c1c1c2a, 0x1c011c1423052a01, 0x1c2a1c011c010101, 0x1c2a2a012a2a222a, 
	0x0606060606060a06, 0x060404090a090604, 0x0700060706060604, 0x0606060704040606, 0x060a062b0606060a, 0x041f010106070706, 0x060606060606060a, 0x060604070a0a0606, 
	
};

u64 gHammerPegBaseDL_Hammer_Peg_02_pal_rgba16[] = {
	0x20c529491883294b, 0x2107318b18c520c7, 0x39cf210918851083, 0x8c615ad763176319, 0x739b6b5763596b59, 0x420f421152957c1f, 0x5a9552935ad539cb, 0x39cd31cd29072909, 
	0x4a0f31494a514a53, 0x318941cd398b3989, 0x3a0f6357318d18c7, 
};

Vtx gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1500, 0, -1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-1500, 0, 1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-1500, 500, 1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {-1500, 500, -1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {1500, 0, -1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {1500, 0, 1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {1500, 500, 1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
	{{ {1500, 500, -1500}, 0, {-16, -16}, {0, 0, 0, 0} }},
};

Vtx gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_vtx_0[20] = {
	{{ {-1000, 500, 1000}, 0, {1008, -16}, {166, 90, 0, 255} }},
	{{ {-1500, 0, -1500}, 0, {-16, 496}, {166, 90, 0, 255} }},
	{{ {-1500, 0, 1500}, 0, {1008, 496}, {166, 90, 0, 255} }},
	{{ {-1000, 500, -1000}, 0, {-16, -16}, {166, 90, 0, 255} }},
	{{ {-1000, 500, -1000}, 0, {1008, -16}, {0, 90, 166, 255} }},
	{{ {1500, 0, -1500}, 0, {-16, 496}, {0, 90, 166, 255} }},
	{{ {-1500, 0, -1500}, 0, {1008, 496}, {0, 90, 166, 255} }},
	{{ {1000, 500, -1000}, 0, {-16, -16}, {0, 90, 166, 255} }},
	{{ {1000, 500, -1000}, 0, {1008, -16}, {90, 90, 0, 255} }},
	{{ {1500, 0, 1500}, 0, {-16, 496}, {90, 90, 0, 255} }},
	{{ {1500, 0, -1500}, 0, {1008, 496}, {90, 90, 0, 255} }},
	{{ {1000, 500, 1000}, 0, {-16, -16}, {90, 90, 0, 255} }},
	{{ {1000, 500, 1000}, 0, {1008, -16}, {0, 90, 90, 255} }},
	{{ {-1500, 0, 1500}, 0, {-16, 496}, {0, 90, 90, 255} }},
	{{ {1500, 0, 1500}, 0, {1008, 496}, {0, 90, 90, 255} }},
	{{ {-1000, 500, 1000}, 0, {-16, -16}, {0, 90, 90, 255} }},
	{{ {-1000, 500, -1000}, 0, {-16, 418}, {0, 127, 0, 255} }},
	{{ {1000, 500, 1000}, 0, {1008, 62}, {0, 127, 0, 255} }},
	{{ {1000, 500, -1000}, 0, {-16, 62}, {0, 127, 0, 255} }},
	{{ {-1000, 500, 1000}, 0, {1008, 418}, {0, 127, 0, 255} }},
};

Gfx gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_vtx_0 + 0, 20, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 15, 13, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 19, 17, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gHammerPegBaseDL_Base_layerOpaque[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gHammerPegBaseDL_Hammer_Peg_02_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 43),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, gHammerPegBaseDL_Hammer_Peg_02_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 255, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 60),
	gsSPEndDisplayList(),
};

Gfx gHammerPegBaseDL[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gHammerPegBaseDL_Base_layerOpaque),
	gsSPDisplayList(gHammerPegBaseDL_gHammerPegBaseDL_mesh_layer_Opaque_tri_0),
	gsSPEndDisplayList(),
};

