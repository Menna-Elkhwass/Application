#include"types.h"
void card(struct ST_cardData_t *client) {
    printf("Please enter card data:\n");
    printf("Please enter card holder name:\n");
    scanf( "%[^\n]%*c",client->cardHolderName);
    printf("Please enter account number:\n");
    scanf(" %s", client->primaryAccountNumber);
    printf( "Please enter card Expiry Date:\t\t(MM/YY)\n");
    scanf(" %s",client->cardExpirationDate);
}
