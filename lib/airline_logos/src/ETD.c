
/*******************************************************************************
* image
* filename: unsaved
* name: ETD
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



static const uint16_t image_data_ETD[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffe0, 0xffe0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffe0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xd525, 0x0000, 0x7be0, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xfd4a, 0x0000, 0x0000, 0xccc5, 0xc4c5, 0x0000, 0xf800, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xc4c5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xcc85, 0xcce6, 0x0000, 0x0000, 0x0000, 0x0000, 0xfbe0, 0x0000, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0xbbe7, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xc4c5, 0xccc5, 0xccc5, 0xccc5, 0xbbe7, 0x0000, 0xcca5, 0xccc5, 0xfbe0, 0xfd4a, 0xccc5, 0x0000, 0x0000, 0xc4c5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xbbe7, 0x0000, 
    0x0000, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xc4c5, 0xccc5, 0xc4c5, 0xc4c5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xd4e4, 0xc4a5, 0xccc5, 0xccc5, 0xb484, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0xccc6, 0xccc5, 0xccc5, 0xcd05, 0xcce5, 0xccc5, 0xccc5, 0x0000, 
    0x0000, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xc4c5, 0x0000, 0xccc5, 0xc4a5, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0xccc5, 0xccc5, 0x0000, 0x0000, 0xcce5, 0xccc5, 0x0000, 
    0x0000, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xcce5, 0xcce5, 0xcc84, 0xccc5, 0xc4a5, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xccc5, 0x0000, 0x0000, 0xcce5, 0xccc5, 0xccc5, 0xd4a5, 0x0000, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0x0000, 
    0x0000, 0xffe0, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xdc84, 0xccc5, 0xc4c5, 0x0000, 0x0000, 0xcce5, 0xccc5, 0xcce5, 0xad4a, 0x0000, 0xcce5, 0xccc5, 0xc467, 0x0000, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xccc5, 0xf800, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xd505, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xc4c5, 0xcce5, 0xccc5, 0xccc5, 0xdce7, 0xccc5, 0xccc5, 0xc4c5, 0xccc5, 0xcce5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xccc5, 0xcce5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xc4c5, 0xccc5, 0xccc5, 0xc547, 0xccc5, 0xccc5, 0xd4e4, 0xccc5, 0xccc5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc5, 0xcce5, 0xccc5, 0xccc4, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc6, 0xcce5, 0xcce5, 0xf800, 0xccc5, 0xcce5, 0xcce5, 0xcce5, 0xc4e5, 0xcd05, 0xccc5, 0xcce5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7be0, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xcce5, 0xcce5, 0xccc5, 0xccc5, 0xcce5, 0xc4c5, 0xccc5, 0xccc5, 0xcd05, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xccc4, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xccc5, 0xcce5, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xfbe0, 0xbbe7, 0xbce3, 0xbbe7, 0xbce3, 0x0000, 0xd545, 0xad40, 0xabe5, 0xccc6, 0xbbe7, 0xdce3, 0xfd4a, 0xfbe0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
};
const tImage airline_logo_ETD = { image_data_ETD, 32, 32,
    16 };
