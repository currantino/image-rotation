#include "image_reader.h"

bool read_image(FILE *f, struct image *image)
{
	if (!f)
		return false;
	size_t padding = image_get_padding(image);
	printf("padding = %zu\n", padding);
	for (size_t i = 0; f && i < image->size.x * image->size.y; i++) {
		image->data[i] = pixel_read(f);
	}
	fclose(f);
	return true;
}
