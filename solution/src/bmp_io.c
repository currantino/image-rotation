#include "bmp_io.h"

#ifndef BF_TYPE
#define BF_TYPE 19778
#endif

#ifndef BYTES_PER_PIXEL
#define BYTES_PER_PIXEL 3
#endif

#ifndef BITS_PER_BYTE
#define BITS_PER_BYTE 8
#endif

static enum read_status bmp_header_read(FILE *in, struct bmp_header *header)
{
	size_t values_read = fread(header, sizeof(struct bmp_header), 1, in);
	return values_read == 1 ? READ_OK : READ_INVALID_HEADER;
}

enum read_status from_bmp(FILE *in, struct image *img)
{
	if (!in) {
		return READ_ERROR;
	}

	struct bmp_header *header = malloc(sizeof(struct bmp_header));
	bmp_header_read(in, header);

	size_t width = header->biWidth;
	size_t height = header->biHeight;
	struct dimensions dim = {.x = width, .y = height};
	*img = image_create(dim);
	struct pixel *data = img->data;
	size_t padding_in_bytes = image_get_padding_in_bytes(img);
	printf("\nheight=%zupx, width=%zupx, padding=%zubytes\n\n", height,
	       width, padding_in_bytes);

	fseek(in, header->bOffBits, SEEK_SET);
	for (size_t row = 0; row < height; row++) {
		fread(data + (height - row - 1) * width, sizeof(struct pixel),
		      width, in);
		fseek(in, padding_in_bytes, SEEK_CUR);
	}
	free(header);
	return READ_OK;
}

static struct bmp_header image_generate_header(const struct image *img)
{
	struct bmp_header header = {0};

	header.bfType = BF_TYPE;
	header.bfileSize = ((image_get_width(img) * BYTES_PER_PIXEL +
			     image_get_padding_in_bytes(img)) *
			    image_get_height(img)) +
			   sizeof(struct bmp_header);
	header.bOffBits = sizeof(struct bmp_header);
	header.biSize = 40;
	header.biWidth = image_get_width(img);
	header.biHeight = image_get_height(img);
	header.biPlanes = 1;
	header.biBitCount = BYTES_PER_PIXEL * BITS_PER_BYTE;
	header.biCompression = 0;
	header.biSizeImage = ((image_get_width(img) * BYTES_PER_PIXEL +
			       image_get_padding_in_bytes(img)) *
			      image_get_height(img));
	header.biXPelsPerMeter = 2834;
	header.biYPelsPerMeter = 2834;

	return header;
}

static enum write_status write_bmp_header(FILE *out,
					  const struct bmp_header *header)
{
	fwrite(header, sizeof(struct bmp_header), 1, out);
	return WRITE_OK;
}

enum write_status to_bmp(FILE *out, const struct image *img)
{
	if (!out) {
		return WRITE_ERROR;
	}
	struct bmp_header *header = malloc(sizeof(struct bmp_header));
	*header = image_generate_header(img);
	write_bmp_header(out, header);
	free(header);
	size_t width = image_get_width(img);
	size_t height = image_get_height(img);
	struct pixel *data = img->data;
	size_t padding_in_bytes = image_get_padding_in_bytes(img);

	size_t pixels_written = 0;
	for (size_t row = 0; row < height; row++) {
		pixels_written += fwrite(data + (height - row - 1) * width,
					 sizeof(struct pixel), width, out);
		fseek(out, padding_in_bytes, SEEK_CUR);
	}
	if (pixels_written != width * height) {
		return WRITE_ERROR;
	}
	return WRITE_OK;
}
