#include<stdio.h>
#include<stdlib.h>

typedef struct Pocket {
	// The RandomAccessFile of Pocket
	FILE *fp;
} Pocket;

void Pocket__init(Pocket* self, FILE *fp) {
	fp = fopen("pocket.txt", "r+");
	self->fp = fp;
}

// Creates a Pocket object that interfaces with the
// Pocket RandomAccessFile
Pocket* Pocket__create() {
	FILE *fp;
	Pocket* result = (Pocket*) malloc(sizeof(Pocket));
	Pocket__init(result, fp);
	return result;
}

// Add a product to the pocket
void addProduct(Pocket *self, char* product) {
	fputs(product, self->fp);
	fputs("\n", self->fp);
}

// CLose the file
void Pocket__close(Pocket* self) {
	fclose(self->fp);
}

// for testing purposes
/*int main() {
	Pocket *pocket = Pocket__create();
	addProduct(pocket, "book");
	addProduct(pocket, "pen");
	return 0;
}*/
