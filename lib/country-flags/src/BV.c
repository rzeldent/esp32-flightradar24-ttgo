
/*******************************************************************************
* image
* filename: unsaved
* name: image_bv
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



static const uint16_t image_data_image_bv[300] = {
    0xe945, 0xe945, 0xe945, 0xf145, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xd6bc, 0xf1e7, 0xe945, 0xe945, 0xf145, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xf165, 0xe945, 0xe945, 0xfcf3, 0x5bb3, 0x012c, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe965, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb4, 0x012d, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xf165, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xf165, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xf145, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xf3ef, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3ef, 0xfe18, 0x5bb4, 0x012d, 0xcebc, 0xf3cf, 0xf3ef, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 
    0x9517, 0x9517, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x3290, 0x012d, 0x7455, 0x8d17, 0x8d17, 0x8d17, 0x9517, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 
    0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x014c, 0x012d, 0x014c, 0x012d, 0x014c, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 0x012d, 
    0x9517, 0x8d17, 0x8d17, 0x8d17, 0x94f7, 0x8d17, 0x3290, 0x012c, 0x7455, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 0x8d17, 
    0xf3cf, 0xf3cf, 0xf3cf, 0xf3ef, 0xf3cf, 0xfe18, 0x5bb3, 0x012d, 0xd6bc, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3ef, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 0xf3cf, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xd6bc, 0xe9e8, 0xf165, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x014d, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xcebc, 0xf1e8, 0xe945, 0xf145, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x014d, 0xd6bc, 0xf1e8, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 
    0xe945, 0xe945, 0xf165, 0xe945, 0xe945, 0xf4f3, 0x5bb3, 0x012d, 0xd6bc, 0xf1e7, 0xe945, 0xe945, 0xe945, 0xe945, 0xe945, 0xe965, 0xe945, 0xe945, 0xe945, 0xe945
};
const tImage country_flag_BV = { image_data_image_bv, 20, 15,
    16 };
