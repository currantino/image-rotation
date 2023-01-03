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

#ifndef BI_BIT_COUNT
#define BI_BIT_COUNT 24
#endif

struct __attribute__((packed)) bmp_header {
	uint16_t bfType;
	uint32_t bfileSize;
	uint32_t bfReserved;
	uint32_t bOffBits;
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

enum bmp_header_status {
	BMP_HEADER_OK = 0,
	INVALID_SIGNATURE,
	INVALID_BI_PLANES,
	UNSUPPORTED_BI_BIT_COUNT,
	UNSUPPORTED_BI_COMPRESSION,
	INVALID_DIMENSIONS,
	BMP_HEADER_ERROR
};

static const char *const bmp_header_status_msg[] = {
    [BMP_HEADER_OK] = "BMP image header is valid",
    [INVALID_SIGNATURE] = "BMP image header has invalid signature",
    [INVALID_BI_PLANES] = "BMP image has invalid number of planes",
    [UNSUPPORTED_BI_BIT_COUNT] = "BMP image has unsupported bit count",
    [UNSUPPORTED_BI_COMPRESSION] = "BMP image has unsupported compression",
    [INVALID_DIMENSIONS] = "BMP image has non-positive dimensions",
    [BMP_HEADER_ERROR] = "Error occured while processing BMP image header"};

static enum bmp_header_status
bmp_header_is_valid(const struct bmp_header *header)
{
	if (header->bfType != BF_TYPE) {
		return INVALID_SIGNATURE;
	} else if (header->biPlanes != BI_PLANES) {
		return INVALID_BI_PLANES;
	} else if (header->biBitCount != BI_BIT_COUNT) {
		return UNSUPPORTED_BI_BIT_COUNT;
	} else if (header->biCompression != BI_COMPRESSION) {
		return UNSUPPORTED_BI_COMPRESSION;
	} else if (header->biWidth <= 0 || header->biHeight <= 0) {
		return INVALID_DIMENSIONS;
	}
	return BMP_HEADER_OK;
}

static enum bmp_header_status bmp_header_read(FILE *in,
					      struct bmp_header *header)
{
	const size_t values_read =
	    fread(header, sizeof(struct bmp_header), 1, in);
	if (values_read == 1) {
		return bmp_header_is_valid(header);
	}
	return BMP_HEADER_ERROR;
}

enum read_status from_bmp(FILE *in, struct image *img)
{
	if (!in) {
		return READ_ERROR;
	}

	struct bmp_header header = {0};

	enum bmp_header_status header_read_status =
	    bmp_header_read(in, &header);
	if (header_read_status != BMP_HEADER_OK) {
		log_err(bmp_header_status_msg[header_read_status]);
		return READ_HEADER_ERROR;
	} else {
		log_ok(bmp_header_status_msg[header_read_status]);
	}

	const size_t width = header.biWidth;
	const size_t height = header.biHeight;
	const struct dimensions dim = {.x = width, .y = height};
	const uint16_t bytes_per_pixel =
	    (uint16_t)(header.biBitCount / (uint16_t)BITS_PER_BYTE);
	if (fseek(in, header.bOffBits, SEEK_SET)) {
		return READ_ERROR;
	}
	struct image maybe_img = {0};
	maybe_img = image_create(dim, bytes_per_pixel);
	const int64_t padding_in_bytes =
	    bmp_image_get_padding_in_bytes(&maybe_img);
	for (size_t row = 0; row < height; row++) {
		const enum read_status row_read_status =
		    image_read_row(&maybe_img, row, in);
		if (row_read_status != READ_OK) {
			image_destroy(&maybe_img);
			return row_read_status;
		}
		if (!skip_padding(in, (long)padding_in_bytes)) {
			image_destroy(&maybe_img);
			return READ_ERROR;
		}
	}
	*img = maybe_img;
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
	const size_t height = image_get_height(img);
	const int64_t padding_in_bytes = bmp_image_get_padding_in_bytes(img);

	for (size_t row = 0; row < height; row++) {
		const enum write_status row_write_status =
		    image_write_row(img, row, out);
		if (row_write_status != WRITE_OK) {
			return row_write_status;
		}
		if (!skip_padding(out, (long)padding_in_bytes)) {
			return WRITE_ERROR;
		}
	}
	return WRITE_OK;
}

int64_t bmp_image_get_padding_in_bytes(const struct image *img)
{
	const int64_t width_in_bytes = (int64_t)image_get_width(img) *
				       (int64_t)image_get_bytes_per_pixel(img);
	return 4 - width_in_bytes % 4;
}
