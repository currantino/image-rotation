#include "bmp_image.h"

int64_t bmp_image_get_padding_in_bytes(const struct image *img)
{
	int64_t width_in_bytes =
	    (int64_t)(img->size.x) * image_get_bytes_per_pixel(img);
	return width_in_bytes % 4 == 0 ? 0 : 4 - width_in_bytes % 4;
}
