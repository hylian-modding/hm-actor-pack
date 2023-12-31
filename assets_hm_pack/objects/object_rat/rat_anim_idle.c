#include "ultra64.h"
#include "global.h"

s16 gRatSkelIdleAnimFrameData[1280] = {
	0x0000, 0xfff0, 0x3fe3, 0x61ef, 0xffff, 0xbbaf, 0x04a0, 0x04a0, 0x04a0, 0x049f, 0x049e, 0x049e, 0x049c, 0x049b, 0x049a, 0x0499, 
	0x0497, 0x0496, 0x0495, 0x0493, 0x0492, 0x0491, 0x0490, 0x048f, 0x048f, 0x048e, 0x048e, 0x048f, 0x048f, 0x0490, 0x0491, 0x0492, 
	0x0493, 0x0495, 0x0496, 0x0498, 0x049a, 0x049b, 0x049d, 0x049f, 0x04a0, 0x04a2, 0x04a3, 0x04a4, 0x04a5, 0x04a5, 0x04a5, 0x04a5, 
	0x04a4, 0x04a3, 0x04a2, 0x04a0, 0x049e, 0x049c, 0x049a, 0x0498, 0x0495, 0x0493, 0x0490, 0x048e, 0x048c, 0x048a, 0x0488, 0x0487, 
	0x0486, 0x0485, 0x0485, 0x0486, 0x0487, 0x048a, 0x048d, 0x0490, 0x0492, 0x0494, 0x0495, 0x0496, 0x0497, 0x0498, 0x0499, 0x049a, 
	0x049a, 0x049b, 0x049c, 0x049c, 0x049c, 0x049d, 0x049d, 0x049d, 0x049d, 0x049d, 0x049e, 0x049e, 0x049e, 0x049e, 0x049e, 0x049e, 
	0x049e, 0x01fd, 0x01fc, 0x01fa, 0x01f7, 0x01f2, 0x01ed, 0x01e6, 0x01e0, 0x01d8, 0x01d1, 0x01c9, 0x01c1, 0x01ba, 0x01b2, 0x01ab, 
	0x01a5, 0x01a0, 0x019b, 0x0198, 0x0196, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 
	0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 
	0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0195, 0x0196, 
	0x0198, 0x019a, 0x019d, 0x01a0, 0x01a3, 0x01a7, 0x01ab, 0x01b0, 0x01b5, 0x01ba, 0x01bf, 0x01c4, 0x01c9, 0x01ce, 0x01d3, 0x01d8, 
	0x01dd, 0x01e2, 0x01e6, 0x01eb, 0x01ef, 0x01f2, 0x01f5, 0x01f8, 0x01fa, 0x01fc, 0x01fd, 0x01fd, 0xde66, 0xdd53, 0xdacb, 0xd7ea, 
	0xd5f9, 0xd600, 0xd795, 0xd9c3, 0xdaf0, 0xd965, 0xd708, 0xd5f9, 0xd64e, 0xd72d, 0xd865, 0xd9b5, 0xdaba, 0xdaf0, 0xda94, 0xda3a, 
	0xd9de, 0xd97f, 0xd919, 0xd8a9, 0xd82e, 0xd79e, 0xd6f6, 0xd63f, 0xd581, 0xd4c5, 0xd411, 0xd36c, 0xd2db, 0xd25f, 0xd1fa, 0xd1ac, 
	0xd173, 0xd14e, 0xd13b, 0xd137, 0xd140, 0xd20a, 0xd39f, 0xd51b, 0xd5c1, 0xd54b, 0xd42e, 0xd2d2, 0xd1ab, 0xd140, 0xd1b2, 0xd2ad, 
	0xd410, 0xd5a8, 0xd724, 0xd818, 0xd8a0, 0xd922, 0xd99e, 0xda14, 0xda82, 0xdaea, 0xdb4b, 0xdba5, 0xdbf8, 0xdc45, 0xdc8b, 0xdccb, 
	0xdcff, 0xdd24, 0xdd3c, 0xdd4b, 0xdd53, 0xdd58, 0xdd5b, 0xdd5e, 0xdd64, 0xdd6c, 0xdd79, 0xdd89, 0xdd9d, 0xddb4, 0xddcd, 0xdde8, 
	0xde03, 0xde1d, 0xde35, 0xde49, 0xde59, 0xde63, 0xde66, 0x83c7, 0x83ca, 0x83cc, 0x83c0, 0x83ac, 0x83ac, 0x83c8, 0x83e6, 0x83f2, 
	0x83e1, 0x83bf, 0x83ac, 0x83b1, 0x83be, 0x83cf, 0x83df, 0x83eb, 0x83f2, 0x83f8, 0x83fd, 0x83fe, 0x83f3, 0x83d7, 0x83a5, 0x8354, 
	0x82de, 0x8244, 0x8188, 0x80ae, 0x7fbb, 0x7eb4, 0x7da2, 0x7c89, 0x7b72, 0x7a63, 0x7961, 0x7870, 0x7795, 0x76d2, 0x7628, 0x759a, 
	0x7564, 0x7593, 0x75df, 0x7606, 0x75ee, 0x75b9, 0x7585, 0x7570, 0x759a, 0x75e6, 0x7628, 0x7666, 0x76a4, 0x76e1, 0x7717, 0x7744, 
	0x7772, 0x779e, 0x77ca, 0x77f5, 0x7820, 0x784a, 0x7873, 0x789b, 0x78c3, 0x78eb, 0x7911, 0x7946, 0x7994, 0x79f9, 0x7a6f, 0x7af6, 
	0x7b8a, 0x7c29, 0x7ccf, 0x7d7b, 0x7e28, 0x7ed5, 0x7f7f, 0x8023, 0x80c0, 0x8152, 0x81da, 0x8254, 0x82bf, 0x8319, 0x8363, 0x8399, 
	0x83bb, 0x83c7, 0xfa0c, 0xfa32, 0xfa8f, 0xfb02, 0xfb59, 0xfb58, 0xfb03, 0xfa90, 0xfa53, 0xfaa3, 0xfb21, 0xfb59, 0xfb49, 0xfb1d, 
	0xfadf, 0xfa9b, 0xfa65, 0xfa53, 0xfa59, 0xfa5e, 0xfa6b, 0xfa87, 0xfabb, 0xfb0f, 0xfb8b, 0xfc36, 0xfd0e, 0xfe0b, 0xff25, 0x0054, 
	0x018f, 0x02cf, 0x040d, 0x0543, 0x066d, 0x0785, 0x088a, 0x0979, 0x0a4f, 0x0b0c, 0x0bae, 0x0c25, 0x0c69, 0x0c82, 0x0c85, 0x0c7e, 
	0x0c67, 0x0c3b, 0x0bfc, 0x0bae, 0x0b78, 0x0b73, 0x0b8f, 0x0bb8, 0x0bda, 0x0bdd, 0x0bc9, 0x0bb3, 0x0b9b, 0x0b80, 0x0b64, 0x0b46, 
	0x0b27, 0x0b05, 0x0ae2, 0x0abd, 0x0a97, 0x0a6e, 0x0a2e, 0x09c1, 0x0930, 0x087f, 0x07b3, 0x06d2, 0x05e0, 0x04e3, 0x03dd, 0x02d4, 
	0x01cb, 0x00c6, 0xffc8, 0xfed6, 0xfdf1, 0xfd1e, 0xfc5d, 0xfbb4, 0xfb23, 0xfaad, 0xfa55, 0xfa1f, 0xfa0c, 0x2d23, 0x2d21, 0x2d19, 
	0x2d0d, 0x2cfd, 0x2cea, 0x2cd4, 0x2cbc, 0x2ca2, 0x2c88, 0x2c6c, 0x2c51, 0x2c36, 0x2c1c, 0x2c04, 0x2bef, 0x2bdb, 0x2bcc, 0x2bc0, 
	0x2bb8, 0x2bb5, 0x2bba, 0x2bc7, 0x2bdb, 0x2bf6, 0x2c17, 0x2c3c, 0x2c65, 0x2c90, 0x2cbe, 0x2cec, 0x2d1b, 0x2d48, 0x2d74, 0x2d9d, 
	0x2dc2, 0x2de3, 0x2dfe, 0x2e12, 0x2e1f, 0x2e23, 0x2e1f, 0x2e12, 0x2dfd, 0x2de2, 0x2dc2, 0x2d9c, 0x2d73, 0x2d47, 0x2d1a, 0x2ceb, 
	0x2cbc, 0x2c8e, 0x2c62, 0x2c39, 0x2c14, 0x2bf3, 0x2bd8, 0x2bc4, 0x2bb7, 0x2bb3, 0x2bb4, 0x2bb7, 0x2bbd, 0x2bc4, 0x2bce, 0x2bd9, 
	0x2be5, 0x2bf3, 0x2c02, 0x2c12, 0x2c23, 0x2c34, 0x2c46, 0x2c58, 0x2c6b, 0x2c7d, 0x2c90, 0x2ca1, 0x2cb3, 0x2cc4, 0x2cd4, 0x2ce3, 
	0x2cf0, 0x2cfd, 0x2d08, 0x2d11, 0x2d19, 0x2d1f, 0x2d22, 0x2d23, 0xf97f, 0xf980, 0xf982, 0xf986, 0xf98b, 0xf991, 0xf998, 0xf9a0, 
	0xf9a8, 0xf9b1, 0xf9b9, 0xf9c2, 0xf9ca, 0xf9d3, 0xf9da, 0xf9e1, 0xf9e7, 0xf9ec, 0xf9f0, 0xf9f2, 0xf9f3, 0xf9f2, 0xf9f0, 0xf9eb, 
	0xf9e6, 0xf9df, 0xf9d7, 0xf9cf, 0xf9c6, 0xf9bc, 0xf9b2, 0xf9a9, 0xf99f, 0xf996, 0xf98e, 0xf986, 0xf97f, 0xf979, 0xf975, 0xf973, 
	0xf972, 0xf973, 0xf975, 0xf979, 0xf97f, 0xf986, 0xf98d, 0xf996, 0xf99f, 0xf9a9, 0xf9b2, 0xf9bc, 0xf9c5, 0xf9ce, 0xf9d7, 0xf9df, 
	0xf9e5, 0xf9eb, 0xf9ef, 0xf9f2, 0xf9f3, 0xf9f3, 0xf9f1, 0xf9f0, 0xf9ed, 0xf9ea, 0xf9e7, 0xf9e3, 0xf9df, 0xf9da, 0xf9d5, 0xf9d0, 
	0xf9ca, 0xf9c5, 0xf9bf, 0xf9b9, 0xf9b3, 0xf9ae, 0xf9a8, 0xf9a2, 0xf99d, 0xf998, 0xf993, 0xf98f, 0xf98b, 0xf988, 0xf985, 0xf982, 
	0xf981, 0xf97f, 0xf97f, 0xfbe6, 0xfbe6, 0xfbe6, 0xfbe6, 0xfbe5, 0xfbe5, 0xfbe4, 0xfbe4, 0xfbe3, 0xfbe2, 0xfbe1, 0xfbe0, 0xfbe0, 
	0xfbdf, 0xfbde, 0xfbdd, 0xfbdd, 0xfbdc, 0xfbdc, 0xfbdb, 0xfbdb, 0xfbdb, 0xfbdb, 0xfbdb, 0xfbda, 0xfbda, 0xfbd9, 0xfbd9, 0xfbd8, 
	0xfbd7, 0xfbd7, 0xfbd6, 0xfbd5, 0xfbd4, 0xfbd3, 0xfbd2, 0xfbd2, 0xfbd1, 0xfbd1, 0xfbd0, 0xfbd0, 0xfbd0, 0xfbd1, 0xfbd1, 0xfbd2, 
	0xfbd3, 0xfbd3, 0xfbd4, 0xfbd5, 0xfbd6, 0xfbd7, 0xfbd8, 0xfbd9, 0xfbd9, 0xfbda, 0xfbda, 0xfbdb, 0xfbdb, 0xfbdb, 0xfbdc, 0xfbdc, 
	0xfbdc, 0xfbdc, 0xfbdc, 0xfbdc, 0xfbdd, 0xfbdd, 0xfbdd, 0xfbde, 0xfbde, 0xfbdf, 0xfbdf, 0xfbe0, 0xfbe0, 0xfbe1, 0xfbe2, 0xfbe2, 
	0xfbe3, 0xfbe3, 0xfbe4, 0xfbe4, 0xfbe4, 0xfbe5, 0xfbe5, 0xfbe5, 0xfbe6, 0xfbe6, 0xfbe6, 0xfbe6, 0xfbe6, 0xfbe6, 0x2d23, 0x2d21, 
	0x2d19, 0x2d0d, 0x2cfd, 0x2cea, 0x2cd4, 0x2cbc, 0x2ca2, 0x2c88, 0x2c6c, 0x2c51, 0x2c36, 0x2c1c, 0x2c04, 0x2bef, 0x2bdb, 0x2bcc, 
	0x2bc0, 0x2bb8, 0x2bb5, 0x2bba, 0x2bc7, 0x2bdb, 0x2bf6, 0x2c17, 0x2c3c, 0x2c65, 0x2c90, 0x2cbe, 0x2cec, 0x2d1b, 0x2d48, 0x2d74, 
	0x2d9d, 0x2dc2, 0x2de3, 0x2dfe, 0x2e12, 0x2e1f, 0x2e23, 0x2e1f, 0x2e12, 0x2dfd, 0x2de2, 0x2dc2, 0x2d9c, 0x2d73, 0x2d47, 0x2d1a, 
	0x2ceb, 0x2cbc, 0x2c8e, 0x2c62, 0x2c39, 0x2c14, 0x2bf3, 0x2bd8, 0x2bc4, 0x2bb7, 0x2bb3, 0x2bb4, 0x2bb7, 0x2bbd, 0x2bc4, 0x2bce, 
	0x2bd9, 0x2be5, 0x2bf3, 0x2c02, 0x2c12, 0x2c23, 0x2c34, 0x2c46, 0x2c58, 0x2c6b, 0x2c7d, 0x2c90, 0x2ca1, 0x2cb3, 0x2cc4, 0x2cd4, 
	0x2ce3, 0x2cf0, 0x2cfd, 0x2d08, 0x2d11, 0x2d19, 0x2d1f, 0x2d22, 0x2d23, 0x0680, 0x067f, 0x067d, 0x0679, 0x0674, 0x066e, 0x0667, 
	0x065f, 0x0657, 0x064e, 0x0646, 0x063d, 0x0635, 0x062c, 0x0625, 0x061e, 0x0618, 0x0613, 0x060f, 0x060d, 0x060c, 0x060d, 0x060f, 
	0x0614, 0x0619, 0x0620, 0x0628, 0x0630, 0x0639, 0x0643, 0x064d, 0x0656, 0x0660, 0x0669, 0x0671, 0x0679, 0x0680, 0x0686, 0x068a, 
	0x068c, 0x068d, 0x068c, 0x068a, 0x0686, 0x0680, 0x0679, 0x0672, 0x0669, 0x0660, 0x0656, 0x064d, 0x0643, 0x063a, 0x0631, 0x0628, 
	0x0620, 0x061a, 0x0614, 0x0610, 0x060d, 0x060c, 0x060c, 0x060e, 0x060f, 0x0612, 0x0615, 0x0618, 0x061c, 0x0620, 0x0625, 0x062a, 
	0x062f, 0x0635, 0x063a, 0x0640, 0x0646, 0x064c, 0x0651, 0x0657, 0x065d, 0x0662, 0x0667, 0x066c, 0x0670, 0x0674, 0x0677, 0x067a, 
	0x067d, 0x067e, 0x067f, 0x0680, 0x0419, 0x0419, 0x0419, 0x0419, 0x041a, 0x041a, 0x041b, 0x041b, 0x041c, 0x041d, 0x041e, 0x041f, 
	0x041f, 0x0420, 0x0421, 0x0422, 0x0422, 0x0423, 0x0423, 0x0424, 0x0424, 0x0424, 0x0424, 0x0424, 0x0425, 0x0425, 0x0426, 0x0426, 
	0x0427, 0x0428, 0x0428, 0x0429, 0x042a, 0x042b, 0x042c, 0x042d, 0x042d, 0x042e, 0x042e, 0x042f, 0x042f, 0x042f, 0x042e, 0x042e, 
	0x042d, 0x042c, 0x042c, 0x042b, 0x042a, 0x0429, 0x0428, 0x0427, 0x0426, 0x0426, 0x0425, 0x0425, 0x0424, 0x0424, 0x0424, 0x0423, 
	0x0423, 0x0423, 0x0423, 0x0423, 0x0423, 0x0422, 0x0422, 0x0422, 0x0421, 0x0421, 0x0420, 0x0420, 0x041f, 0x041f, 0x041e, 0x041d, 
	0x041d, 0x041c, 0x041c, 0x041b, 0x041b, 0x041b, 0x041a, 0x041a, 0x041a, 0x0419, 0x0419, 0x0419, 0x0419, 0x0419, 0x0419, 0xb7ed, 
	0xb822, 0xb8a7, 0xb954, 0xba01, 0xba86, 0xbabb, 0xbaa7, 0xba71, 0xba1e, 0xb9b4, 0xb939, 0xb8b4, 0xb829, 0xb79e, 0xb71a, 0xb6a2, 
	0xb63b, 0xb5eb, 0xb5b7, 0xb5a4, 0xb5a4, 0xb5a5, 0xb5a5, 0xb5a6, 0xb5a8, 0xb5a9, 0xb5ac, 0xb5af, 0xb5b3, 0xb5b7, 0xb5bd, 0xb5c3, 
	0xb5ca, 0xb5d2, 0xb5dc, 0xb5e6, 0xb5f2, 0xb5ff, 0xb60d, 0xb61d, 0xb651, 0xb6bd, 0xb74a, 0xb7e0, 0xb86a, 0xb8cf, 0xb8f6, 0xb8e8, 
	0xb8c1, 0xb889, 0xb84a, 0xb80b, 0xb7d5, 0xb7b0, 0xb7a4, 0xb7ae, 0xb7c3, 0xb7e2, 0xb807, 0xb831, 0xb85d, 0xb889, 0xb8b2, 0xb8d6, 
	0xb8f2, 0xb905, 0xb90c, 0xb90b, 0xb906, 0xb900, 0xb8f7, 0xb8ec, 0xb8df, 0xb8d0, 0xb8c0, 0xb8af, 0xb89e, 0xb88b, 0xb878, 0xb866, 
	0xb853, 0xb841, 0xb830, 0xb821, 0xb812, 0xb806, 0xb7fc, 0xb7f4, 0xb7ef, 0xb7ed, 0x0000, 0xffcd, 0xff4c, 0xfe9e, 0xfde5, 0xfd44, 
	0xfcdf, 0xfca7, 0xfc78, 0xfc51, 0xfc31, 0xfc18, 0xfc04, 0xfbf6, 0xfbec, 0xfbe6, 0xfbe3, 0xfbe2, 0xfbe2, 0xfbe3, 0xfbe3, 0xfbe7, 
	0xfbf4, 0xfc07, 0xfc22, 0xfc44, 0xfc6c, 0xfc99, 0xfccb, 0xfd02, 0xfd3d, 0xfd7c, 0xfdbe, 0xfe02, 0xfe48, 0xfe90, 0xfeda, 0xff23, 
	0xff6d, 0xffb7, 0x0000, 0x0047, 0x008d, 0x00d1, 0x0114, 0x0154, 0x0191, 0x01cb, 0x0200, 0x0233, 0x0264, 0x0295, 0x02c6, 0x02f9, 
	0x032f, 0x0369, 0x03a9, 0x03ec, 0x0432, 0x0477, 0x04bb, 0x04fb, 0x0536, 0x056a, 0x0596, 0x05b7, 0x05cd, 0x05d4, 0x05cc, 0x05b5, 
	0x0591, 0x0560, 0x0524, 0x04df, 0x0491, 0x043d, 0x03e3, 0x0385, 0x0325, 0x02c4, 0x0263, 0x0204, 0x01a8, 0x0151, 0x0101, 0x00b9, 
	0x007a, 0x0047, 0x0021, 0x0008, 0x0000, 0xffff, 0x0008, 0x001d, 0x0036, 0x004d, 0x0060, 0x006c, 0x0074, 0x007d, 0x0086, 0x0090, 
	0x009a, 0x00a3, 0x00ad, 0x00b5, 0x00bd, 0x00c4, 0x00ca, 0x00ce, 0x00d1, 0x00d1, 0x00d1, 0x00ce, 0x00ca, 0x00c5, 0x00be, 0x00b6, 
	0x00ad, 0x00a3, 0x0098, 0x008c, 0x007f, 0x0072, 0x0064, 0x0056, 0x0048, 0x0039, 0x002b, 0x001c, 0x000e, 0xffff, 0xfff1, 0xffe5, 
	0xffda, 0xffd0, 0xffc7, 0xffbf, 0xffb7, 0xffae, 0xffa5, 0xff9c, 0xff92, 0xff87, 0xff7d, 0xff72, 0xff67, 0xff5d, 0xff52, 0xff48, 
	0xff3e, 0xff35, 0xff2d, 0xff26, 0xff20, 0xff1c, 0xff19, 0xff17, 0xff16, 0xff17, 0xff1a, 0xff20, 0xff27, 0xff2f, 0xff3a, 0xff45, 
	0xff52, 0xff5f, 0xff6d, 0xff7c, 0xff8c, 0xff9b, 0xffaa, 0xffb9, 0xffc7, 0xffd4, 0xffe0, 0xffea, 0xfff3, 0xfff9, 0xfffe, 0xffff, 
};

JointIndex gRatSkelIdleAnimJointIndices[11] = {
	{ 0x0000, 0x0006, 0x0001, },
	{ 0x0061, 0x0000, 0x0000, },
	{ 0x0002, 0x0000, 0x0000, },
	{ 0x0003, 0x0004, 0x0004, },
	{ 0x0005, 0x0004, 0x0004, },
	{ 0x0003, 0x0004, 0x0004, },
	{ 0x0005, 0x0004, 0x0004, },
	{ 0x00bc, 0x0117, 0x0172, },
	{ 0x01cd, 0x0228, 0x0283, },
	{ 0x02de, 0x0339, 0x0394, },
	{ 0x03ef, 0x044a, 0x04a5, },
};

AnimationHeader gRatSkelIdleAnim = { { 91 }, gRatSkelIdleAnimFrameData, gRatSkelIdleAnimJointIndices, 6 };

