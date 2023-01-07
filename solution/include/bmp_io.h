#ifndef BMP_IO_H
#define BMP_IO_H

#include "image.h"
#include "image_io.h"
#include "util.h"
#include <stdio.h>

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

enum read_status bmp_image_read(const char *path, struct image *img);

enum write_status bmp_image_write(const char *path, const struct image *img);

#endif
