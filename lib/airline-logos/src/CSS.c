
/*******************************************************************************
* image
* filename: unsaved
* name: CSS
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



static const uint16_t image_data_CSS[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0861, 0x1082, 0x1082, 0x1082, 0x0841, 0x0841, 0x1082, 0x1082, 0x1082, 0x1082, 0x0020, 0x0000, 0x0861, 0x1082, 0x1082, 0x1082, 0x0841, 0x0020, 0x0861, 0x0020, 0x1082, 0x1082, 0x1082, 0x0861, 0x0000, 0x0861, 0x0841, 0x0000, 0x0000, 0x0000, 0x0861, 0x0020, 
    0xdefb, 0xef5d, 0xef5d, 0xef5d, 0x8410, 0x9492, 0xef5d, 0xef5d, 0xef5d, 0xdedb, 0x10a2, 0x0020, 0xbdd7, 0xef5d, 0xef5d, 0xef5d, 0xad75, 0x632c, 0xc638, 0x4a69, 0xef5d, 0xef5d, 0xef5d, 0xe71c, 0x31a6, 0xc638, 0x6b6d, 0x0020, 0x0000, 0x1082, 0xce59, 0x4a69, 
    0xf7be, 0xa514, 0x73ae, 0x73ae, 0x4208, 0xa514, 0xd6ba, 0x738e, 0x73ae, 0x738e, 0x0861, 0x0020, 0xc638, 0xc638, 0x738e, 0xbdd7, 0xd6ba, 0x6b6d, 0xdedb, 0x528a, 0xf7be, 0x7bef, 0x7bef, 0xf7be, 0x528a, 0xd6ba, 0x738e, 0x0000, 0x0000, 0x1082, 0xdedb, 0x528a, 
    0xf79e, 0xdefb, 0xce79, 0xce59, 0x528a, 0xa514, 0xf79e, 0xce79, 0xce79, 0x6b4d, 0x0000, 0x0020, 0xc638, 0xe73c, 0xce79, 0xe71c, 0xdedb, 0x528a, 0xd6ba, 0x528a, 0xf7be, 0x9cf3, 0xa534, 0xf7be, 0x528a, 0xdedb, 0x73ae, 0x0000, 0x0000, 0x1082, 0xdedb, 0x528a, 
    0x6b6d, 0xad55, 0xad55, 0xe73c, 0x8c51, 0xa514, 0xe71c, 0x9cd3, 0x9cd3, 0x4a69, 0x0000, 0x0020, 0xc638, 0xd69a, 0x9cd3, 0xc618, 0xd6ba, 0x528a, 0xdedb, 0x528a, 0xffdf, 0xc618, 0xf7be, 0xd69a, 0x31a6, 0xd6ba, 0x738e, 0x0000, 0x0000, 0x1082, 0xdefb, 0x528a, 
    0x94b2, 0x9cd3, 0x9cd3, 0xe73c, 0x8c51, 0xa514, 0xad75, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0xc638, 0x8c51, 0x0000, 0x738e, 0xdedb, 0x528a, 0xd6ba, 0x528a, 0xef7d, 0x10a2, 0xad55, 0xa534, 0x1082, 0xe71c, 0xc638, 0x9cf3, 0x9cd3, 0x31a6, 0xdefb, 0x528a, 
    0xd69a, 0xd6ba, 0xd6ba, 0xd6ba, 0x6b6d, 0x8c51, 0x9492, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0xad55, 0x738e, 0x0000, 0x632c, 0xb5b6, 0x4228, 0xb5b6, 0x4228, 0xce79, 0x0861, 0x31a6, 0xce79, 0x31a6, 0xc638, 0xd6ba, 0xd6ba, 0xd69a, 0x4208, 0xbdd7, 0x4228, 
    0x0861, 0x0861, 0x0861, 0x0861, 0x0020, 0x0841, 0x0841, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0841, 0x0841, 0x0000, 0x0020, 0x0861, 0x0020, 0x0861, 0x0020, 0x0861, 0x0000, 0x0020, 0x0861, 0x0020, 0x0861, 0x0861, 0x0861, 0x0861, 0x0020, 0x0861, 0x0020, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x4a49, 0x6b4d, 0x1082, 0x4228, 0x738e, 0x8c51, 0x9cd3, 0x9cf3, 0x9cf3, 0x8c51, 0x0841, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x738e, 0x630c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18e3, 0x4a69, 0xa514, 0x632c, 0x18e3, 0x0861, 
    0x73ae, 0xbdd7, 0xd69a, 0x8c71, 0xb596, 0x738e, 0xc638, 0xce79, 0x7bef, 0x6b6d, 0x0841, 0x0000, 0x0000, 0x0841, 0x4228, 0x4a49, 0x4a49, 0xce79, 0xb596, 0x4a49, 0x4a49, 0x4208, 0x0020, 0x0000, 0x0000, 0x0000, 0x8c51, 0xf7be, 0xe73c, 0xf7be, 0xce59, 0xce59, 
    0x7bcf, 0xbdf7, 0xe73c, 0x9492, 0xa534, 0x8c51, 0xef5d, 0xdedb, 0xbdd7, 0x73ae, 0x0000, 0x0000, 0x0020, 0x2104, 0xce79, 0xdedb, 0xdedb, 0xf79e, 0xef7d, 0xdedb, 0xdedb, 0xbdf7, 0x0841, 0x0000, 0x0000, 0x0000, 0x8c51, 0xd69a, 0x8410, 0xe73c, 0xa534, 0x6b6d, 
    0x7bcf, 0xbdf7, 0xe73c, 0x94b2, 0xa534, 0xbdd7, 0xad75, 0x8410, 0xad55, 0x9cf3, 0x0000, 0x0000, 0x0000, 0x0020, 0x1082, 0x1082, 0x1082, 0xbdd7, 0x9cd3, 0x1082, 0x1082, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x8c71, 0xc618, 0xad55, 0xf7be, 0x8c51, 0xce59, 
    0x7bcf, 0xbdf7, 0xe73c, 0x94b2, 0xa534, 0xbdd7, 0x94b2, 0xdefb, 0x8c71, 0xa514, 0x0000, 0x0000, 0x0020, 0x0000, 0x4228, 0x94b2, 0x9492, 0xe71c, 0xd69a, 0x9492, 0x9492, 0x3186, 0x0000, 0x0000, 0x0000, 0x1082, 0xc638, 0xe71c, 0x9cd3, 0xf79e, 0x8c71, 0xef5d, 
    0x73ae, 0xbdf7, 0xef5d, 0x94b2, 0xa534, 0xbdd7, 0x9cd3, 0xe71c, 0x8c71, 0xa514, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x8430, 0x8c51, 0xdedb, 0xce79, 0x8c51, 0x8c51, 0x3186, 0x0000, 0x0000, 0x0000, 0x10a2, 0xce59, 0xef5d, 0xa534, 0xef7d, 0x8c71, 0xef5d, 
    0x7bcf, 0xbdf7, 0xe73c, 0x94b2, 0xa534, 0xbdd7, 0x9cd3, 0xe71c, 0x8c71, 0xa514, 0x0000, 0x0000, 0x0000, 0x0020, 0x0861, 0x0861, 0x0861, 0xbdd7, 0x9cd3, 0x0861, 0x0861, 0x0861, 0x0020, 0x0000, 0x0000, 0x0000, 0x8c71, 0xce79, 0xa534, 0xef7d, 0x8c71, 0xef5d, 
    0x8c71, 0xb596, 0xe73c, 0x9492, 0xad55, 0x7bcf, 0x73ae, 0xe73c, 0x6b4d, 0x6b4d, 0x0000, 0x0000, 0x0000, 0x4a49, 0xd6ba, 0xd69a, 0xd6ba, 0xf79e, 0xef5d, 0xd69a, 0xd69a, 0xd6ba, 0x2965, 0x0000, 0x0000, 0x0000, 0x8c71, 0xc618, 0x6b6d, 0xef7d, 0x8c51, 0xef5d, 
    0xd6ba, 0x6b4d, 0x39e7, 0x7bcf, 0xad55, 0x5aeb, 0xc618, 0xef7d, 0xb5b6, 0x52aa, 0x0000, 0x0020, 0x0000, 0x1082, 0x3186, 0x3186, 0x3186, 0xc618, 0xad75, 0x2965, 0x3186, 0x3186, 0x0841, 0x0000, 0x0000, 0x0841, 0xb5b6, 0xbdd7, 0x4a69, 0xef5d, 0xb596, 0xf7be, 
    0x632c, 0x0841, 0x0000, 0x4a69, 0x6b6d, 0x73ae, 0x73ae, 0x2965, 0x8410, 0x632c, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x7bef, 0x632c, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x94b2, 0x528a, 0x738e, 0x9cf3, 0x6b6d, 0x9cd3, 
    0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_CSS = { image_data_CSS, 32, 32,
    16 };
