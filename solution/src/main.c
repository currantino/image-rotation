#include <stdbool.h>
#include <stdio.h>

#include "bmp_io.h"
#include "image_rotator.h"
#include "util.h"

void usage(void)
{
	fprintf(
	    stderr,
	    "Usage: ./build/image-transformer BMP_FILE_NAME BMP_FILENAME\n");
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv; // supress 'unused parameters' warning
	if (argc != 3) {
		if (argc < 3)
			perror("Not enough arguments \n");
		if (argc > 3)
			perror("Too many arguments \n");
		exit(1);
	}

	struct image *img = malloc(sizeof(struct image));
	struct image *rotated = malloc(sizeof(struct image));

	FILE *in = fopen(argv[1], "rb");
	switch (from_bmp(in, img)) {
	case READ_OK: {
		err("file read successfully!", GREEN);
		break;
	}
	case READ_ERROR: {
		err("file could not be read", RED);
		return 1;
	}
	case READ_INVALID_HEADER: {
		err("header of the file could not be read", RED);
		return 2;
	}
	}

	fclose(in);

	*rotated = image_rotate(*img);
	image_destroy(img);

	FILE *out = fopen(argv[2], "wb");
	switch (to_bmp(out, rotated)) {
	case WRITE_OK: {
		err("file written successfully!", GREEN);
		break;
	}
	case WRITE_ERROR: {
		err("file could not be written", RED);
		return 1;
	}
	}
	fclose(out);
	image_destroy(rotated);
	return 0;
}
