
/*******************************************************************************
* image
* filename: unsaved
* name: UAE
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



static const uint16_t image_data_UAE[1024] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf208, 0xe167, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xda49, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd967, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0xaaaa, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe188, 0xe1a8, 0xe1a8, 0xe9c8, 0x0000, 0xd9e7, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd988, 0xe1a8, 0xe1a8, 0xe1a8, 0xf80f, 0xe188, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe188, 0xe1a8, 0xe1a8, 0xe1c7, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd14a, 0xe188, 0xe1a8, 0xe1a8, 0xe189, 0x0000, 0xe1a8, 0xe1a8, 0xfaaa, 0xd1a8, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe188, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0xe1a8, 0xe1a8, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd988, 0xe1a8, 0xe188, 0x0000, 0xe9a9, 0xe188, 0xe1a8, 0xe1a8, 0xe188, 0xe148, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0xf986, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0xe1c9, 0xe924, 0xaaaa, 0xe188, 0xe1a8, 0x0000, 0x0000, 0xe189, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe9a9, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a9, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe188, 0xe1a8, 0x0000, 0xd929, 0xe1a8, 0x0000, 0xe167, 0xe1a8, 0xe9a9, 0xfaaa, 0xe188, 0xe1a8, 0xd988, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1c8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0xe1c8, 0xe1a8, 0xe1c8, 0x0000, 0x0000, 0xd9e7, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe169, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe189, 0xe1a8, 0xd988, 0xe1c8, 0xe1a8, 0xe188, 0xe189, 0x0000, 0x0000, 0x0000, 0x0000, 0xe188, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xf800, 0xd9a8, 0xf9e7, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe189, 0xe1a8, 0xd9a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xda49, 0xe188, 0xe1a8, 0xe165, 0xe1a8, 0xe188, 0x0000, 0x0000, 0x0000, 0xd929, 0xe1a8, 0xf94a, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe189, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe189, 0xd9a9, 0xe188, 0xe189, 0xe188, 0xe1a8, 0x0000, 0x0000, 0xf986, 0xe168, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe9e7, 0xe188, 0xf800, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xd1c8, 0x0000, 0xe1a8, 0x7800, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0xb9e7, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0xe9c9, 0xe1c7, 0xe1c7, 0xe1c7, 0xe1ca, 0xc989, 0xc989, 0xc989, 0xe189, 0xe189, 0xd988, 0xe1a8, 0xe1a8, 0xe1a8, 0xd147, 0xe188, 0xe1a8, 0xe1a8, 0xd924, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0xd929, 0xe1a8, 0xd989, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xf800, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe188, 0xe1a8, 0xf800, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xf800, 0xe188, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0x0000, 0xf80f, 0xe1a9, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe189, 0xe1a8, 0xf800, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0xd9a8, 0xe9a9, 0x0000, 0xf800, 0xe1a8, 0xf800, 0xfbef, 0xe188, 0xf800, 0x0000, 0xe189, 0xe1a8, 0xe1a8, 0xe188, 0xe1c8, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0x0000, 0xd9a8, 0xe1a8, 0xe1a8, 0xd988, 0xe188, 0xe1a8, 0xe1a8, 0xfaaa, 0xe1a8, 0xe1a8, 0x0000, 0xe189, 0xe1a8, 0xe1a8, 0xe188, 0xe187, 0xe1a8, 0xe1a8, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0xe1a8, 0xe1a8, 0xe1a8, 0xd989, 0xe1a8, 0xe1a8, 0xe189, 0xd989, 0xe1a8, 0xe1a8, 0xe188, 0x0000, 0xe1a8, 0xe1a8, 0xfaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0x0000, 0xe189, 0xe1a8, 0xe1a8, 0xd9a9, 0xe1a9, 0xe1a8, 0xe1a8, 0xf800, 0xe1a8, 0xe1a8, 0xd968, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0xf800, 0xe1a8, 0xfaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xe1c8, 0xe1a8, 0xe188, 0x0000, 0xd988, 0xe188, 0x0000, 0x0000, 0xe1a8, 0xf80f, 0x0000, 0xf800, 0xe1a8, 0xd9a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xd9a8, 0x0000, 0x0000, 0xe1a8, 0xfaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0xf80f, 0xe1a8, 0xe1a8, 0xd9a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1c8, 0xe168, 0xe187, 0xe1a8, 0xe188, 0xf800, 0x0000, 0xe187, 0xe1a8, 0xfaaa, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe188, 0xe188, 0xe188, 0xe188, 0xe188, 0xe1a9, 0xe188, 0x0000, 0xe187, 0xe1a8, 0xd988, 0x0000, 0xf9e7, 0xe188, 0xe1a8, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xd929, 0xe188, 0xe1a8, 0xd8e7, 0x0000, 0xfaaa, 0xe1a8, 0xe1a8, 0xe1a8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xd929, 0x0000, 0xe1a8, 0xfaaa, 0xfaaa, 0xd988, 0xe1a8, 0xe1a8, 0xe1a8, 0xe187, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf9e7, 0xe9c9, 0xe967, 0xe967, 0xe988, 0xe189, 0xe1c8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe9a9, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xd968, 0xe1a8, 0xe1a8, 0xe1a8, 0xe1a8, 0xe947, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf9e7
};
const tImage airline_logo_UAE = { image_data_UAE, 32, 32,
    16 };
