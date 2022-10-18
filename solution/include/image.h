#pragma once

#include "pixel.h"
#include <stddef.h>
#include <stdlib.h>

#include "dimensions.h"

struct image {
	struct dimensions size;
	struct pixel *data;
};

struct image image_create(struct dimensions size);
size_t image_get_padding_in_bytes(const struct image *image);
void image_destroy(struct image *image);
size_t image_get_width(const struct image *image);
size_t image_get_height(const struct image *image);
size_t image_get_size(const struct image *image);
