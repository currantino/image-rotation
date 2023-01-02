#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "image.h"
#include "io.h"
#include <stdbool.h>
#include <stdio.h>

bool skip_padding(FILE *stream, const long padding_in_bytes);

enum read_status image_read_row(const struct image *img, const size_t row,
				FILE *in);

enum write_status image_write_row(const struct image *img, const size_t row,
				  FILE *out);

const char *get_read_status_msg(enum read_status read_status);

const char *get_write_status_msg(enum write_status write_status);

#endif
