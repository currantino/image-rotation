#include "bmp_header.h"

static bool read_header( FILE* f, struct bmp_header* header) {
	return fread( header, sizeof( struct bmp_header ), 1 , f );
}

bool read_header_from_file( const char* filename, struct bmp_header* header) {
	if (!filename) return false;
	FILE* f = fopen(filename, "rb");
	if (!f) return false;
	bool is_read_successfully = read_header( f, header );
	if (is_read_successfully) {
		fclose(f);
		printf( "width is %u, height is %u\n", header -> biWidth, header -> biHeight );
		return true;
	} else {
		return false;
	}
}

