
/*******************************************************************************
* image
* filename: unsaved
* name: MGL
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



static const uint16_t image_data_MGL[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3bf7, 0x2230, 0x6b76, 0x2252, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2a51, 0x09af, 0x11cf, 0x3271, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2a51, 0x1a10, 0x2230, 0x4af3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x63f6, 0x09af, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x096e, 0x098e, 0x098e, 0x098e, 0x098e, 0x19ef, 0x3291, 0x11cf, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x11af, 0x52b5, 
    0x2a51, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x1a10, 0x19cf, 0x2a71, 0x018e, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09af, 0x2210, 0x0000, 
    0x6b95, 0x19cf, 0x09af, 0x09af, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x09ae, 0x098f, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x09af, 0x11cf, 0x3ad3, 0x0000, 0x0000, 
    0x0000, 0x3ab3, 0x001f, 0x3251, 0x098e, 0x09ae, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x2210, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x2230, 0x42d3, 0x03ef, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x3291, 0x09af, 0x19ef, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x19ef, 0x2aaf, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4b33, 0x7bef, 0x2a31, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x19f0, 0x52b5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x52f4, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09af, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x2a71, 0x3291, 0x6b95, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x1a10, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x018e, 0x018e, 0x018e, 0x018e, 0x018e, 0x018e, 0x018e, 0x018e, 0x098e, 0x2230, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1a10, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09af, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x098e, 0x3a92, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x19f0, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x11cf, 0x09ae, 0x098e, 0x098e, 0x018e, 0x19cf, 0x02aa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001f, 0x2210, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x11ef, 0x5352, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4af3, 0x09af, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09af, 0x09ae, 0x19f0, 0x39ef, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x11af, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x19ef, 0x19f0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x42d2, 0x098e, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x098e, 0x2230, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7395, 0x11af, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09ae, 0x09af, 0x2a11, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3ab2, 0x098e, 0x09ae, 0x09ae, 0x098e, 0x11af, 0x3291, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x018e, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7bef, 0x2230, 0x098e, 0x098e, 0x19ef, 0x3a71, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x098e, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xad55, 0x19ef, 0x11cf, 0x3333, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01ef, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5395, 0x2231, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_MGL = { image_data_MGL, 32, 32,
    16 };
