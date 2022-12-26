#include "image_transformations.h"

struct image image_rotate(const struct image source)
{
	struct dimensions size = source.size;
	struct dimensions reversed = dimensions_reverse(&size);
	struct image rotated = image_create(reversed);

	size_t rotated_width = image_get_width(&rotated);
	size_t rotated_height = image_get_height(&rotated);

	for (size_t row = 0; row < rotated_height; row++) {
		for (size_t col = 0; col < rotated_width; col++) {
			*image_get_pixel_by_row_and_col(&rotated, row, col) =
			    *image_get_pixel_by_row_and_col(
				&source, rotated_width - 1 - col, row);
		}
	}

	return rotated;
}

struct image image_color_filter_red(const struct image source)
{
	struct dimensions size = source.size;
	struct image filtered = image_create(size);

	for (size_t row = 0; row < image_get_height(&filtered); row++) {
		for (size_t col = 0; col < image_get_width(&filtered); col++) {
			struct pixel pixel =
			    *image_get_pixel_by_row_and_col(&source, row, col);
			pixel.components[0] = 0;
			pixel.components[1] = 0;
			*image_get_pixel_by_row_and_col(&filtered, row, col) =
			    pixel;
		}
	}

	return filtered;
}
