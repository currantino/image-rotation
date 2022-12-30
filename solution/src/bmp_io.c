#include "bmp_io.h"

#ifndef BF_TYPE
#define BF_TYPE 19778
#endif

#ifndef BITS_PER_BYTE
#define BITS_PER_BYTE 8
#endif

#ifndef PIXEL_DENSITY
#define PIXEL_DENSITY 2834
#endif

#ifndef BI_SIZE
#define BI_SIZE 40
#endif

#ifndef BI_PLANES
#define BI_PLANES 1
#endif

#ifndef BI_COMPRESSION
#define BI_COMPRESSION 0
#endif

static enum read_status bmp_header_read(FILE *in, struct bmp_header *header)
{
	const size_t values_read =
	    fread(header, sizeof(struct bmp_header), 1, in);
	return values_read == 1 ? READ_OK : READ_HEADER_ERROR;
}

enum read_status from_bmp(FILE *in, struct image *img)
{
	if (!in) {
		return READ_ERROR;
	}

	struct bmp_header header = {0};

	enum read_status header_read_status = bmp_header_read(in, &header);

	if (header_read_status != READ_OK) {
		return header_read_status;
	}

	const size_t width = header.biWidth;
	const size_t height = header.biHeight;
	const struct dimensions dim = {.x = width, .y = height};
	const uint16_t bytes_per_pixel =
	    (uint16_t)(header.biBitCount / (uint16_t)BITS_PER_BYTE);
	*img = image_create(dim, bytes_per_pixel);
	const int64_t padding_in_bytes = bmp_image_get_padding_in_bytes(img);
	fseek(in, header.bOffBits, SEEK_SET);
	for (size_t row = 0; row < height; row++) {
		fread(image_get_start_address_of_row(img, row),
		      sizeof(struct pixel), width, in);
		fseek(in, padding_in_bytes, SEEK_CUR);
	}
	return READ_OK;
}

static struct bmp_header bmp_image_generate_header(const struct image *img)
{
	struct bmp_header header = {0};

	header.bfType = BF_TYPE;
	header.bfileSize =
	    ((image_get_width(img) * image_get_bytes_per_pixel(img) +
	      bmp_image_get_padding_in_bytes(img)) *
	     image_get_height(img)) +
	    sizeof(struct bmp_header);
	header.bOffBits = sizeof(struct bmp_header);
	header.biSize = BI_SIZE;
	header.biWidth = image_get_width(img);
	header.biHeight = image_get_height(img);
	header.biPlanes = BI_PLANES;
	header.biBitCount = image_get_bytes_per_pixel(img) * BITS_PER_BYTE;
	header.biCompression = BI_COMPRESSION;
	header.biSizeImage =
	    (image_get_width(img) * image_get_bytes_per_pixel(img) +
	     bmp_image_get_padding_in_bytes(img)) *
	    image_get_height(img);
	header.biXPelsPerMeter = PIXEL_DENSITY;
	header.biYPelsPerMeter = PIXEL_DENSITY;

	return header;
}

static enum write_status write_bmp_header(FILE *out,
					  const struct bmp_header *header)
{

	const size_t values_written =
	    fwrite(header, sizeof(struct bmp_header), 1, out);
	return values_written == 1 ? WRITE_OK : WRITE_HEADER_ERROR;
}

enum write_status to_bmp(FILE *out, const struct image *img)
{
	if (!out) {
		return WRITE_ERROR;
	}
	const struct bmp_header header = bmp_image_generate_header(img);
	const enum write_status write_header_status =
	    write_bmp_header(out, &header);
	if (write_header_status != WRITE_OK) {
		return write_header_status;
	}
	const size_t width = image_get_width(img);
	const size_t height = image_get_height(img);
	const int64_t padding_in_bytes = bmp_image_get_padding_in_bytes(img);

	size_t pixels_written = 0;
	for (size_t row = 0; row < height; row++) {
		pixels_written +=
		    fwrite(image_get_start_address_of_row(img, row),
			   sizeof(struct pixel), width, out);
		fseek(out, padding_in_bytes, SEEK_CUR);
	}
	if (pixels_written != width * height) {
		return WRITE_ERROR;
	}
	return WRITE_OK;
}

int64_t bmp_image_get_padding_in_bytes(const struct image *img)
{
	const int64_t width_in_bytes =
	    image_get_width(img) * image_get_bytes_per_pixel(img);
	return 4 - width_in_bytes % 4;
}
