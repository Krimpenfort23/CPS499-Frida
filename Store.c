#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Store {
	// The list of products sold in the store
	char *list;
} Store;

void Store__init(Store* self) {
	self->list = "candies - 1\ncar - 30000\npen - 40\nbook - 100    \n";
	printf("%s", self->list);
}

Store* Store__create() {
	Store* result = (Store*) malloc(sizeof(Store));
	Store__init(result);
	return result;
}

//Returns the price of a particular product
int getPrice(Store *self, char *product) {
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
	Store *store = Store__create();
	printf("%d\n", getPrice(store, "candies"));
	return 0;
}*/
