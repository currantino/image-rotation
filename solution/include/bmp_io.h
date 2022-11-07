#ifndef BMP_IO_H
#define BMP_IO_H

#include <stdio.h>

#include "bmp_header.h"
#include "image.h"

enum read_status { READ_OK, READ_INVALID_HEADER, READ_ERROR };

enum write_status { WRITE_OK, WRITE_ERROR };

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

#endif
