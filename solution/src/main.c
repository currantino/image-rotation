#include <stdbool.h>
#include <stdio.h>

#include "bmp_io.h"
#include "image_rotator.h"

void usage()
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
	from_bmp(in, img);
	fclose(in);

	*rotated = image_rotate(*img);
	image_destroy(img);

	FILE *out = fopen(argv[2], "wb");
	to_bmp(out, rotated);
	fclose(out);
	image_destroy(rotated);
	return 0;
}
