
/*******************************************************************************
* image
* filename: unsaved
* name: ASH
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



static const uint16_t image_data_ASH[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x1082, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0841, 0x94b2, 0xce59, 0x73ae, 0x0000, 0x0841, 0xa555, 0xc638, 0x630c, 0x9cf3, 0xc638, 0xc638, 0xc638, 0xc618, 0x630c, 0x2965, 0xc618, 0xe75d, 0xdefb, 0xad55, 0x2965, 0x0000, 0x0000, 0x6b6d, 0xc659, 0x632c, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0x8451, 0xce79, 0xd6db, 0x18c3, 0x4a69, 0xc638, 0xad75, 0x7bef, 0xa514, 0xc638, 0xce9a, 0xdefb, 0xd6db, 0x7bf0, 0xce9a, 0xc638, 0xbdf7, 0xce79, 0xc618, 0x94b2, 0x0000, 0x0861, 0xb5b7, 0xadb6, 0xa555, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0x8c92, 0xb5d7, 0xd6db, 0x94b3, 0xc618, 0x9cf3, 0xad75, 0x8410, 0xad75, 0xc618, 0x7bf0, 0x5acb, 0x5acb, 0x4a69, 0xe73c, 0xdf1c, 0x52aa, 0x3186, 0x6b8e, 0x18c3, 0x0000, 0x4208, 0xceba, 0x9d34, 0xb5d7, 0x3186, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0xa535, 0xbe18, 0xc638, 0xf79e, 0xdefb, 0xb5b6, 0xc639, 0x8430, 0xbdf7, 0xbe18, 0xdedb, 0xdedb, 0xce79, 0x528a, 0x8451, 0xa554, 0xe73c, 0xef7d, 0x9cf3, 0x18c3, 0x0000, 0xa555, 0xce9a, 0x94b2, 0xbe18, 0x73af, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0xb5b6, 0xce59, 0x8430, 0xbdd7, 0xce99, 0x8c92, 0xd6ba, 0x8451, 0xce79, 0xad96, 0xb5d7, 0xc618, 0xce59, 0x52aa, 0x2104, 0x8c51, 0xb5b6, 0xc618, 0xe73c, 0xbdf7, 0x18e3, 0xef7d, 0xce79, 0x4a49, 0xe75d, 0xb5b7, 0x0841, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0xbdf7, 0xd6bb, 0x4208, 0x8451, 0x8430, 0x8430, 0xe75d, 0x8c72, 0xdedb, 0xbe18, 0x73ae, 0x4a69, 0x4a69, 0x2986, 0x39c7, 0x9492, 0x31a6, 0x8c71, 0xce9a, 0xdefb, 0x632c, 0xef9e, 0xe71c, 0xdefb, 0xdefc, 0xc618, 0x4229, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0861, 0xdefb, 0xe75d, 0x4208, 0x3186, 0x0861, 0x94b2, 0xe75d, 0x94d3, 0xd6ba, 0xd6db, 0xf7be, 0xf7be, 0xe73c, 0x8c72, 0xbdd7, 0xdedb, 0xef7d, 0xf79e, 0xb5b6, 0x8c51, 0xc638, 0xce79, 0xa555, 0xad75, 0xa575, 0xb5b7, 0x8c71, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0841, 0xb5b6, 0xbdf7, 0x31a6, 0x0000, 0x0000, 0x73ae, 0xbdf7, 0x73ae, 0x9cf3, 0xb5d7, 0xbdd7, 0xc618, 0xc618, 0x632c, 0x2965, 0x9cd3, 0xbe18, 0xbdf8, 0x94b2, 0x39c7, 0xbe18, 0xa555, 0x1082, 0x0000, 0x18c3, 0xb5d7, 0xa535, 0x0861, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x528a, 0x0000, 0x0000, 0x4229, 0x4a69, 0x39c7, 0x39c7, 0x39e8, 0x2945, 0x0000, 0x0000, 0x0000, 0x2945, 0x39c7, 0x0841, 0x0000, 0x0000, 0x3a08, 0x5acb, 0x39c7, 0x39c7, 0x2124, 0x4208, 0x3186, 0x4208, 0x0020, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x2145, 0x2124, 0x10a2, 0x0000, 0x4a49, 0x31a7, 0x0000, 0x0000, 0x18c3, 0x31a6, 0x0000, 0x0000, 0x0000, 0x2945, 0x2965, 0x39c7, 0x0000, 0x0000, 0x4208, 0x31a7, 0x0000, 0x0000, 0x2945, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x31a6, 0x0000, 0x31a6, 0x0000, 0x4a49, 0x31a7, 0x0000, 0x0000, 0x2945, 0x3186, 0x0000, 0x0000, 0x0000, 0x2945, 0x2945, 0x0861, 0x2104, 0x0000, 0x4208, 0x4a6a, 0x2124, 0x2124, 0x1082, 0x4228, 0x2104, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x1082, 0x2965, 0x10a3, 0x39e7, 0x0000, 0x4a49, 0x4a6a, 0x31a7, 0x528a, 0x10c3, 0x2945, 0x0000, 0x0000, 0x0000, 0x2945, 0x2945, 0x0000, 0x2945, 0x0841, 0x4208, 0x4a49, 0x18e3, 0x18e3, 0x0020, 0x0000, 0x18c3, 0x39e7, 0x0841, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x31a6, 0x2945, 0x2945, 0x2965, 0x2966, 0x4a49, 0x31a7, 0x0000, 0x0861, 0x2945, 0x2945, 0x0000, 0x0000, 0x0000, 0x2945, 0x2945, 0x0000, 0x0000, 0x31a6, 0x4208, 0x31a7, 0x0000, 0x0000, 0x0841, 0x0000, 0x0000, 0x1082, 0x1082, 0x0000, 
    0x0000, 0x0000, 0x0020, 0x2945, 0x0000, 0x0000, 0x0000, 0x2965, 0x4208, 0x2986, 0x0000, 0x0000, 0x2104, 0x3186, 0x2966, 0x2966, 0x2945, 0x2124, 0x2124, 0x0000, 0x0000, 0x0861, 0x4249, 0x4a6a, 0x2966, 0x2966, 0x2966, 0x39e7, 0x2945, 0x39c7, 0x0020, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0020, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x0020, 0x0020, 0x0020, 0x0000, 0x0841, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_ASH = { image_data_ASH, 32, 32,
    16 };
