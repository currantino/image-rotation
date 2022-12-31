#include <stdio.h>

#include "io.h"
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

	const char *input_path = argv[1];

	struct image img = {0};

	FILE *in = NULL;
	enum stream_open_status input_stream_open_status =
	    stream_open(input_path, READ_BINARY, &in);
	log_msg(get_stream_open_msg(input_stream_open_status));

	if (input_stream_open_status != OPEN_SUCCESS) {
		return EXIT_FAILURE;
	}
	const enum read_status read_status = from_bmp(in, &img);

	log_msg(get_read_status_msg(read_status));
	if (read_status != READ_OK) {
		image_destroy(&img);
		return EXIT_FAILURE;
	}

	enum stream_close_status input_stream_close_status = stream_close(in);
	log_msg(get_stream_close_msg(input_stream_close_status));

	if (input_stream_close_status != CLOSE_SUCCESS) {
		return EXIT_FAILURE;
	}

	struct image rotated = {0};
	rotated = image_rotate(&img);
	image_destroy(&img);

	const char *output_path = argv[2];
	FILE *out = NULL;
	enum stream_open_status output_stream_open_status =
	    stream_open(output_path, WRITE_BINARY, &out);
	log_msg(get_stream_open_msg(output_stream_open_status));
	if (output_stream_open_status != OPEN_SUCCESS) {
		image_destroy(&rotated);
		return EXIT_FAILURE;
	}

	enum write_status write_status = to_bmp(out, &rotated);
	log_msg(get_write_status_msg(write_status));
	if (write_status != WRITE_OK) {
		return EXIT_FAILURE;
	}

	enum stream_close_status output_stream_close_status = stream_close(out);
	log_msg(get_stream_close_msg(output_stream_close_status));
	if (output_stream_close_status != CLOSE_SUCCESS) {
		image_destroy(&rotated);
	}
	return EXIT_SUCCESS;
}
