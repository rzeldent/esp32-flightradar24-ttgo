
/*******************************************************************************
* image
* filename: unsaved
* name: image_af
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



static const uint16_t image_data_image_af[260] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4040, 0xd102, 0xd102, 0xd102, 0xd0e2, 0xd102, 0xd102, 0x42c5, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4040, 0xd102, 0xd102, 0xd163, 0xd163, 0xd163, 0xd102, 0x42c5, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4040, 0xd9e5, 0xda47, 0xd9c5, 0xd102, 0xd163, 0xd9e5, 0x42c5, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2104, 0x93ae, 0xd0e2, 0xd163, 0xd9e5, 0xd163, 0xd163, 0xd102, 0x9d12, 0x1408, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x630c, 0x5944, 0xd102, 0xdac9, 0xd163, 0xd163, 0xd101, 0xd102, 0x6bca, 0x5d70, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x630c, 0x5944, 0xdac9, 0xec91, 0xe32b, 0xe32b, 0xe32b, 0xdac9, 0x6bca, 0x5d70, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9492, 0x7228, 0xf5d6, 0xed33, 0xdac9, 0xd9e5, 0xe40f, 0xed33, 0x742b, 0x9634, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9d12, 0x8b2c, 0xda47, 0xdac9, 0xd163, 0xda47, 0xdac9, 0xe32b, 0x8ccf, 0xa676, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3185, 0x7228, 0xda47, 0xe40f, 0xdac9, 0xe40f, 0xec91, 0xdac9, 0x742b, 0x44cc, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xacb2, 0xdac9, 0xe3ad, 0xe32b, 0xe32b, 0xec91, 0xdaa9, 0xa572, 0x1408, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5944, 0xec91, 0xda47, 0xdac9, 0xda47, 0xda47, 0xec91, 0x5347, 0x03c7, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x50c2, 0xd102, 0xdac9, 0xd102, 0xd102, 0xdac9, 0xd102, 0x5347, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4040, 0xd102, 0xd102, 0xd102, 0xd101, 0xd102, 0xd102, 0x42c5, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6, 0x03c6
};
const tImage image_af = { image_data_image_af, 20, 13,
    16 };
