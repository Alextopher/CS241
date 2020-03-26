#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void btoa ( FILE *ifp, FILE *ofp );

int main( int argc, char *argv[] ) {
	FILE *ifp, *ofp;

	if (argc < 3) {
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}
	if (!(ifp = fopen(argv[1],"r"))) {
		fprintf(stderr,"Cannot open file %s\n",argv[1]);
	  	exit(1);
	}
	if (!(ofp = fopen(argv[2],"w"))) {
		fprintf(stderr,"Cannot open file %s\n",argv[2]);
		exit(1);
	}

	btoa(ifp, ofp);

	return 0;
}

void btoa( FILE *ifp, FILE *ofp ) {
	char c;

	char byte = 0;
	unsigned char mask = 1 << 7;

	while ((c = fgetc(ifp)) != EOF) {
		if (c == '1') {
			byte |= mask;
		}

		if (!(mask >>= 1)) {
			fputc(byte, ofp);
			byte = 0;
			mask = 1 << 7;
		}
	}
}

