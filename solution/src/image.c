#include "image.h"

struct image image_create(const struct dimensions size)
{
	struct pixel *data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

void image_destroy(struct image *img) { free(img->data); }

int64_t image_get_bytes_per_pixel(const struct image *img)
{
	return img->bytes_per_pixel;
}

void image_set_bytes_per_pixel(struct image *img, int64_t bytes_per_pixel)
{
	img->bytes_per_pixel = bytes_per_pixel;
}

size_t image_get_width(const struct image *img) { return img->size.x; }

size_t image_get_height(const struct image *img) { return img->size.y; }

size_t image_get_size(const struct image *img)
{
	return image_get_width(img) * image_get_height(img);
}

struct pixel *image_get_data(const struct image *img) { return img->data; }

struct pixel *image_get_pixel_by_row_and_col(const struct image *img,
					     const size_t row, const size_t col)
{
	return image_get_data(img) + row * image_get_width(img) + col;
}

struct pixel *image_get_start_address_of_row(const struct image *img,
					     const size_t row)
{
	return image_get_data(img) + row * image_get_width(img);
}
