
/*******************************************************************************
* image
* filename: unsaved
* name: image_zw
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



static const uint16_t image_data_image_zw[200] = {
    0xa534, 0x0aa1, 0x0320, 0x0320, 0x0300, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 
    0xffff, 0xd69a, 0x73c6, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 
    0xffff, 0xffff, 0xef1c, 0x9c4c, 0xed40, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 
    0xffff, 0xef7d, 0xe388, 0xffff, 0xb514, 0xa882, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 
    0xf679, 0xd986, 0xdcc0, 0xe264, 0xf679, 0xd69a, 0x4985, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 
    0xffff, 0xd42c, 0xc4c0, 0xe388, 0xffff, 0xd69a, 0x4985, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 0x3800, 
    0xffff, 0xf679, 0xffff, 0xf679, 0xb514, 0xa882, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 0xd000, 
    0xffff, 0xffff, 0xef7d, 0x9c4c, 0xed40, 0xfda0, 0xfd80, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 0xfda0, 
    0xffff, 0xd69a, 0x73c6, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 0x9500, 
    0xa534, 0x0ac1, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320, 0x0320
};
const tImage image_zw = { image_data_image_zw, 20, 10,
    16 };
