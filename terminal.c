#include"types.h"
uint8_t terminal(struct ST_cardData_t *c, struct ST_terminalData_t *t) {
    printf("\nPlease enter terminal data:\n");
    printf("Please Enter the transaction Amount:\n");
    scanf("%lf", &t->transAmount);
   
    if (t->transAmount > t->maxTransAmount) {
        printf("The Transaction is declined.\n");
        printf("Error! Transaction Amount is greater then Maximum Transaction Amount\n");
        return -1;
    }   
        printf("Please Enter transaction Date:\t\t (DD/MM/YYYY)\n");
        scanf(" %s", t->transactionDate);
       
        uint8_t dateValidation = checkDate(c->cardExpirationDate, t->transactionDate);
        if (dateValidation == 0) {
            printf("The Transaction is declined\n");
            printf("Error! Card is Expired!\n");
            return -1;
        }
        return 1;
    }
    
uint8_t checkDate(uint8_t expirationDate[6], uint8_t terminalDate[11]){
   
    uint8_t *expirationDateYears  = &expirationDate[3];
    uint8_t *expirationDateMonths = &expirationDate[0];
    uint8_t *terminalDateYears    = &terminalDate[8];
    uint8_t *terminalDateMonths   = &terminalDate[3];
    uint32_t expirationDateInt = 100*atoi( expirationDateYears) + atoi(expirationDateMonths);
    uint32_t terminalDateInt = 100*atoi(terminalDateYears)+atoi(terminalDateMonths);
    
    if(terminalDateInt < expirationDateInt) return 1;
    else return 0;
}

