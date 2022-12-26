#ifndef BMP_IMAGE_H
#include <image.h>
#include <inttypes.h>
#define BMP_IMAGE_H

int64_t bmp_image_get_padding_in_bytes(const struct image *img);
#endif
