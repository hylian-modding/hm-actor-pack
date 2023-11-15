#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gSpikePadLargeCol_polygonTypes[] = {
	{ 0x00000000, 0x00000002 },
};

CollisionPoly gSpikePadLargeCol_polygons[] = {
	{ 0x0000, 0x0000, 0x0001, 0x0002, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xc180 },
	{ 0x0000, 0x0000, 0x0002, 0x0003, COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xc180 },
	{ 0x0000, 0x0003, 0x0002, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), 0xc180 },
	{ 0x0000, 0x0003, 0x0004, 0x0005, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-1.0), 0xc180 },
	{ 0x0000, 0x0005, 0x0004, 0x0006, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xc180 },
	{ 0x0000, 0x0005, 0x0006, 0x0007, COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), 0xc180 },
	{ 0x0000, 0x0007, 0x0006, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), 0xc180 },
	{ 0x0000, 0x0007, 0x0001, 0x0000, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), 0xc180 },
	{ 0x0000, 0x0004, 0x0002, 0x0001, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(-4.470348002882929e-08), 0xfc18 },
	{ 0x0000, 0x0004, 0x0001, 0x0006, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(-4.470348002882929e-08), 0xfc18 },
};

Vec3s gSpikePadLargeCol_vertices[8] = {
	{ -16000, 0, 16000 },
	{ -16000, 1000, 16000 },
	{ -16000, 1000, -16000 },
	{ -16000, 0, -16000 },
	{ 16000, 1000, -16000 },
	{ 16000, 0, -16000 },
	{ 16000, 1000, 16000 },
	{ 16000, 0, 16000 },
};

CollisionHeader gSpikePadLargeCol_collisionHeader = {
	-16000,
	0,
	-16000,
	16000,
	1000,
	16000,
	8,
	gSpikePadLargeCol_vertices,
	10,
	gSpikePadLargeCol_polygons,
	gSpikePadLargeCol_polygonTypes,
	0,
	0,
	0
};
