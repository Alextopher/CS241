#include <stdio.h>
#include <stdlib.h>

void jabber ( FILE *ifp, FILE *ofp );

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

	jabber(ifp, ofp);

	return 0;
}

typedef struct node_t {
	int index;

	// Children
	struct node_t * zero;
	struct node_t * one;
} node;

node * new_node( int index ) {
	node * n = malloc(sizeof(node));

	n -> index = index;
	n -> zero = NULL;
	n -> one = NULL;

	return n;
}

void printTree(node * curr, int depth);

void jabber( FILE *ifp, FILE *ofp ) {
	// Read the entire file into a buffer
        fseek(ifp, 0L, SEEK_END);
        long sz = ftell(ifp);
        rewind(ifp);

        char * buffer = malloc(sz);
        fread(buffer, 1, sz, ifp);

	// Start the tree
	node * root = new_node(0);
	node * cursor = root;

	int index = 0;
       	int bits = 0;
	int i;
	for (i = 0; i < sz; ++i) {
		char c = buffer[i];

		if (c == '0') {
			if (cursor -> zero == NULL) {
				// Print index
				int j;
				for (j = bits - 1; j >= 0; --j) {
					fputc('0' + ((cursor -> index >> j) & 1), ofp);
				}
				
				// Append next bit
				fputc('0', ofp);
				
				// Create new node
				cursor -> zero = new_node(++index);
			} else {
				// Step down
				cursor = cursor -> zero;
				continue;
			}
		} else if (c == '1') {
			if (cursor -> one == NULL) {
				// Print index
				int j;
				for (j = bits - 1; j >= 0; --j) {
					fputc('0' + ((cursor -> index >> j) & 1), ofp);
				}
				
				// Append next bit
				fputc('1', ofp);
				
				// Create new node
				cursor -> one = new_node(++index);
			} else {
				// Step down
				cursor = cursor -> one;
				continue;
			}
		} else {
			fprintf(stderr, "Invalid character");
			exit(1);
		}

		// Update bits if needed
		if (1 << bits & index)
			++bits;

		// Reset the cursor
		cursor = root;
	}

	// Final index
	int j;
	for (j = bits - 1; j >= 0; --j) {
		fputc('0' + ((cursor -> index >> j) & 1), ofp);
	}

	//printTree(root, 0);
}


int rec[1];
//int rec[1000000];
void printTree(node * curr, int depth)
{
    int i;
    if(curr==NULL)return;
    printf("\t");
    for(i=0;i<depth;i++)
        if(i==depth-1)
            printf("%s---",rec[depth-1]?"L":"R");
        else
            printf("%s   ",rec[i]?"|":" ");
    printf("%d\n",curr->index);
    rec[depth]=1;
    printTree(curr->zero,depth+1);
    rec[depth]=0;
    printTree(curr->one,depth+1);
}
