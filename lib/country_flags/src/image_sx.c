
/*******************************************************************************
* image
* filename: unsaved
* name: image_sx
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



static const uint16_t image_data_image_sx[260] = {
    0xf535, 0xd925, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffff, 0xff1c, 0xe249, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffff, 0xffff, 0xffff, 0xebf0, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xf5b7, 0xd925, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffff, 0xff1c, 0xe507, 0xdc66, 0xed8c, 0xff1c, 0xe249, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffff, 0xd535, 0x4d36, 0x9598, 0x6d9b, 0xfe9a, 0xffff, 0xec51, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8c3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 0xd8a3, 
    0xffda, 0xdd32, 0xa61a, 0xc67a, 0x95fb, 0xfe8d, 0xffff, 0xffff, 0xb495, 0x690a, 0x690a, 0x690a, 0x68ea, 0x690a, 0x690a, 0x690a, 0x690a, 0x690a, 0x690a, 0x690a, 
    0xf733, 0xe5f2, 0x94b5, 0xc67a, 0x94b5, 0xf6ad, 0xffff, 0x84b8, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 
    0xffff, 0xf733, 0xff2b, 0xfeef, 0xeecc, 0xc634, 0x42f4, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 
    0xffff, 0xffff, 0xffff, 0xffff, 0xadfb, 0x09b1, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 
    0xffff, 0xffff, 0xffff, 0x7437, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 
    0xffff, 0xe73e, 0x3293, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 
    0xa57a, 0x09b1, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150, 0x0150
};
const tImage image_sx = { image_data_image_sx, 20, 13,
    16 };
