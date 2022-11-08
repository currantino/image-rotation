#include "image.h"

#ifndef BYTES_PER_PIXEL
#define BYTES_PER_PIXEL 3
#endif

long image_get_padding_in_bytes(const struct image *image)
{
	long width_in_bytes = (long)(image->size.x) * BYTES_PER_PIXEL;
	return width_in_bytes % 4 == 0 ? 0 : 4 - width_in_bytes % 4;
}
struct image image_create(const struct dimensions size)
{
	struct pixel *data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

void image_destroy(struct image *image)
{
	free(image->data);
}

size_t image_get_width(const struct image *img) { return img->size.x; }

size_t image_get_height(const struct image *img) { return img->size.y; }

size_t image_get_size(const struct image *img)
{
	return image_get_width(img) * image_get_height(img);
}
