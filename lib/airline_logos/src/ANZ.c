
/*******************************************************************************
* image
* filename: unsaved
* name: ANZ
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



static const uint16_t image_data_ANZ[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xbe7a, 0x7cd4, 0x22cc, 0x0a4a, 0x2aec, 0x74b3, 0xbe59, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8d55, 0x438f, 0x0a2a, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x22cc, 0x5c11, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xbefb, 0x6c72, 0x0a4a, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0a2a, 0x6c92, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x53f5, 0x4baf, 0x0209, 0x01e9, 0x01e9, 0x0229, 0x3b4e, 0x5c31, 0x8514, 0x5410, 0x124a, 0x01e9, 0x01e9, 0x2aec, 0xd6dc, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7bef, 0x5c11, 0x01e9, 0x01e9, 0x01e9, 0x22cc, 0x8535, 0xf79e, 0x0000, 0xad55, 0x0000, 0x74b3, 0x0a29, 0x01e9, 0x0209, 0xadf8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xad55, 0x3b6e, 0x01e9, 0x01e9, 0x01e9, 0x2b0d, 0xb618, 0x0000, 0x7d34, 0x4bb0, 0x438f, 0x9576, 0x0000, 0x3b6e, 0x01e9, 0x01e9, 0x8515, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xb5b6, 0x4bcf, 0x01e9, 0x01e9, 0x01e9, 0x3b6e, 0xadd7, 0x0000, 0x0000, 0x4bd0, 0x01e9, 0x01e9, 0x124a, 0xc69a, 0x22cc, 0x01e9, 0x0209, 0x9db7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xdefb, 0x5c11, 0x0209, 0x01e9, 0x01e9, 0x3b4e, 0xa5d7, 0x0000, 0x0000, 0x0000, 0x22cc, 0x01e9, 0x01e9, 0x0209, 0x438f, 0x01e9, 0x01e9, 0x126b, 0xa5b7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x74d3, 0x0209, 0x01e9, 0x01e9, 0x2b0d, 0x8d96, 0x0000, 0x0000, 0x0000, 0x0000, 0x53f0, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0209, 0x6451, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x53d0, 0x0229, 0x01e9, 0x01e9, 0x3b4e, 0x7cf3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x9575, 0x1aab, 0x01e9, 0x01e9, 0x01e9, 0x0a2a, 0x4bd0, 0x7bef, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6c72, 0x0a4a, 0x01e9, 0x01e9, 0x1aac, 0xb639, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xa5b7, 0x74d3, 0x5c31, 0x7cf4, 0x7cb3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xa5f7, 0x1a8b, 0x01e9, 0x01e9, 0x0a2a, 0xa5d7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x8534, 0x22ec, 0x01e9, 0x01e9, 0x01e9, 0x4baf, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x3b6e, 0x6c72, 0x0000, 
    0x0000, 0x0000, 0xb639, 0x332d, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x8514, 0x0000, 
    0x0000, 0xdefb, 0x5c31, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x128b, 0xb659, 0x0000, 
    0x0000, 0xbe59, 0x3b4e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x334e, 0x6472, 0x0000, 0x0000, 
    0x0000, 0xe75d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xdf3d, 0xe75d, 0xffff, 0x0000, 0x0000, 
    0x0000, 0x4bd0, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x0a2a, 0x3b6e, 0xdfff, 0x0000, 0x0000, 
    0x0000, 0x7cd3, 0x0209, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0209, 0x9576, 0x0000, 0x0000, 0x0000, 
    0x0000, 0xce9a, 0x126b, 0x01e9, 0x01e9, 0x0209, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x126a, 0x330d, 0xe71c, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x6472, 0x01e9, 0x01e9, 0x3b4e, 0xbe7a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xbe9a, 0xc6ba, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x8d35, 0x0209, 0x01e9, 0x0a2a, 0xae18, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0xbe79, 0x22ec, 0x01e9, 0x01e9, 0x6451, 0x0000, 0x0000, 0x0000, 0xe79e, 0x6451, 0x22cc, 0x126b, 0x3b6e, 0x6c72, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x6c93, 0x01e9, 0x01e9, 0x22cc, 0xd71d, 0x0000, 0x0000, 0x6c92, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0209, 0x6c72, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x9555, 0x1a8b, 0x01e9, 0x0209, 0x8d35, 0x0000, 0xe73c, 0x436e, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0a2a, 0xbe79, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0xffff, 0x6452, 0x01e9, 0x01e9, 0x22cc, 0xb659, 0xffff, 0x4bb0, 0x01e9, 0x01e9, 0x0a2a, 0x332d, 0x01e9, 0x01e9, 0x6c72, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xb659, 0x126b, 0x01e9, 0x0209, 0x6431, 0x0000, 0x9596, 0x53f0, 0x3b6e, 0x5c31, 0x8d35, 0x01e9, 0x01e9, 0x4bd0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0x6431, 0x01e9, 0x01e9, 0x0a2a, 0x5c11, 0xf7ff, 0x0000, 0x0000, 0xffff, 0x5c31, 0x01e9, 0x01e9, 0x6c72, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf7be, 0x4baf, 0x01e9, 0x01e9, 0x0209, 0x438f, 0x53f0, 0x74b3, 0x4bd0, 0x0209, 0x01e9, 0x0a4a, 0xadf8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xbe59, 0x438f, 0x0209, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x01e9, 0x0209, 0x6c72, 0x7bef, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xbe5a, 0x6c72, 0x126b, 0x0209, 0x01e9, 0x01e9, 0x01e9, 0x0a4a, 0x74b3, 0xc6ba, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xc6ba, 0x7cf4, 0x4baf, 0x438f, 0x6c92, 0xb639, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_ANZ = { image_data_ANZ, 32, 32,
    16 };
