#ifndef IMAGE_TRANSFORMATIONS_H
#define IMAGE_TRANSFORMATIONS_H

#include "image.h"

struct image image_rotate(const struct image source);
struct image image_color_filter_red(const struct image source);

#endif
