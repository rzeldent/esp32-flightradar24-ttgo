
/*******************************************************************************
* image
* filename: unsaved
* name: AIS
*
* preset name: Color R5G6B5
* data block size: 16 bit(s), uint16_t
* RLE compression enabled: no
* conversion type: Color, not_used not_used
* bits per pixel: 16
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: no
*******************************************************************************/

/*
 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/
#include <timage.h>



static const uint16_t image_data_AIS[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x64d9, 0x1bf2, 0x13f2, 0x13f3, 0x1413, 0x03d2, 0x03d2, 0x1c13, 0x13f3, 0x1412, 0x1bf2, 0x64d9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3495, 0x13f2, 0x13d2, 0x3c74, 0x7597, 0xa639, 0xc6bb, 0xd6fb, 0xd6fc, 0xc6bb, 0xa639, 0x7577, 0x3c74, 0x13f2, 0x0bf2, 0x3c73, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2d55, 0x13f2, 0x13f2, 0x6516, 0xcedb, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xe73c, 0xe73d, 0xc6bb, 0x5d16, 0x13f2, 0x13f1, 0x0555, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2c32, 0x0bf2, 0x44b5, 0xcebb, 0xe73c, 0xe73c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe75c, 0xe73c, 0xc6bb, 0x3c95, 0x0bf2, 0x2c73, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x1c32, 0x0bd2, 0x7557, 0xe71c, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73d, 0xe73c, 0xdf3c, 0x7557, 0x0bf2, 0x1c32, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x2c32, 0x0bd2, 0x85b8, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0x7d97, 0x0bd2, 0x3c53, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x2d55, 0x0bf2, 0x7557, 0xe73c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe75d, 0x6d57, 0x0bd2, 0x03ef, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x13f2, 0x44b5, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0x3c94, 0x1c12, 0x0000, 0x0000, 
    0x0000, 0x3493, 0x13f2, 0xcebb, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xbe9a, 0x0bf2, 0x34d3, 0x0000, 
    0x0000, 0x13f2, 0x6516, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xef3c, 0xe71c, 0xdf1c, 0xdf1c, 0xdf1c, 0xe73c, 0xe73c, 0xef3c, 0x5515, 0x13f2, 0x0000, 
    0x64d3, 0x13f2, 0xcedb, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xb69b, 0x4d57, 0x2d38, 0x0518, 0x0518, 0x1539, 0x3d38, 0x6577, 0x9e39, 0xbe9b, 0x0bd2, 0x7df7, 
    0x23f2, 0x3494, 0xe73c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xd6fc, 0x5d78, 0x0c75, 0x1cf8, 0x0cf8, 0x0cf8, 0x1cb6, 0x2c75, 0x4cd6, 0x7597, 0x9e1a, 0xdf1c, 0x3453, 0x1c33, 
    0x13f2, 0x7597, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xae9b, 0x24b6, 0x0c56, 0x1cf7, 0x1538, 0x4d78, 0x8dd8, 0xcedb, 0xe73c, 0xef3c, 0xe73c, 0xef3c, 0xe73c, 0x6d77, 0x1c12, 
    0x0a8c, 0xa639, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0x85f9, 0x1496, 0x1496, 0x3518, 0x65f9, 0xcefc, 0xe73c, 0xe73c, 0xe73d, 0xe73d, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xa619, 0x0a8c, 
    0x1413, 0xc6bb, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xef3c, 0xe73c, 0xcefb, 0x44f7, 0x0c76, 0x0c75, 0x6d79, 0xd71c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xbe9b, 0x1413, 
    0x03d2, 0xd6fb, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0x9e5a, 0x1496, 0x0456, 0x1cb6, 0xae7b, 0xe73c, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xcedb, 0x0bd2, 
    0x03d2, 0xd6fb, 0xcefb, 0xe73c, 0xef3c, 0xe73c, 0xef3c, 0xe73c, 0xe73d, 0xef3c, 0xdf1c, 0x9e19, 0x44f6, 0x0c75, 0x0c76, 0x6578, 0xd71c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xcebb, 0x0bd2, 
    0x1c13, 0xc6bb, 0xd6fb, 0x5d16, 0x4cb5, 0x6d57, 0x7d98, 0x85b8, 0x7557, 0x4cd6, 0x13f3, 0x0c14, 0x0c95, 0x3d18, 0xb6bb, 0xe73c, 0xe75c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xbe9b, 0x1433, 
    0x13f3, 0xa639, 0xe73c, 0xe73c, 0xcedb, 0x7d77, 0x4494, 0x2433, 0x13f4, 0x1c14, 0x3c75, 0x6db9, 0xb6bb, 0xe75c, 0xe73c, 0xe73c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0x9e39, 0x13f2, 
    0x13f2, 0x7577, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xe73c, 0xdf1c, 0xe71c, 0xe73c, 0xe73d, 0xe75c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0x6d56, 0x1bf3, 
    0x1bf2, 0x3c74, 0xe73c, 0xe73d, 0xe73c, 0xe73d, 0xe73c, 0xef3d, 0xe73c, 0xe75c, 0xe73c, 0xe75c, 0xef3c, 0xe73c, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xef3c, 0xe73c, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xdf3c, 0x2c53, 0x1bf2, 
    0x64d9, 0x0bf2, 0xc6db, 0xe75c, 0xe73d, 0xef3d, 0xe73c, 0xe73c, 0xbe7b, 0x8dd8, 0x8db8, 0xae5a, 0xef3c, 0xe75c, 0xef3c, 0x95f9, 0xb67a, 0xef3c, 0xe73d, 0xe75c, 0xef3d, 0xe73d, 0xb69b, 0x7d98, 0xef3d, 0xef3d, 0xe73d, 0xe73c, 0xef3c, 0xbe9a, 0x0bf2, 0x7df7, 
    0x0000, 0x0bf2, 0x5d15, 0xe73c, 0xe73c, 0xbe9b, 0x7577, 0xa61a, 0xa659, 0x6536, 0xa63a, 0xbe7a, 0xb65a, 0x7577, 0xb67a, 0x7557, 0xa619, 0x9e3a, 0xd6db, 0xae3a, 0x7d78, 0x9e19, 0xcebb, 0x9e19, 0xc69b, 0x7577, 0x9df8, 0xe75c, 0xe73c, 0x54f5, 0x13f2, 0x0000, 
    0x0000, 0x2c34, 0x13f2, 0xc6bb, 0xe73c, 0x3474, 0xb67a, 0x7d57, 0xa61a, 0x6537, 0x6d57, 0x8dd9, 0x2433, 0xc6bb, 0x7d77, 0x6d77, 0x6516, 0x4cb5, 0xe75c, 0x8dd9, 0x9e39, 0x2c34, 0xae5a, 0x5cf6, 0x6d57, 0xae5a, 0xe73c, 0xef3c, 0xbe7b, 0x0bd2, 0x2bf2, 0x0000, 
    0x0000, 0x0000, 0x13f1, 0x3c95, 0xdf3c, 0x3454, 0xb67a, 0x8599, 0xa639, 0x6537, 0x6d57, 0x85d9, 0x2413, 0xc69b, 0x85b8, 0x7557, 0x5cf7, 0x3454, 0xcedb, 0x2c34, 0xae59, 0x2c55, 0xae5a, 0x5d16, 0x6d57, 0xbe9b, 0xe73c, 0xdf1d, 0x3474, 0x1bf2, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x02b5, 0x0bf2, 0x6d57, 0xb67a, 0x5cf6, 0x95f9, 0xbe9b, 0x95d8, 0x95f9, 0xb67a, 0x9e39, 0x5cf6, 0xa65a, 0x9e19, 0xbe9b, 0xa619, 0x9e39, 0x7557, 0x85b8, 0x7557, 0xbe9b, 0x8dd8, 0x95d8, 0xc6db, 0xe73c, 0x6d36, 0x0bd2, 0x07ff, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x2c73, 0x0bd2, 0x8598, 0xef3c, 0xe73c, 0xe73d, 0xe73d, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xef3d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xef1c, 0xe73c, 0xef3c, 0xef3c, 0xe73d, 0xe73c, 0xe75c, 0x7d77, 0x0bd2, 0x3cb2, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x1c73, 0x0bd2, 0x6d57, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xef3c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73d, 0xe73c, 0xe75c, 0xe75c, 0xdf1c, 0x6d36, 0x0bd2, 0x2453, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3cb5, 0x0bd2, 0x3c94, 0xc69a, 0xef3c, 0xe75c, 0xe73d, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xef3c, 0xe73c, 0xbe7b, 0x3474, 0x0bd2, 0x3cb2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x03ef, 0x13f2, 0x0bf2, 0x5516, 0xbe9a, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xe73c, 0xbe9a, 0x54f5, 0x13d2, 0x1bf2, 0x07ff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3494, 0x13f2, 0x0bd2, 0x3453, 0x6d77, 0xa619, 0xbe9b, 0xcedb, 0xcebb, 0xbe9a, 0x9e19, 0x7557, 0x2c54, 0x0bf2, 0x13f2, 0x2bf2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7df7, 0x1c13, 0x1413, 0x1413, 0x1413, 0x0bd2, 0x0bd2, 0x1c13, 0x13f3, 0x1433, 0x1bd2, 0x7df7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_AIS = { image_data_AIS, 32, 32,
    16 };
