#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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
	int price = 0;
	if (product == "candies") {
		price = 1;
	}
	if (product == "car") {
		price = 30000;
	}
	if (product == "pen") {
		price = 40;
	}
	if (product == "book") {
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
