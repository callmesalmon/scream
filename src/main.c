#include "scream.h"

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("USAGE: scream <file>\n");
        return 1;
    }
    FILE *file_ptr;
    char buf[16384];

    file_ptr = fopen(argv[1], "r");

    if (NULL == file_ptr) {
        printf("File can't be opened \n");
    }

    while (fgets(buf, 16384, file_ptr) != NULL) {}
	
	char *input = "";
	expr(buf, input);
	return 0;
}
