#include <esp32-hal-log.h>
#include <zimage.h>
#include <miniz.h>

unsigned short* z_image_decode(const z_image_data_t *z_image_data)
{
    auto image = new unsigned short[z_image_data->width * z_image_data->height];
    assert(image);
    ulong uncompressed_len = z_image_data->width * z_image_data->height * sizeof(unsigned short);
    auto status = uncompress((unsigned char*)image, &uncompressed_len, z_image_data->compressed_data, z_image_data->compressed_size);
    log_d("Decompressed image: %u -> %u bytes.", z_image_data->compressed_size, uncompressed_len);
    assert(status == MZ_OK);
    return image;
}
