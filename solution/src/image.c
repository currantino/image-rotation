#include "image.h"

#ifndef BYTES_PER_PIXEL
#define BYTES_PER_PIXEL 3
#endif

struct image image_create(const struct dimensions size)
{
	struct pixel *data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

void image_destroy(struct image *image)
{
	free(image->data);
	free(image);
}

size_t image_get_width(const struct image *img) { return img->size.x; }

size_t image_get_height(const struct image *img) { return img->size.y; }

size_t image_get_size(const struct image *img)
{
	return image_get_width(img) * image_get_height(img);
}
