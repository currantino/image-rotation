#include <stdio.h>

#include "bmp_io.h"
#include "image_transformer.h"
#include "io.h"
#include "util.h"

void usage(void)
{
	fprintf(
	    stderr,
	    "Usage: ./build/image-transformer BMP_FILE_NAME BMP_FILENAME\n");
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		if (argc < 3) {
			err("Not enough arguments");
			usage();
		}
		if (argc > 3) {
			err("Too many arguments");
			usage();
		}
		return EXIT_FAILURE;
	}

	const char *input_path = argv[1];
	struct image img = {0};
	if (bmp_image_read(input_path, &img) != READ_OK) {
		return EXIT_FAILURE;
	}

	struct image image_transformed = {0};
	image_transformed = image_rotate(&img);
	image_destroy(&img);

	const char *output_path = argv[2];
	if (bmp_image_write(output_path, &image_transformed) != WRITE_OK) {
		image_destroy(&image_transformed);
		return EXIT_FAILURE;
	}

	image_destroy(&image_transformed);
	return EXIT_SUCCESS;
}
