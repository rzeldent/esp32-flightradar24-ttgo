
/*******************************************************************************
* image
* filename: unsaved
* name: image_ki
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



static const uint16_t image_data_image_ki[200] = {
    0xc882, 0xc882, 0xc882, 0xc061, 0xc882, 0xc882, 0xc061, 0xd1a1, 0xdac1, 0xd201, 0xdac1, 0xdb21, 0xc921, 0xc882, 0xc082, 0xc882, 0xc882, 0xc882, 0xc882, 0xc061, 
    0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc061, 0xc8c1, 0xec80, 0xe440, 0xc8c1, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 
    0xc082, 0xc881, 0xc882, 0xc882, 0xc082, 0xc882, 0xc882, 0xc882, 0xc8c1, 0xd1c1, 0xc9a0, 0xc862, 0xc882, 0xc882, 0xc882, 0xc882, 0xc882, 0xc862, 0xc061, 0xc862, 
    0xc882, 0xc882, 0xc881, 0xc882, 0xc882, 0xc882, 0xc882, 0xc921, 0xe440, 0xed00, 0xed00, 0xec80, 0xc921, 0xc882, 0xc881, 0xc862, 0xc882, 0xc882, 0xc882, 0xc882, 
    0xc882, 0xc881, 0xc882, 0xc8e3, 0xc882, 0xc882, 0xc882, 0xdb22, 0xed00, 0xfe80, 0xfe80, 0xed00, 0xdb22, 0xc862, 0xc882, 0xc882, 0xc8e3, 0xc882, 0xc882, 0xc882, 
    0xce3a, 0xb558, 0xbdb8, 0xce3a, 0xce3a, 0xb558, 0xbdb8, 0xce3a, 0xd6ba, 0xce57, 0xce57, 0xd6ba, 0xce3a, 0xbdb8, 0xb578, 0xce3a, 0xce3a, 0xbdb8, 0xb557, 0xce3a, 
    0x5b73, 0x5b53, 0x5b53, 0x6bb4, 0x5b73, 0x5b53, 0x5b53, 0x6bb4, 0x5b73, 0x5b73, 0x5b73, 0x5b73, 0x6bb4, 0x5b53, 0x5b53, 0x5b73, 0x6bb4, 0x5b53, 0x5b53, 0x5b73, 
    0x8476, 0xa579, 0x94f7, 0x7415, 0x8496, 0xa579, 0x94f7, 0x7415, 0x8496, 0xad99, 0xad99, 0x8496, 0x7435, 0x9518, 0xa579, 0x8496, 0x7435, 0x9d18, 0xa579, 0x8496, 
    0x9518, 0x7415, 0x8496, 0xa579, 0x9518, 0x7415, 0x8496, 0xa578, 0x9d58, 0x8496, 0x8496, 0xa558, 0xa579, 0x8496, 0x7435, 0x9517, 0xa579, 0x8496, 0x7435, 0x9d18, 
    0x42b1, 0x63d4, 0x5353, 0x322f, 0x42b1, 0x63d4, 0x5353, 0x322f, 0x3a91, 0x6393, 0x6393, 0x3a91, 0x322f, 0x5353, 0x6bb4, 0x3a90, 0x3230, 0x5353, 0x63b4, 0x42b1
};
const tImage image_ki = { image_data_image_ki, 20, 10,
    16 };
