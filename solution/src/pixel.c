#include "pixel.h"

struct pixel pixel_create(uint8_t blue, uint8_t green, uint8_t red) {
	return (struct pixel) {{blue, green, red}};
}

struct pixel pixel_read(FILE *f) {
	if (!f) {return (struct pixel) {0};}
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	fread(&blue, sizeof(uint8_t), 1, f);
	fread(&green, sizeof(uint8_t), 1, f);
	fread(&red, sizeof(uint8_t), 1, f);
	return pixel_create(blue, green, red);
}
