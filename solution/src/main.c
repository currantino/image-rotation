#include <stdio.h>
#include <stdbool.h>

#include "bmp.h"
#include "util.h"
#include "bmp_header.h"

void usage() {
	fprintf(stderr, "Usage: ./build/image-transformer BMP_FILE_NAME BMP_FILENAME\n");
}

int main( int argc, char** argv ) {
    (void) argc; (void) argv; // supress 'unused parameters' warning
	//if (argc != 3) usage();
	// if (argc < 3) err("Not enough arguments \n");
	//if (argc > 3) err("Too many arguments \n");
	struct bmp_header* header = malloc(sizeof(struct bmp_header));
	read_header_from_file( argv[1], header);	
	
    return 0;
}
