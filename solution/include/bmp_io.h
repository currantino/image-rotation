#ifndef BMP_IO_H
#define BMP_IO_H

#include "bmp_header.h"
#include "image.h"
#include <stdio.h>

enum read_status { READ_OK, READ_HEADER_ERROR, READ_ERROR };

enum write_status { WRITE_OK, WRITE_HEADER_ERROR, WRITE_ERROR };

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status to_bmp(FILE *out, const struct image *img);

int64_t bmp_image_get_padding_in_bytes(const struct image *img);

static const char *const image_read_error_msg[] = {
    [READ_OK] = "File read successfully!",
    [READ_HEADER_ERROR] = "File header could not be read!",
    [READ_ERROR] = "File could not be read!"};

static const char *const image_write_error_msg[] = {
    [WRITE_OK] = "File written successfully!",
    [WRITE_HEADER_ERROR] = "File header could not be read!",
    [WRITE_ERROR] = "File could not be written!"};

#endif
