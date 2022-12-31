#include "image_transformer.h"

struct image image_rotate(const struct image *source)
{
	const struct dimensions size = source->size;
	const struct dimensions size_reversed = dimensions_reverse(&size);
	struct image result =
	    image_create(size_reversed, image_get_bytes_per_pixel(source));

	const size_t result_width = image_get_width(&result);
	const size_t result_height = image_get_height(&result);

	for (size_t row = 0; row < result_height; row++) {
		for (size_t col = 0; col < result_width; col++) {
			*image_get_pixel_by_row_and_col(&result, row, col) =
			    *image_get_pixel_by_row_and_col(
				source, result_width - 1 - col, row);
		}
	}

	return result;
}
