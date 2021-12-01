#include <image.h>

std::unique_ptr<image_t> rle_decode(const image_data_t *rle_image)
{
    auto image = std::unique_ptr<image_t>(new image_t);
    image->width = rle_image->width;
    image->height = rle_image->height;
    uint size = rle_image->width * rle_image->height;
    image->data = new unsigned short[size];

return nullptr;
    // const unsigned short *rle_data = rle_image->data;
    // unsigned short *image_data = (unsigned short *)image->data;
    // const unsigned short *image_data_end = image_data + size;

    // while (image_data < image_data_end)
    // {
    //     // Do variable length decoding
    //     uint count = 0;
    //     do
    //     {
    //         count <<= 7;
    //         count |= *rle_data & 0x7f;
    //     } while (*rle_data++ & 0x80);

    //     // Write the RLE data
    //     unsigned short value = *rle_data++;
    //     while (count--)
    //         *image_data++ = value;
    // }

    // return image;
}
