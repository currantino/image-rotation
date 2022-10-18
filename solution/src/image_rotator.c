#include "image_rotator.h"
#include "stdbool.h"
void print_data(size_t height, size_t width, struct pixel *data)
{
	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) {
			pixel_print(data[row * width + col]);
		}
		printf("\n");
	}
}
struct image image_rotate(const struct image source)
{
	struct dimensions size = source.size;
	struct dimensions reversed = dimensions_reverse(&size);
	struct image rotated = image_create(reversed);

	struct pixel *source_data = source.data;
	struct pixel *data = rotated.data;

	size_t width = image_get_width(&source);
	size_t height = image_get_height(&source);

	print_data(height, width, source_data);

	for (size_t row = 0; row < height; row++) {
		for (size_t col = 0; col < width; col++) {
			data[(width - col - 1) * height + row] =
			    source_data[row * width + col];
		}
	}

	print_data(width, height, data);

	return rotated;
}
