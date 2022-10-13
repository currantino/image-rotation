#pragma once

#include "pixel.h"
#include <stddef.h>
#include <stdlib.h>

#include "dimensions.h"

#define BYTES_PER_PIXEL 3

struct image {
	struct dimensions size;
	struct pixel *data;
};

struct image image_create(struct dimensions size);
size_t image_get_padding(struct image *image);
void image_destroy(struct image *image);
