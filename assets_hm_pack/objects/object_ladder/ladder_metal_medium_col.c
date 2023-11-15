#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gLadderMetalMediumCol_polygonTypes[] = {
	{ 0x00400000, 0x000037c2 },
	{ 0x00600000, 0x000037c2 },
	{ 0x00000000, 0x000037c2 },
};

CollisionPoly gLadderMetalMediumCol_polygons[] = {
	{ 0x0000, 0x2000, 0x0001, 0x0002, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.39939071839035e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0000, 0x2000, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.39939071839035e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0001, 0x2005, 0x0006, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711395392165286e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0001, 0x2006, 0x0007, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711395392165286e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0002, 0x2008, 0x0009, 0x000a, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.39939071839035e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
	{ 0x0002, 0x2008, 0x000b, 0x0009, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.39939071839035e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
};

Vec3s gLadderMetalMediumCol_vertices[12] = {
	{ 1591, 0, 424 },
	{ 1591, 21000, 424 },
	{ -1591, 21000, 424 },
	{ -1591, 0, 424 },
	{ 1591, 21500, 0 },
	{ 1591, 19500, 0 },
	{ -1591, 19500, 0 },
	{ -1591, 21500, 0 },
	{ 1591, 0, 212 },
	{ -1591, 21000, 212 },
	{ 1591, 21000, 212 },
	{ -1591, 0, 212 },
};

CollisionHeader gLadderMetalMediumCol_collisionHeader = {
	-1591,
	0,
	0,
	1591,
	21500,
	424,
	12,
	gLadderMetalMediumCol_vertices,
	6,
	gLadderMetalMediumCol_polygons,
	gLadderMetalMediumCol_polygonTypes,
	0,
	0,
	0
};

