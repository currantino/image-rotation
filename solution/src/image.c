#include "image.h"

struct image image_create(struct dimensions size)
{
	struct pixel *data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

size_t image_get_padding(struct image *image)
{
	size_t width_in_bytes = ((image->size).x) * BYTES_PER_PIXEL;
	size_t padding_in_bytes = 0;
	if (width_in_bytes % 4 == 0) {
		return padding_in_bytes;
	} else {
		while ((width_in_bytes + padding_in_bytes) % 4 != 0) {
			padding_in_bytes++;
		}
		return padding_in_bytes;
	}
}

void image_destroy(struct image *image)
{
	free(image->data);
	free(image);
}
