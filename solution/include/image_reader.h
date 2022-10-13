#ifndef IMAGE_READER_H
#define IMAGE_READER_H

#include "image.h"
#include <stdbool.h>
#include <stdio.h>

bool read_image(FILE *f, struct image *image);

#endif
