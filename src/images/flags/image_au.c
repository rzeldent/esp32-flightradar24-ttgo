
/*******************************************************************************
* image
* filename: unsaved
* name: image_au
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



static const uint16_t image_data_image_au[200] = {
    0xcbf3, 0xc578, 0x42b1, 0x010d, 0xd330, 0xd330, 0x010d, 0x5a4f, 0xcbf3, 0xc578, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 
    0x42d1, 0x83b3, 0xdcf6, 0xd61a, 0xe371, 0xe371, 0xdcf6, 0xd61a, 0x7415, 0x42d1, 0x010d, 0x010d, 0x010d, 0x010d, 0x42d1, 0x42d1, 0x010d, 0x010d, 0x00ed, 0x010d, 
    0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0xe005, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 
    0x42b2, 0x7415, 0xd61a, 0xdcf6, 0xe371, 0xe371, 0xd61a, 0xdcf6, 0x83b3, 0x42d1, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x00ed, 0x3250, 0x7415, 0x010d, 0x010d, 
    0xc578, 0xcbf3, 0x5a4f, 0x010d, 0xd330, 0xd330, 0x010d, 0x42d1, 0xc598, 0xcbf3, 0x010d, 0x010d, 0xa578, 0x010d, 0x010d, 0x010d, 0x010d, 0x116e, 0x010d, 0x010d, 
    0x010d, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x21ef, 0x19cf, 0x010d, 0x010d, 0x010d, 
    0x010d, 0x010d, 0x010d, 0x116e, 0x5333, 0x5333, 0x116e, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 
    0x010d, 0x010d, 0x010d, 0x010d, 0xe73d, 0xe73d, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 
    0x010d, 0x010d, 0x010d, 0x010d, 0x3250, 0x3250, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x5333, 0x5333, 0x010d, 0x010d, 0x010d, 0x010d, 
    0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d, 0x00ed, 0x010d, 0x010d, 0x010d, 0x010d, 0x010d
};
const tImage image_au = { image_data_image_au, 20, 10,
    16 };
