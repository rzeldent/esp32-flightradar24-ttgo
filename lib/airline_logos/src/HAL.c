
/*******************************************************************************
* image
* filename: unsaved
* name: HAL
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



static const uint16_t image_data_HAL[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb8b1, 0xc8b1, 0xc8b1, 0xc0b1, 0xc0b1, 0xc8b1, 0xb8b1, 0xb0d1, 0xa8f1, 0xb0d1, 0xe968, 0xe987, 0xe987, 0xe967, 0xe967, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc0d0, 0xc0d1, 0xc0d1, 0xc0d1, 0xc0d1, 0xb0f1, 0x8151, 0x5192, 0x41b2, 0x41b2, 0x41b2, 0x79af, 0xe967, 0xe987, 0xe987, 0xe987, 0xe987, 0xe967, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb8f1, 0xb8f1, 0xb8f1, 0xb8f1, 0xb8f1, 0x9931, 0x49b2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x49d1, 0xd988, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe967, 0xe967, 0xf187, 0xe168, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb0f1, 0xb0f1, 0xb0f1, 0xb0f1, 0xb0f1, 0xa111, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x51b1, 0xc989, 0xd189, 0xc989, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa931, 0xb111, 0xb111, 0xb111, 0xb111, 0xb111, 0x7172, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0xc189, 0xe987, 0xe987, 0xe987, 0xb98a, 0xe187, 0xd188, 0xc18a, 0xd188, 0xe987, 0xe987, 0xe987, 0xe987, 0xf9e7, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xa0f0, 0xa931, 0xa931, 0xa931, 0xa931, 0xa931, 0xa931, 0x5992, 0x41d1, 0x41d2, 0x41d2, 0x51b1, 0xe987, 0xe987, 0xe987, 0xe987, 0xc18a, 0xa98b, 0x79ae, 0x49d1, 0xb98a, 0xe987, 0xe987, 0xe987, 0xe987, 0xe927, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xa131, 0xa131, 0xa131, 0xa131, 0xa131, 0xa131, 0xa131, 0x0000, 0x0000, 0x000f, 0x41b2, 0xb18b, 0xe987, 0xe987, 0xe987, 0xe987, 0xc189, 0x49d1, 0x69af, 0x91ad, 0xe987, 0xe987, 0xe987, 0xe967, 0xe967, 0xfaaa, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x9951, 0x9951, 0xa151, 0xa151, 0xa151, 0xa151, 0xa151, 0x6992, 0x39b2, 0x41d1, 0x52b5, 0x0000, 0x0000, 0xe987, 0xe987, 0xe987, 0xe987, 0xe188, 0xb98a, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe967, 0xe186, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x9951, 0x9951, 0x9951, 0x9951, 0x9951, 0x9951, 0x8971, 0x41d2, 0x41b2, 0x41b2, 0x41b2, 0x0000, 0x0000, 0xe987, 0xe967, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe967, 0xf9e7, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x9151, 0x9171, 0x9171, 0x9171, 0x9171, 0x9151, 0x7192, 0x41d2, 0x41b2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xe987, 0xfaaa, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x78ef, 0x8971, 0x9171, 0x9171, 0x9171, 0x9171, 0x9171, 0x8971, 0x41d2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe967, 0xe987, 0xe987, 0xe987, 0xe987, 0xd988, 0xb18a, 0xe987, 0xe987, 0xe987, 0xe967, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x8991, 0x8971, 0x8971, 0x8971, 0x8971, 0x8971, 0x8971, 0x8971, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe167, 0xb98a, 0xe987, 0xe987, 0xe987, 0xc18a, 0x41d2, 0x59b0, 0x69af, 0x51b1, 0x51d1, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x7991, 0x8171, 0x8171, 0x8171, 0x8171, 0x8171, 0x8171, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41d2, 0x41b2, 0x81ad, 0x91ad, 0x69af, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x7951, 0x8191, 0x8191, 0x8191, 0x8191, 0x8192, 0x7951, 0x71d1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x9993, 0x7992, 0x7992, 0x7992, 0x7992, 0x7991, 0x7992, 0x7991, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41b1, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x7991, 0x7192, 0x7192, 0x7192, 0x7191, 0x7192, 0x7192, 0x7192, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x7192, 0x7192, 0x7192, 0x7192, 0x7192, 0x7191, 0x7191, 0x7191, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39d1, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x69b2, 0x6992, 0x6992, 0x6992, 0x6992, 0x6991, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39d1, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x4a52, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x6992, 0x69b2, 0x69b2, 0x6992, 0x69f2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x79ef, 0x0000, 0x0000, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x6932, 0x6192, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x6193, 0x6932, 0x5992, 0x61b2, 0x6192, 0x61b1, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b2, 0x61b1, 0x0000, 0x0000, 0x0000, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x0000, 0x0000, 0x0000, 0x39d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x39f1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5992, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x59b2, 0x0000, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x41b2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39ef, 0x51b2, 0x51b2, 0x51b2, 0x51b2, 0x51b2, 0x51b2, 0x4991, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x39f7, 0x49d2, 0x51b2, 0x51b2, 0x51b2, 0x51b2, 0x0000, 0x4a52, 0x41b2, 0x41d2, 0x41d2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x49b2, 0x49b2, 0x49b2, 0x49b2, 0x0000, 0x41b2, 0x41d2, 0x41d2, 0x41b2, 0x41d1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x49b2, 0x49b2, 0x49b2, 0x49b2, 0x41d2, 0x41b2, 0x41d2, 0x41b2, 0x41d2, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x52aa, 0x41b2, 0x41d2, 0x41d2, 0x41b2, 0x41d2, 0x41d2, 0x41b2, 0x39d1, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41d2, 0x41d2, 0x41d2, 0x41b2, 0x41b2, 0x41f2, 0x4932, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x41b2, 0x41b2, 0x41b2, 0x41b2, 0x001f, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_HAL = { image_data_HAL, 32, 32,
    16 };
