#include "image.h"

struct image image_create( struct dimensions size ) {
	struct pixel* data = malloc(sizeof(struct pixel) * size.x * size.y);
	struct image created_image = {.size = size, .data = data};
	return created_image;
}

void image_destroy( struct image* image ) {
	free(image -> data);
	free(image);
}
