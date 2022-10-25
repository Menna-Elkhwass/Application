#include "card.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MaxCardHolderName 24 
#define MinCardHolderName 20
#define CardExpireDate 5
#define MaxPAN 19
#define MinPAN 16

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Enter Cardholder's name: ");
	scanf_s("%[^\n]s", cardData->cardHolderName, MaxCardHolderName + 1);
	int n = strlen(cardData->cardHolderName);
	int i = 0;
	while (i < n)
	{
		if ((cardData->cardHolderName[i] >= 'a' && cardData->cardHolderName[i] <= 'z')
			|| (cardData->cardHolderName[i] >= 'A' && cardData->cardHolderName[i] <= 'Z')
			|| (cardData->cardHolderName[i] == ' '))
		{
			i++;
		}
		else
		{
			return Wrong_Name;
		}
	}
	if ((strlen(cardData->cardHolderName) > MaxCardHolderName) || (strlen(cardData->cardHolderName) < MinCardHolderName)
		|| (strlen(cardData->cardHolderName) == NULL))
	{
		return Wrong_Name;
	}
	else
	{
		char name[25];
		strcpy(name, cardData->cardHolderName);
		char* FirstName = strtok(name, " ");
		printf("hello %s\n", FirstName);
		return Card_Ok;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Enter Card Expire date MM/YY: ");
	scanf_s("%s", &cardData->cardExpirationDate, CardExpireDate + 1);

	if ((strlen(cardData->cardExpirationDate) != CardExpireDate)
		|| (strlen(cardData->cardExpirationDate) == NULL)
		|| (cardData->cardExpirationDate[2] != '/')
		|| (cardData->cardExpirationDate[0] > '1')
		|| ((cardData->cardExpirationDate[0] == '0') && (cardData->cardExpirationDate[1] == '0'))
		|| ((cardData->cardExpirationDate[0] == '1') && (cardData->cardExpirationDate[1] > '2'))
		|| (isdigit(cardData->cardExpirationDate[0]) == 0) || (isdigit(cardData->cardExpirationDate[1]) == 0)
		|| (isdigit(cardData->cardExpirationDate[3]) == 0) || (isdigit(cardData->cardExpirationDate[4]) == 0))
	{
		return Exp_Date;
	}
	else
	{
		return Card_Ok;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Enter Card's PAN: ");

	scanf_s("%s", &cardData->primaryAccountNumber, MaxPAN + 1);

	// Check that the whole PAN is Numbers.
	int m = strlen(cardData->primaryAccountNumber);
	int j = 0;
	while (j < m)
	{
		if ((cardData->primaryAccountNumber[j] >= '0' && cardData->primaryAccountNumber[j] <= '9'))
		{
			j++;
		}
		else
		{
			return Wrong_Pan;
		}
	}
	if ((strlen(cardData->primaryAccountNumber) > MaxPAN)
		|| (strlen(cardData->primaryAccountNumber) < MinPAN)
		|| (strlen(cardData->primaryAccountNumber) == NULL))
	{
		return Wrong_Pan;
	}
	else
	{
		return Card_Ok;
	}
}
