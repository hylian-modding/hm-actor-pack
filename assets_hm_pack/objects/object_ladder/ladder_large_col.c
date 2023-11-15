#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gLadderLargeCol_polygonTypes[] = {
	{ 0x00400000, 0x000237ca },
	{ 0x00600000, 0x000037ca },
	{ 0x00000000, 0x000237ca },
};

CollisionPoly gLadderLargeCol_polygons[] = {
	{ 0x0000, 0x2000, 0x0001, 0x0002, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.391921137880672e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0000, 0x2000, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.391921137880672e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0001, 0x2005, 0x0006, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.371135275960114e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0001, 0x2006, 0x0007, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.371135275960114e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0002, 0x2008, 0x0009, 0x000a, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.391921137880672e-08), COLPOLY_SNORMAL(1.0), 0xff2c },
	{ 0x0002, 0x2008, 0x000a, 0x000b, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.391921137880672e-08), COLPOLY_SNORMAL(1.0), 0xff2c },
};

Vec3s gLadderLargeCol_vertices[12] = {
	{ 1556, 0, 424 },
	{ 1556, 28500, 424 },
	{ -1556, 28500, 424 },
	{ -1556, 0, 424 },
	{ 1556, 29000, 0 },
	{ 1556, 27000, 0 },
	{ -1556, 27000, 0 },
	{ -1556, 29000, 0 },
	{ 1556, 0, 212 },
	{ 1556, 28500, 212 },
	{ -1556, 28500, 212 },
	{ -1556, 0, 212 },
};

CollisionHeader gLadderLargeCol_collisionHeader = {
	-1556,
	0,
	0,
	1556,
	29000,
	424,
	12,
	gLadderLargeCol_vertices,
	6,
	gLadderLargeCol_polygons,
	gLadderLargeCol_polygonTypes,
	0,
	0,
	0
};

