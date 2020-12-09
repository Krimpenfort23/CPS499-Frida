#include <stdio.h>
#include <stdlib.h>

typedef struct Pocket {
	// The RandomAccessFile of Pocket
	FILE *fp;
} Pocket_t;

void Pocket__init(Pocket_t* self, FILE *fp) {
	fp = fopen("pocket.txt", "a+");
	self->fp = fp;
}

// Creates a Pocket object that interfaces with the
// Pocket RandomAccessFile
Pocket_t* Pocket__create() {
	FILE *fp;
	Pocket_t* result = (Pocket_t*) malloc(sizeof(Pocket_t));
	Pocket__init(result, fp);
	return result;
}

// Add a product to the pocket
void addProduct(Pocket_t *self, char* product) {
	fputs(product, self->fp);
	fputs("\n", self->fp);
}

// CLose the file
void Pocket__close(Pocket_t* self) {
	fclose(self->fp);
}

// for testing purposes
int main() {
	Pocket_t *pocket = Pocket__create();
	addProduct(pocket, "book");
	addProduct(pocket, "pen");
	return 0;
}
