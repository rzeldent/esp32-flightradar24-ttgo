#include <esp32-hal-log.h>
#include <zimage.h>
#include <miniz.h>
#include <esp.h>
/*
std::vector<unsigned short> z_image_decode(const z_image_data_t *z_image_data)
{
    auto image = std::vector<unsigned short>(z_image_data->width * z_image_data->height);
    ulong uncompressed_len;
    log_i("Decoding zimage");
    auto status = uncompress((unsigned char *)image.data(), &uncompressed_len, z_image_data->compressed_data, z_image_data->compressed_size);
    log_i("Decompressed: %d. %u -> %u.", status, z_image_data->compressed_size, uncompressed_len);
    assert(status == MZ_OK);
    return image;
}
*/
unsigned short* z_image_decode(const z_image_data_t *z_image_data)
{
    auto image = new unsigned short[z_image_data->width * z_image_data->height];
    assert(image);
    ulong uncompressed_len = z_image_data->width * z_image_data->height * sizeof(unsigned short);
    log_i("Decompressing zimage. Heap: %lu", ESP.getFreeHeap());
    auto status = uncompress((unsigned char*)image, &uncompressed_len, z_image_data->compressed_data, z_image_data->compressed_size);
    log_i("Decompressed: %d. %u -> %u.", status, z_image_data->compressed_size, uncompressed_len);
    assert(status == MZ_OK);
    return image;
}
