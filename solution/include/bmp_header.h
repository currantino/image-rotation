#ifndef BMP_HEADER_H
#define BMP_HEADER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct __attribute__((packed)) bmp_header {
	uint16_t bfType;
	uint32_t bfileSize;
	uint32_t bfReserved;
	uint32_t bOffBits;
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

bool read_header_from_file(FILE *f, struct bmp_header *header);
bool write_header_to_file(FILE *f, struct bmp_header *header);

#endif