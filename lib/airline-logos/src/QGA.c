
/*******************************************************************************
* image
* filename: unsaved
* name: QGA
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



static const uint16_t image_data_QGA[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x6063, 0x80c4, 0x78a3, 0x88c4, 0x78a4, 0x78a4, 0x80c4, 0x78a4, 0x4882, 0x0000, 0x0000, 0x3882, 0x80c4, 0x80c4, 0x78a3, 0x70a3, 0x88c4, 0x70a3, 0x70a3, 0x80a4, 0x0000, 0x0000, 0x0000, 0x88a4, 0x78a3, 0x88c4, 0x78a4, 0x78a4, 0x78a4, 0x88c4, 0x70a3, 0x7800, 
    0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90e4, 0x0000, 0x0000, 0x90c5, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x0000, 0x0000, 0x9904, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x0000, 
    0xf800, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0xf800, 0x0000, 0xa800, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x8904, 0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x88c4, 0x0000, 
    0x0000, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90a5, 0x0000, 0x0000, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x0000, 0x0000, 0x7945, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0xa800, 0x0000, 
    0x0000, 0x88e4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0xa800, 0x0000, 0x7800, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x90c5, 0x0000, 0x0000, 0x88c4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x88c4, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x0000, 0x0000, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0xf800, 0x0000, 0x7800, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x7945, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x88c4, 0x7945, 0x0000, 0xf800, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x88a5, 0x0000, 0x0000, 0x88a5, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x90e5, 0x88c4, 0x90c5, 0x88c4, 0x0000, 0x0000, 0x88e4, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0xf800, 0x0000, 0x7800, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x78c6, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x90c5, 0x88c4, 0x9904, 0x0000, 0x0000, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x0000, 0x0000, 0x90c4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x90c5, 0x88c4, 0x0000, 0x0000, 0x9084, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x7807, 0x0000, 0x0000, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x88e4, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x9806, 0x8884, 0x0000, 0x0000, 0x90c5, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x0000, 0x0000, 0x88e3, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7807, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x88c4, 0x0000, 0x0000, 0x90c4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x88c5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x90c4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x0000, 0x0000, 0x98e3, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x7800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88a4, 0x0000, 0x0000, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x90c4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x88e5, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0xf800, 0x0000, 0x7800, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x9986, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x88e4, 0x0000, 0x0000, 0x90c4, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x88c5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0xa800, 0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90a5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x88c4, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x90c4, 0x0000, 0x0000, 0x88c4, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x7807, 0x0000, 0x0000, 0x90c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x88e5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c4, 0x0000, 0x0000, 0x9904, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8884, 0x88c4, 0x90c5, 0x90c4, 0x88e5, 0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x90e5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x90c5, 0x90c5, 0x88c4, 0x0000, 0x0000, 0x98e3, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c4, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x88c4, 0x90c5, 0x90c5, 0x0000, 0x0000, 0x88c5, 0x88c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x90c5, 0x88c5, 0x90c5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x98c6, 0x90c5, 0x0000, 0x0000, 0xa800, 0x88c5, 0x88c5, 0x88c5, 0x88c5, 0x88c5, 0x88c5, 0x88c5, 0x90c5, 0xa80a, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9986, 0x0000, 0x0000, 0x7800, 0x88a4, 0x90e4, 0x90e4, 0x90e4, 0x90e4, 0x90e4, 0x90e4, 0x90c4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_QGA = { image_data_QGA, 32, 32,
    16 };
