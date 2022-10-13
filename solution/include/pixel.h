#ifndef PIXEL_H
#define PIXEL_H

#include <inttypes.h>
#include <stdio.h>

struct pixel {
	uint8_t components[3];
};

struct pixel pixel_create(uint8_t blue, uint8_t green, uint8_t red);
struct pixel pixel_read(FILE *f);

#endif
