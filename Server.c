#include "server.h"
#include <stdio.h>
#include <string.h>


ST_accountsDB_t AccounstDataBase[255] = { {5000.00,"5432851432568542",0},{1000.00,"7524685214538526",0}
										,{3000.00,"5426842695173546",1} };

ST_transaction_t transactionsDataBase[255] = { 0 };

int acc_num = 0;
int trans_num = 1;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t Trans_state = 0;

	if (isValidAccount(&transData->cardHolderData) == Blocked_Account)
	{
		Trans_state = Declined_Stolen_Card;
		transactionsDataBase[trans_num].transState = Trans_state;
		if (saveTransaction(transData) == Saving_Failed)
		{
			return Internal_Server_Error;
		}
		else
		{
			return Declined_Stolen_Card;
		}
	}
	if (isValidAccount(&transData->cardHolderData) == Account_Not_Found)
	{
		Trans_state = Declined_Invalid_Card;
		transactionsDataBase[trans_num].transState = Trans_state;
		if (saveTransaction(transData) == Saving_Failed)
		{
			return Internal_Server_Error;
		}
		else
		{
			return Declined_Invalid_Card;
		}
	}
	if (isAmountAvailable(&transData->terminalData) == Low_Balance)
	{
		Trans_state = Declined_Insuffecient_Fund;
		transactionsDataBase[trans_num].transState = Trans_state;
		if (saveTransaction(transData) == Saving_Failed)
		{
			return Internal_Server_Error;
		}
		else
		{
			return Declined_Insuffecient_Fund;
		}
	}
	else
	{
		Trans_state = Approved;
		transactionsDataBase[trans_num].transState = Trans_state;
		if (saveTransaction(transData) == Saving_Failed)
		{
			return Internal_Server_Error;
		}
		else
		{
			printf("Your Card had a successful transaction of %.2f\n", transData->terminalData.transAmount);
			AccounstDataBase[acc_num].balance = (AccounstDataBase[acc_num].balance - transData->terminalData.transAmount);
			printf("Your new available balance is %.2f\n", AccounstDataBase[acc_num].balance);
			return Approved;
		}
	}		
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (acc_num = 0; acc_num < 255; acc_num++)
	{
		if (strcmp(cardData->primaryAccountNumber, AccounstDataBase[acc_num].primaryAccountNumber) == 0)
		{
			if ((AccounstDataBase[acc_num].status) == 0)
			{
			return Server_Ok;
			}
			else 
			{
			return Blocked_Account;
			}
		}	
	}
			return Account_Not_Found;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount <= AccounstDataBase[acc_num].balance)
	{
		return Server_Ok;
	}
		return Low_Balance;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{	

	transData->transactionSequenceNumber = trans_num ;
	for (trans_num = 1; trans_num < 255; trans_num++)
	{
		memcpy(transactionsDataBase[trans_num].cardHolderData.cardHolderName,transData->cardHolderData.cardHolderName,sizeof(transData->cardHolderData.cardHolderName));
		memcpy(transactionsDataBase[trans_num].cardHolderData.primaryAccountNumber,transData->cardHolderData.primaryAccountNumber, sizeof(transData->cardHolderData.primaryAccountNumber));
		memcpy(transactionsDataBase[trans_num].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate, sizeof(transData->cardHolderData.cardExpirationDate));
		memcpy(transactionsDataBase[trans_num].terminalData.transactionDate , transData->terminalData.transactionDate,sizeof(transData->terminalData.transactionDate));
		transactionsDataBase[trans_num].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		transactionsDataBase[trans_num].terminalData.transAmount = transData->terminalData.transAmount;
		transactionsDataBase[trans_num].transactionSequenceNumber = trans_num;
	
		FILE* in;
		in = fopen("D:\\Menna Elkhwass\\resubmission menna_elkhwass Payment App\\Payment Application Project\\Transaction DB.txt", "w+");
	//	fprintf(in, "NAME: %s\nPAN: %s\nEXP Date: %s\nTrans.Date: %s\nMax Amount: %.2f\nTrans.Amount: %.2f\nTrans.State: %d\nTrans.NO: %d",
			transactionsDataBase[trans_num].cardHolderData.cardHolderName,
			transactionsDataBase[trans_num].cardHolderData.primaryAccountNumber,
			transactionsDataBase[trans_num].cardHolderData.cardExpirationDate,
			transactionsDataBase[trans_num].terminalData.transactionDate,
			transactionsDataBase[trans_num].terminalData.maxTransAmount,
			transactionsDataBase[trans_num].terminalData.transAmount,
			transactionsDataBase[trans_num].transState,
	//		transactionsDataBase[trans_num].transactionSequenceNumber);

		fseek(in, 0, Seek_End);
		int in_size = ftell(in);
		if (in_size == 0)
		{
			return Saving_Failed;
		}
		else
		{
			return Server_Ok;
		}
		fclose(in);
	}
		return Saving_Failed;	
}

EN_serverError_t getTransaction(ST_transaction_t* transData)
{
	int cmd;
	printf("Press (1) to get the Transaction's Data\nPress (0) to Exit\n");
	scanf_s("%d", &cmd);
	if (cmd == 1)
	{
		FILE* in;
		in = fopen("D:\\Menna Elkwass\\resubmission menna_elkhwass; Payment App\\Payment Application Project\\Transaction DB.txt", "r+");

		char single_line[100];
		while (!feof(in))
		{
			fgets(single_line, 100, in);
			puts(single_line);
		}
		fclose(in);
		printf("THANK YOU!\n");
		return 0;
	}
	if (cmd == 0)
	{
		printf("THANK YOU!\n");
	}
	else
	{
		printf("Wrong \n");
		return getTransaction(transData);
	}
}
