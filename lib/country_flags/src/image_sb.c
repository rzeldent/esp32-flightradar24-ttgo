
/*******************************************************************************
* image
* filename: unsaved
* name: image_sb
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



static const uint16_t image_data_image_sb[200] = {
    0x0297, 0x1b38, 0x0297, 0x0297, 0x0297, 0x2b78, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x3372, 0xbd67, 0xbd64, 
    0x1b38, 0xdf5e, 0x1b38, 0x0297, 0x1b38, 0xdf5e, 0x1b38, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x3b72, 0xbd66, 0xbd63, 0x53a5, 0x22c6, 
    0x0297, 0x0297, 0x12f7, 0xae1c, 0x12d8, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 
    0x0297, 0x0297, 0x0297, 0xa61d, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 
    0x0297, 0xdf5e, 0x0ad7, 0x0297, 0x12f7, 0xdf5e, 0x0297, 0x0297, 0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 
    0x0297, 0x4419, 0x0297, 0x0297, 0x0297, 0x4419, 0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 
    0x0297, 0x0297, 0x0297, 0x0297, 0x0297, 0x3372, 0xbd66, 0xbd63, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22e6, 0x22c6, 
    0x0297, 0x0297, 0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x1ae6, 0x22c6, 0x22c6, 0x22c6, 0x1ae6, 0x22c6, 0x22c6, 
    0x0297, 0x3b72, 0xbd66, 0xbd64, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 
    0xbd66, 0xc564, 0x53a5, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6, 0x22c6
};
const tImage image_sb = { image_data_image_sb, 20, 10,
    16 };
