#include "image_io.h"

bool skip_padding(FILE *stream, const long padding_in_bytes)
{
	int is_padding_skipped = !fseek(stream, padding_in_bytes, SEEK_CUR);
	return is_padding_skipped;
}

enum read_status image_read_row(const struct image *img, const size_t row,
				FILE *in)
{
	size_t pixels_read =
	    fread(image_get_start_address_of_row(img, row),
		  sizeof(struct pixel), image_get_width(img), in);
	if (pixels_read != image_get_width(img)) {
		if (feof(in)) {
			return READ_UNEXPECTED_EOF;
		} else if (ferror(in)) {
			return READ_ERROR;
		}
		return READ_ERROR;
	}
	return READ_OK;
}

enum write_status image_write_row(const struct image *img, const size_t row,
				  FILE *out)
{
	size_t pixels_written =
	    fwrite(image_get_start_address_of_row(img, row),
		   sizeof(struct pixel), image_get_width(img), out);
	if (pixels_written != image_get_width(img)) {
		return WRITE_ERROR;
	}
	return WRITE_OK;
}
