#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void atob ( FILE *ifp, FILE *ofp );

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

	atob(ifp, ofp);

	return 0;
}

void atob ( FILE *ifp, FILE *ofp ) {
	char c;
	while ((c = fgetc(ifp)) != EOF) {
		char i;
		for (i = 7; i >= 0; --i) {
			fputc('0' + (c >> i & 1), ofp);
		}
	}
}
