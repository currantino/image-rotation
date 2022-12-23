#pragma once

#include "dimensions.h"
#include "image.h"
#include "pixel.h"
#include <stddef.h>
#include <stdlib.h>

struct image {
	struct dimensions size;
	struct pixel *data;
};

struct image image_create(const struct dimensions size);
int64_t image_get_padding_in_bytes(const struct image *image);
void image_destroy(struct image *image);
size_t image_get_width(const struct image *img);
size_t image_get_height(const struct image *img);
size_t image_get_size(const struct image *img);
struct pixel *image_get_data(const struct image *img);
struct pixel *image_get_pixel_by_row_and_col(const struct image *img,
					     const size_t row,
					     const size_t col);
