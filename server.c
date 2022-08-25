#include"types.h"

uint8_t server(struct ST_accountBalance_t *dataBase,struct ST_cardData_t *card, struct ST_terminalData_t *t) {
    uint8_t result = linearSearch(dataBase, 10, card->primaryAccountNumber);
  
    if (result == (255)) {
        printf("The Transaction is declined\n");
        printf("Error! Account is not found !\n");
        return -1;
    }
   
    if(dataBase[result].balance < t->transAmount){
        printf("The Transaction is declined\n");
        printf("Error! Transaction amount is greater than Account Balance.\n");
        return -1;
    }
    printf("The Transaction is APPROVED.\n");
    return result;

}
