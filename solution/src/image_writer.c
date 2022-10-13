#include "image_writer.h"

bool image_write(FILE *f, struct image *image)
{
	if (!f)
		return false;
	fwrite(image->data, sizeof(struct pixel), image->size.x * image->size.y,
	       f);
	fclose(f);
	return true;
}
