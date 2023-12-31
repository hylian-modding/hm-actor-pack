#include "ultra64.h"
#include "global.h"

s16 gRatSkelDamagedAnimFrameData[372] = {
	0x0000, 0x3fe3, 0x7fff, 0xffff, 0x03e4, 0x05a9, 0x0608, 0x05fd, 0x05db, 0x05a8, 0x056b, 0x052a, 0x04ea, 0x04ae, 0x0477, 0x0446, 
	0x041d, 0x03ff, 0x03eb, 0x03e4, 0xffe5, 0xfe94, 0xfe2e, 0xfdfd, 0xfda1, 0xfd38, 0xfcdf, 0xfcb6, 0xfcd3, 0xfd2c, 0xfdae, 0xfe45, 
	0xfede, 0xff63, 0xffc1, 0xffe5, 0x0854, 0xf0e7, 0xe6b4, 0xe52a, 0xe408, 0xe341, 0xe2ce, 0xe2a9, 0xe443, 0xe886, 0xeea3, 0xf5b0, 
	0xfcae, 0x02aa, 0x06ca, 0x0854, 0x7fca, 0x42d9, 0xfbe4, 0xf932, 0xf94c, 0x04d1, 0x13dc, 0x2154, 0x2f12, 0x3e7e, 0x4ed3, 0x5e83, 
	0x6c14, 0x7691, 0x7d5a, 0x7fca, 0xffff, 0x1525, 0x114e, 0x0e8d, 0x0a83, 0x0bb5, 0x0e0b, 0x0fe5, 0x115b, 0x114f, 0x0f4a, 0x0b8c, 
	0x072d, 0x0362, 0x00e3, 0xffff, 0xffff, 0xfd36, 0xe5a8, 0xe34e, 0xe0f9, 0xe3c9, 0xe8eb, 0xed18, 0xf0f1, 0xf5ca, 0xfaad, 0xfe55, 
	0x0029, 0x0082, 0x0035, 0xffff, 0x991e, 0xcdb0, 0x0902, 0x0837, 0x06c2, 0x044f, 0x0040, 0xf9c3, 0xf035, 0xe353, 0xd369, 0xc1f1, 
	0xb17c, 0xa46d, 0x9c14, 0x991e, 0x0000, 0x0c65, 0x15e0, 0x1348, 0x0df0, 0x07a1, 0x0247, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf89e, 0x0462, 0x03a5, 0x025a, 0x010b, 0x0032, 0xffff, 0xffff, 0xffff, 0x0000, 0xffff, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x7fca, 0x430c, 0xfb62, 0xf8c1, 0xf90d, 0x059d, 0x15fc, 0x23be, 0x3118, 0x3f7e, 0x4eba, 0x5dd6, 
	0x6b6f, 0x7639, 0x7d42, 0x7fca, 0xffff, 0xea02, 0xee19, 0xf137, 0xf51c, 0xf425, 0xf49b, 0xf606, 0xf72d, 0xf88c, 0xfa31, 0xfc00, 
	0xfdae, 0xfef7, 0xffbd, 0xffff, 0xffff, 0x02d9, 0x1b8e, 0x1e96, 0x2052, 0x196f, 0x10c2, 0x0b37, 0x07c4, 0x04f1, 0x02b7, 0x0131, 
	0x0060, 0x0011, 0x0001, 0xffff, 0x991e, 0xcc34, 0x07e6, 0x0758, 0x066e, 0x0457, 0x0058, 0xf9c3, 0xf022, 0xe337, 0xd34c, 0xc1db, 
	0xb170, 0xa468, 0x9c13, 0x991e, 0x0000, 0xf350, 0xe40d, 0xe79b, 0xee74, 0xf674, 0xfd2e, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0d3d, 0x022c, 0x020d, 0x01a8, 0x0124, 0x007a, 0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0xe951, 0xdc3b, 0xff1d, 0x1ed2, 0x1db7, 0x1a87, 0x1560, 0x0e87, 0x06a9, 0xfece, 0xf7e6, 0xf264, 
	0xee51, 0xeb87, 0xe9e1, 0xe951, 0x2065, 0x316b, 0x4063, 0x3fef, 0x3ea8, 0x3ca7, 0x3a04, 0x36da, 0x334b, 0x2f83, 0x2bb8, 0x2825, 
	0x2506, 0x2292, 0x20f8, 0x2065, 0xf8e3, 0xfdb3, 0x0737, 0x06da, 0x05da, 0x045b, 0x0288, 0x008e, 0xfe9b, 0xfcdb, 0xfb6a, 0xfa56, 
	0xf99c, 0xf92c, 0xf8f4, 0xf8e3, 0xfdbd, 0xf09b, 0xe64f, 0xe697, 0xe765, 0xe8b1, 0xea76, 0xeca9, 0xef39, 0xf207, 0xf4e7, 0xf7a9, 
	0xfa18, 0xfc06, 0xfd49, 0xfdbd, 0x2065, 0x31e9, 0x4218, 0x4197, 0x402a, 0x3df4, 0x3b13, 0x37aa, 0x33e2, 0x2feb, 0x2bfc, 0x284f, 
	0x251e, 0x229c, 0x20fb, 0x2065, 0x071c, 0x0332, 0xfb73, 0xfbbf, 0xfc91, 0xfdc9, 0xff46, 0x00e2, 0x0276, 0x03e1, 0x050c, 0x05ec, 
	0x0684, 0x06df, 0x070e, 0x071c, 0x0242, 0x0c8f, 0x1465, 0x1430, 0x1398, 0x12a0, 0x114a, 0x0f9b, 0x0da1, 0x0b74, 0x0935, 0x070c, 
	0x0522, 0x039d, 0x029e, 0x0242, 0xad1e, 0xd998, 0xebcd, 0xedd3, 0xf186, 0xf590, 0xf8b5, 0xf9f7, 0xf730, 0xeee2, 0xe114, 0xd097, 
	0xc23b, 0xb784, 0xb001, 0xad1e, };

JointIndex gRatSkelDamagedAnimJointIndices[11] = {
	{ 0x0000, 0x0004, 0x0014, },
	{ 0x0024, 0x0000, 0x0000, },
	{ 0x0001, 0x0000, 0x0000, },
	{ 0x0034, 0x0044, 0x0054, },
	{ 0x0064, 0x0074, 0x0084, },
	{ 0x0094, 0x00a4, 0x00b4, },
	{ 0x00c4, 0x00d4, 0x00e4, },
	{ 0x00f4, 0x0002, 0x0003, },
	{ 0x0104, 0x0114, 0x0124, },
	{ 0x0134, 0x0144, 0x0154, },
	{ 0x0164, 0x0000, 0x0003, },
};

AnimationHeader gRatSkelDamagedAnim = { { 16 }, gRatSkelDamagedAnimFrameData, gRatSkelDamagedAnimJointIndices, 4 };

