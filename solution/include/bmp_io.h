#ifndef BMP_IO_H
#define BMP_IO_H

#include "image.h"
#include "image_io.h"
#include <stdio.h>

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

int64_t bmp_image_get_padding_in_bytes(const struct image *img);

#endif
