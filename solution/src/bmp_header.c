#include "bmp_header.h"

static bool read_header(FILE *f, struct bmp_header *header)
{
	return fread(header, sizeof(struct bmp_header), 1, f);
}

bool read_header_from_file(FILE *f, struct bmp_header *header)
{
	if (!f)
		return false;
	bool is_read_successfully = read_header(f, header);
	return is_read_successfully;
}

bool write_header_to_file(FILE *f, struct bmp_header *header)
{
	if (!f)
		return false;
	fwrite(header, sizeof(struct bmp_header), 1, f);
	return true;
}
