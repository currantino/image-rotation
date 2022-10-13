#include <stdbool.h>
#include <stdio.h>

#include "bmp.h"
#include "bmp_header.h"
#include "image_reader.h"
#include "image_writer.h"
#include "io.h"

void usage()
{
	fprintf(
	    stderr,
	    "Usage: ./build/image-transformer BMP_FILE_NAME BMP_FILENAME\n");
}

void pixel_print(struct pixel pixel)
{
	printf("pixel: b=%u, g=%u, r=%u\n", pixel.components[0],
	       pixel.components[1], pixel.components[2]);
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
	struct bmp_header *header = malloc(sizeof(struct bmp_header));
	FILE *f = fopen(argv[1], "rb");
	read_header_from_file(f, header);
	struct image *image = malloc(sizeof(struct image));
	struct dimensions size = {header->biWidth, header->biHeight};
	*image = image_create(size);
	read_image(f, image);
	FILE *output = fopen(argv[2], "wb");
	write_header_to_file(f, header);
	bool is_copied = image_write(output, image);
	if (is_copied)
		printf("well done!\n");
	image_destroy(image);
	return 0;
}
