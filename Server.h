#pragma once
#ifndef Server_h
#define Server_h
#include "../Card/card.h"
#include "../terminal/terminal.h"
typedef enum EN_transState_t
{
	Approved, Declined_Insuffecient_Fund, Declined_Stolen_Card, Internal_Server_Error , Declined_Invalid_Card
}EN_transState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;
typedef enum EN_Status_t
{
	Active, Blocked
}EN_Status_t;
typedef struct ST_accountsDB_t
{
	float balance;
	uint8_t primaryAccountNumber[20];
	EN_Status_t status;
}ST_accountsDB_t;
typedef enum EN_serverError_t
{
	Server_Ok, Saving_Failed, Transaction_Not_Found, Account_Not_Found, Low_Balance , Blocked_Account
}EN_serverError_t;
EN_transState_t  recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(ST_transaction_t* transData);

#endif
