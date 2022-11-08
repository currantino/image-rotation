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
	if (argc != 3) {
		if (argc < 3)
			perror("Not enough arguments \n");
		if (argc > 3)
			perror("Too many arguments \n");
		exit(1);
	}

	const char * input_filename = argv[1];

	struct image img = {0};

	FILE *in = fopen(input_filename, "rb");
	enum read_status read_status = from_bmp(in, &img);
	fclose(in);

	switch (read_status) {
	case READ_OK: {
		log_ok(image_read_error_msg[read_status]);
		break;
	}
	default: {
		log_err(image_read_error_msg[read_status]);
		image_destroy(&img);
		return 1;
	}
	}

	struct image rotated = {0};
	rotated = image_rotate(img);
	image_destroy(&img);

	const char * output_filename = argv[2];
	FILE *out = fopen(output_filename, "wb");
	enum write_status write_status = to_bmp(out, &rotated);
	fclose(out);
	image_destroy(&rotated);

	switch (write_status) {
	case WRITE_OK: {
		log_ok(image_write_error_msg[write_status]);
		break;
	}
	default: {
		log_err(image_write_error_msg[write_status]);
		return 1;
	}
	}
	return 0;
}
