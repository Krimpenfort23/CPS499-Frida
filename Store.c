#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Store {
	// The list of products sold in the store
	char *list;
} Store_t;

void Store__init(Store_t* self) {
	self->list = "candies - 1\ncar - 30000\npen - 40\nbook - 100    \n";
}

Store_t* Store__create() {
	Store_t* result = (Store_t*) malloc(sizeof(Store_t));
	Store__init(result);
	return result;
}

char* printItems(Store_t* self) {
	return self->list;
}

//Returns the price of a particular product
int getPrice(Store_t *self, char *product) {
	*(product+strlen(product)-2) = '\0'; // length correction...
	int price = 0;
	if (strcmp(product,"candies") == 0) {
		price = 1;
	}
	else if (strcmp(product,"car") == 0) {
		price = 30000;
	}
	else if (strcmp(product,"pen") == 0) {
		price = 40;
	}
	else if (strcmp(product,"book") == 0) {
		price = 100;
	}
	return price;
}

// for testing purposes
/*int main() {
	Store_t *store = Store__create();
	printf("%d\n", getPrice(store, "candies"));
	printItems(store);
	return 0;
}*/
