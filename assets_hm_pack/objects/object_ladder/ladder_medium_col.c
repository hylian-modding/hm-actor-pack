#include "ultra64.h"
#include "z64.h"
#include "macros.h"

SurfaceType gLadderMediumCol_polygonTypes[] = {
	{ 0x00400000, 0x000237ca },
	{ 0x00600000, 0x000037ca },
	{ 0x00000000, 0x000237ca },
};

CollisionPoly gLadderMediumCol_polygons[] = {
	{ 0x0000, 0x2000, 0x0001, 0x0002, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.399391073661718e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0000, 0x2000, 0x0002, 0x0003, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(4.399391073661718e-08), COLPOLY_SNORMAL(1.0), 0xfe58 },
	{ 0x0001, 0x2005, 0x0006, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711398944878965e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0001, 0x2006, 0x0007, 0x0004, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.3711398944878965e-08), COLPOLY_SNORMAL(-1.0), 0x0000 },
	{ 0x0002, 0x2008, 0x0009, 0x000a, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.399391073661718e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
	{ 0x0002, 0x2008, 0x000b, 0x0009, COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-4.399391073661718e-08), COLPOLY_SNORMAL(-1.0), 0x00d4 },
};

Vec3s gLadderMediumCol_vertices[12] = {
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

CollisionHeader gLadderMediumCol_collisionHeader = {
	-1591,
	0,
	0,
	1591,
	21500,
	424,
	12,
	gLadderMediumCol_vertices,
	6,
	gLadderMediumCol_polygons,
	gLadderMediumCol_polygonTypes,
	0,
	0,
	0
};

