#include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DateOfTransaction 10

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("Enter Transaction date DD/MM/YYYY: ");
	scanf_s("%s", &termData->transactionDate, DateOfTransaction + 1 );

	if ((strlen(termData->transactionDate) != DateOfTransaction)
		|| (strlen(termData->transactionDate) == NULL)
		|| ((termData->transactionDate[2]) != '/')
		|| ((termData->transactionDate[5]) != '/')
		|| (termData->transactionDate[0]>'3')
		|| ((termData->transactionDate[0]=='0') && (termData->transactionDate[1]=='0'))
		|| ((termData->transactionDate[0]=='3') && (termData->transactionDate[1]>'1'))
    || (termData->transactionDate[3]>'1')
		|| ((termData->transactionDate[3]=='0') && (termData->transactionDate[4]=='0'))
		|| ((termData->transactionDate[3]=='1') && (termData->transactionDate[4]>'2'))	
		|| (isdigit(termData->transactionDate[0]) == 0) || (isdigit(termData->transactionDate[1]) == 0)
		|| (isdigit(termData->transactionDate[3]) == 0) || (isdigit(termData->transactionDate[4]) == 0)
		|| (isdigit(termData->transactionDate[6]) == 0) || (isdigit(termData->transactionDate[7]) == 0)
		|| (isdigit(termData->transactionDate[8]) == 0) || (isdigit(termData->transactionDate[9]) == 0))
		{
		return Wrong_Date;
		}
	else
	{
		return Terminal_OK;
	}		
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if ((termData.transactionDate[8]) > (cardData.cardExpirationDate[3]))
	{
		return Expired_Card;
	}
	else if ((termData.transactionDate[8]) == (cardData.cardExpirationDate[3]))	
	{
		if ((termData.transactionDate[9]) > (cardData.cardExpirationDate[4]))
		{
			return Expired_Card;
		}
		else if ((termData.transactionDate[9]) == (cardData.cardExpirationDate[4]))		
		{
			if ((termData.transactionDate[3]) > (cardData.cardExpirationDate[1]))
			{
				return Expired_Card;
			}
			else if ((termData.transactionDate[3]) == (cardData.cardExpirationDate[0]))
			{
				if ((termData.transactionDate[4]) > (cardData.cardExpirationDate[1]))
				{
					return Expired_Card;
				}
			}
		}

	}
	return Terminal_Ok;
}
		
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	return Terminal_Ok;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("Enter The MAX Transaction Amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
	{
		return Invalid_Max_Amount; 
	}
	else
	{
		return Terminal_Ok;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Enter Transaction Amount: ");
	scanf_s("%f", &termData->transAmount);
	if ((termData->transAmount) <= 0)
	{
		return Invalid_Amount;
	}
	return Terminal_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if((termData->transAmount) > (termData->maxTransAmount))
	{
		return Exceed_Max_Amount;
	}
	return Terminal_Ok;
}
