#include <stdint.h>

#include <rle_decode.h>

image_t *decode_rle(const image_t *rle_image)
{
    image_t *image = new image_t();
    image->width = rle_image->width;
    image->height = rle_image->height;
    image->data = new uint16_t[image->width * image->height];

    const uint16_t *rle_data = rle_image->data;
    uint16_t *image_data = (uint16_t *)image->data;
    const uint16_t *image_data_end = image_data + image->width * image->height;

    while (image_data < image_data_end)
    {
        // Do variable length decoding
        uint32_t count = 0;
        do
        {
            count <<= 7;
            count |= *rle_data & 0x7f;
        } while (*rle_data++ & 0x80);
    
        // Write the RLE data
        uint16_t value = *rle_data++;
        while (count--)
            *image_data++ = value;
    }

    return image;
}