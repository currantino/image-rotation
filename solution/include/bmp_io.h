#ifndef BMP_IO_H
#define BMP_IO_H

#include <stdio.h>

#include "bmp_header.h"
#include "image.h"

enum read_status {
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
	READ_INVALID_BITS,
	READ_INVALID_HEADER,
	READ_ERROR
};

enum read_status from_bmp(FILE *in, struct image *img);

enum write_status { WRITE_OK = 0, WRITE_ERROR };

enum write_status to_bmp(FILE *out, const struct image *img);

#endif
