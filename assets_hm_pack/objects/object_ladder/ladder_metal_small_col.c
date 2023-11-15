#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gLadderMetalSmallCol_polygonTypes[] = {
	{ 0x00400000, 0x000037c2 },
	{ 0x00600000, 0x000037c2 },
	{ 0x00000000, 0x000037c2 },
};

CollisionPoly gLadderMetalSmallCol_polygons[] = {
	{ 0x0000, 0x2000, 0x0001, 0x0002, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.4151590827823384e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0000, 0x2000, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.4151590827823384e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0001, 0x2005, 0x0006, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711398944878965e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0001, 0x2006, 0x0007, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711398944878965e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0002, 0x2008, 0x0009, 0x000a, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.4151590827823384e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
	{ 0x0002, 0x2008, 0x000b, 0x0009, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.4151590827823384e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
};

Vec3s gLadderMetalSmallCol_vertices[12] = {
	{ 1556, 0, 424 },
	{ 1556, 13500, 424 },
	{ -1556, 13500, 424 },
	{ -1556, 0, 424 },
	{ 1556, 14000, 0 },
	{ 1556, 12000, 0 },
	{ -1556, 12000, 0 },
	{ -1556, 14000, 0 },
	{ 1556, 0, 212 },
	{ -1556, 13500, 212 },
	{ 1556, 13500, 212 },
	{ -1556, 0, 212 },
};

CollisionHeader gLadderMetalSmallCol_collisionHeader = {
	-1556,
	0,
	0,
	1556,
	14000,
	424,
	12,
	gLadderMetalSmallCol_vertices,
	6,
	gLadderMetalSmallCol_polygons,
	gLadderMetalSmallCol_polygonTypes,
	0,
	0,
	0
};

