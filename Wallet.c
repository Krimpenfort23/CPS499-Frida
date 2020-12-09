#include <stdio.h>
#include <stdlib.h>

typedef struct Wallet {
	// The RandomAccessFile of Wallet
	FILE *fp;
} Wallet_t;

void Wallet__init(Wallet_t* self, FILE *fp) {
	fp = fopen("wallet.txt", "r+");
	self->fp = fp;
}

// Creates a Wallet object that interfaces with the
// Wallet RandomAccessFile
Wallet_t* Wallet__create() {
	FILE *fp;
	Wallet_t* result = (Wallet_t*) malloc(sizeof(Wallet_t));
	Wallet__init(result, fp);
	return result;
}

//Returns the balance of the wallet
int getBalance(Wallet_t *self) {
	// 10 is just arbitrary. I doubt we'll ever have more
	// in the wallet than that
	char c[10];
	fscanf(self->fp, "%[^\n]", c);
	return atoi(c);
}

// This is needed to create a perfectly-sized char. There are
// probably better ways of doing this, but this works.
int getBalanceLen(int balance) {
	int len = 1;
	while(balance > 9) {
		len++;
		balance/=10;
	}
	return len;
}
// Set a new balance in the wallet
void setBalance(Wallet_t *self, int balance) {
	// add the new balance
	char balanceStr[getBalanceLen(balance)];
	sprintf(balanceStr, "%d\n", balance);
	self->fp = fopen("wallet.txt", "w");
	fseek(self->fp, 0, SEEK_SET);
	fputs(balanceStr, self->fp);
}

// CLose the file
void Wallet__close(Wallet_t* self) {
	fclose(self->fp);
}

// for testing purposes
/*int main() {
	Wallet_t *wallet = Wallet__create();
	printf("%d\n", getBalance(wallet));
	setBalance(wallet, 1);
	return 0;
}*/
