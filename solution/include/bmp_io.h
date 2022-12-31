#ifndef BMP_IO_H
#define BMP_IO_H

#include "bmp_header.h"
#include "image.h"
#include "io.h"
#include <stdio.h>

enum read_status { READ_OK, READ_HEADER_ERROR, READ_ERROR };

enum write_status { WRITE_OK, WRITE_HEADER_ERROR, WRITE_ERROR };

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

int64_t bmp_image_get_padding_in_bytes(const struct image *img);

const char *get_read_status_msg(enum read_status read_status);

const char *get_write_status_msg(enum write_status write_status);

#endif
