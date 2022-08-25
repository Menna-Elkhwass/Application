#include "types.h"
struct ST_accountBalance_t dataBase[] =
        {
                {"123456789", 150.00},
                {"234567891",5500.00},
                {"579871234",2350.25},
                {"456758321",1500.12},
                {"258649173",500.00},
                {"654823719",2550.00},
                {"971462485",0.00},
                {"794149625",1.00 },
                {"123032456", 25.12},
                {"456987321", 0.55},
        };

void clear (struct ST_cardData_t *c, struct ST_terminalData_t *t);
int main() {
        struct ST_cardData_t c = {"", "", ""};
        struct ST_terminalData_t t = {0.0, 6000.0, ""};
        uint8_t userInput = 'y';
        struct ST_cardData_t *cptr = &c;
        struct ST_terminalData_t *tptr = &t;
        printf("\t\tWelcome\n");
        while(userInput == 'y'){
            card(cptr);
            uint8_t result = terminal(cptr, tptr);
            if (result == 1)
                result = server(dataBase, cptr, tptr);
            if (result != 255) {
                dataBase[result].balance = dataBase[result].balance - t.transAmount;
        }
        printArray(dataBase, 10);
        clear(cptr, tptr);
        printf("Do you want to continue (y/n)?\n");
        scanf(" %c", &userInput);
        }
}
void clear (struct ST_cardData_t *c, struct ST_terminalData_t *t){
    memset(c->primaryAccountNumber,0, 20);
    memset(c->cardHolderName,0, 25);
    memset(c->cardExpirationDate,0, 6);
    memset(t->transactionDate,0,11);
    t->transAmount = 0.0;
    t->maxTransAmount = 6000;
}
