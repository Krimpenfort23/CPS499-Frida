/**
 * ShoppingCart.c
 * @author: Evan Krimpenfort
 *          Anna Duricy
 */

#include "ShoppingCart.h"
#include "Store.c"
#include "Wallet.c"
#include "Pocket.c"
#define BUFSIZE 1024

/*
 * error - wrapper for perror
 */
void error(char *message) 
{   
    perror(message);
    exit(1);
}

/*
 * Main routine
 */
int main(int argc, char **argv) 
{
    int parentfd = 0; /* parent socket */
    int childfd = 0; /* child socket */
    int port = 0; /* port to listen on */
    int clientlen = 0; /* byte size of client's address */
    int optval = 0; /* flag value for setsockopt */
    int n = 0; /* message byte size */
    char buf[BUFSIZE]; /* message buffer */
    char *hostaddrp; /* dotted decimal host addr string */
    struct sockaddr_in serveraddr; /* server's addr */
    struct sockaddr_in clientaddr; /* client addr */
    struct hostent *hostp; /* client host info */

    /* 
     * check command line arguments 
     */
    if (argc != 2) 
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    port = atoi(argv[1]);

    parentfd = socket(AF_INET, SOCK_STREAM, 0); /* socket: create the parent socket */
    if (parentfd < 0) { error("ERROR opening socket"); }

    /* 
     * setsockopt: Handy debugging trick that lets 
     * us rerun the server immediately after we kill it; 
     * otherwise we have to wait about 20 secs. 
     * Eliminates "ERROR on binding: Address already in use" error. 
     */
    optval = 1;
    setsockopt(parentfd, 
               SOL_SOCKET, 
               SO_REUSEADDR, 
               (const void *)&optval, 
               sizeof(int));

    bzero((char *) &serveraddr, sizeof(serveraddr));    /* build the server's Internet address */
    serveraddr.sin_family = AF_INET;                    /* this is an Internet address */
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);     /* let the system figure out our IP address */
    serveraddr.sin_port = htons((unsigned short)port);  /* this is the port we will listen on */

    if (bind(parentfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)    /* bind: associate the parent socket with a port */
    {
        error("ERROR on binding");
    }

    /* 
     * listen: make this socket ready to accept connection requests 
     */
    if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ 
    {
        error("ERROR on listen");
    }

    /* 
    * main loop: wait for a connection request, echo input line, 
    * then close connection.
    */
    clientlen = sizeof(clientaddr);
    printf("ShoppingCart program is running on port (%d)\n", port);
    printf("Waiting for connections from Clients...\n");
    while (1) 
    {
        /* 
         * accept: wait for a connection request 
         */
        childfd = accept(parentfd, (struct sockaddr *) &clientaddr, &clientlen);
        if (childfd < 0) { error("ERROR on accept"); }
        else { printf("Customer Connected!\n"); }
        
        /* 
         * gethostbyaddr: determine who sent the message 
         */
        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == NULL) { error("ERROR on gethostbyaddr"); }

        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == NULL) { error("ERROR on inet_ntoa\n"); }

        /*
         * Create the store, wallet, and pocket
         */
        Store_t store = *Store__create();
        Wallet_t wallet = *Wallet__create();
        Pocket_t pocket = *Pocket__create();

        /*
         * write: send over the available items.
         */ 
        int balance = getBalance(&wallet);
        Wallet__close(&wallet);
        bzero(buf, BUFSIZE);
        strcpy(buf, "Welcome to Evan Krimpenfort's ShoppingCart.\nPlease select your product:\n");
        write(childfd, buf, strlen(buf));
        bzero(buf, BUFSIZE);
        strcpy(buf, printItems(&store));
        write(childfd, buf, strlen(buf));
        bzero(buf, BUFSIZE);
        sprintf(buf, "Your balance is $%d.\n", balance);
        write(childfd, buf, strlen(buf));
        bzero(buf, BUFSIZE);
        strcpy(buf, "What do you want to buy, type e.g., pen?\n");
        write(childfd, buf, strlen(buf));

        /* 
         * read: read input string from the client
         */
        bzero(buf, BUFSIZE);
        read(childfd, buf, BUFSIZE);
        char* product[BUFSIZE];
        strcpy(product, buf);
        int price = getPrice(&store, product);
        if (price == 0) 
        { 
            bzero(buf, BUFSIZE);
            strcpy(buf, "That Item is not available. Pick another item.\n");
            write(childfd, buf, BUFSIZE);
        }
        else
        {
            addProduct(&pocket, product);
            Pocket__close(&pocket);

            setBalance(&wallet, balance-price); 
            Wallet__close(&wallet);

            /*
             * write: tell the client they can purchase the item.
             */
            bzero(buf, BUFSIZE);
            sprintf(buf, "You have successfully purchased a %s.\nYour new balance is now $%d\n", product, balance-price);
            write(childfd, buf, BUFSIZE);
        }
        
        close(childfd);
    }
}
