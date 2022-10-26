#pragma once
#ifndef Terminal_h
#define Terminal_h

#include <stdint.h>
#include "../Card/card.h"
 
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t; 

typedef enum EN_terminalError_t
{
	Terminal_Ok, Wrong_Date, Expired_Card, Invalid_Card, Invalid_Amount, Exceed_Max_Amount, Invalid_Max_Amount
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif
