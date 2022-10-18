/*#include "image_rotator.h"
#include "stdbool.h"

bool image_rotate(struct image *image)
{
	// struct pixel **input_ptr = &(image -> data);
	// size_t width = image -> size.x;
	// size_t height = image -> size.y;
	// struct pixel *rotated = malloc(sizeof(struct pixel) * width *
	// height); for (size_t i = 0; i < width * height - height; i++) {
	//	rotated[i] = *input_ptr[i+height];
	// }
	// free(image -> data);
	// image -> data = rotated;
	image->size = dimensions_reverse(&(image->size));
	return false;
}
*/

void f() {}
