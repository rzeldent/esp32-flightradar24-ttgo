
/*******************************************************************************
* image
* filename: unsaved
* name: image_bs
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



static const uint16_t image_data_image_bs[200] = {
    0x00e4, 0x034f, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 
    0x0000, 0x0000, 0x01a7, 0x034f, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03d1, 0x03b1, 0x03d1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x024a, 0x03b1, 0x03b1, 0x03d1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18e1, 0x7c07, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x49e1, 0xdd64, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x49e1, 0xdd65, 0xfe25, 0xfe25, 0xfe45, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 0xfe25, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1901, 0x7c06, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 0xad69, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x024a, 0x03b1, 0x03b1, 0x03d1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03d1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 
    0x0000, 0x0000, 0x01a7, 0x034f, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 
    0x00e4, 0x034f, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1, 0x03b1
};
const tImage country_flag_BS = { image_data_image_bs, 20, 10,
    16 };
