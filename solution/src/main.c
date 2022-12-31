#include <stdio.h>

#include "../include/io.h"
#include "bmp_io.h"
#include "image_transformations.h"
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
		if (argc < 3)
			perror("Not enough arguments \n");
		if (argc > 3)
			perror("Too many arguments \n");
		return EXIT_FAILURE;
	}

	const char *input_filename = argv[1];

	struct image img = {0};

	FILE *in = NULL;
	enum file_open_status file_open_status =
	    image_open_stream(input_filename, READ_BINARY, in);
	switch (file_open_status) {
	case OPEN_SUCCESS: {
		log_ok(get_file_open_msg(file_open_status));
		break;
	}
	default: {
		log_err(get_file_open_msg(file_open_status));
		return EXIT_FAILURE;
	}
	}
	const enum read_status read_status = from_bmp(in, &img);
	// enum file_close_status file_close_status =
	image_close_stream(in);

	switch (read_status) {
	case READ_OK: {
		log_ok(get_read_status_msg(read_status));
		break;
	}
	default: {
		log_err(get_read_status_msg(read_status));
		image_destroy(&img);
		return EXIT_FAILURE;
	}
	}

	struct image rotated = {0};
	rotated = image_rotate(&img);
	image_destroy(&img);

	const char *output_filename = argv[2];
	FILE *out = fopen(output_filename, "wb");
	enum write_status write_status = to_bmp(out, &rotated);
	fclose(out);
	image_destroy(&rotated);

	switch (write_status) {
	case WRITE_OK: {
		log_ok(get_write_status_msg(write_status));
		break;
	}
	default: {
		log_err(get_write_status_msg(write_status));
		return EXIT_FAILURE;
	}
	}
	return EXIT_SUCCESS;
}
