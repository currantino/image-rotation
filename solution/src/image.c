#include "image.h"
#define BYTES_PER_PIXEL 3

struct image image_create(struct dimensions size)
{
	struct pixel *data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

size_t image_get_padding_in_bytes(const struct image *image)
{
	size_t width_in_bytes = (image->size.x) * BYTES_PER_PIXEL;
	return width_in_bytes % 4 == 0 ? 0 : 4 - width_in_bytes % 4;
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

struct pixel* image_get_row(const struct image *img, size_t row)
{
	if (row >= image_get_height(img)) {return NULL;}
	return (img -> data) + row * image_get_width(img);
}

struct pixel* image_get_column(const struct image *img, size_t column)
{
	if (column >= image_get_width(img)) { return NULL;}
	return (img -> data) + column;
}
