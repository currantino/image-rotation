#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "image.h"
#include <stdbool.h>
#include <stdio.h>

bool image_write(FILE *f, struct image *image);

#endif
