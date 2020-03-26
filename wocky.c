#include <stdio.h>
#include <stdlib.h>

void wocky ( FILE *ifp, FILE *ofp );

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

	wocky(ifp, ofp);

	return 0;
}

typedef struct element_t {
	char c;
	struct element_t * prefix;
} element;

element * new_element( element * prefix, char c ) {
	element * e = malloc(sizeof(element));

	e -> prefix = prefix;
	e -> c = c;

	return e;
}

// Print a prefix using some recursion
void fprint_element(FILE *fp, element * e) {
	if (e -> prefix != NULL) {
		fprint_element(fp, e -> prefix);
		fputc(e -> c, fp);
	}
}

void wocky ( FILE *ifp, FILE *ofp ) {
	// Read the entire file into a buffer
        fseek(ifp, 0L, SEEK_END);
        long sz = ftell(ifp);
        rewind(ifp);

        char * buffer = malloc(sz);
        fread(buffer, 1, sz, ifp);

	// Start the table of prefixes
	element ** table = malloc(sizeof(element*));
	table[0] = new_element(NULL, '\0');
	int t_length = 1;
	int t_capacity = 1;

	int index = 0; // Index of prefix
	int length = 0; // Number of bits index will be represented in
	int read = 0; // Number of bits currently read

	char c;
	for (int i = 0; i <= sz; ++i) {
		c = buffer[i];
		if (read == length) {
			// Print prefix at index
			fprint_element(ofp, table[index]);

			// Grow table if full
			if (t_length == t_capacity) {
				// Double capacity
				element ** new_table = malloc(2 * t_capacity * sizeof(element*));
				for (int j = 0; j < t_capacity; ++j) {
					new_table[j] = table[j];
				}
				free(table);
				table = new_table;
				t_capacity *= 2;
			}

			// Add new prefix
			table[t_length++] = new_element(table[index], c);
			element * e = table[t_length - 1];

			// Print bit
			fputc(c, ofp);

			// Length increases when max index requires more bits to represent
			if ((t_length - 1) & (1 << length) || length == 0) {
				++length;
			}
			read = 0;
		       	index = 0;
		} else {
			++read;
			if (c == '1') {
				index += 1 << (length - read);
			}
		}
	}
}
