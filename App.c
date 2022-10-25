#include "app.h"
#include "../Card/card.h"
#include "../server/server.h"
#include "../terminal/terminal.h"
#include <stdio.h>
#include <string.h>


int main()
{
	appStart();
}

	void appStart()
	{
		ST_cardData_t card_data;
		ST_cardData_t* cardData = &card_data;

		if (getCardHolderName(cardData) == Wrong_Name)
		{
			printf("It is a wrong name!");
			return 0;
	    }
		if (getCardExpiryDate(cardData) == Exp_Date)
		{
			printf("It is an experied date!");
			return 0;
		}
		if (getCardPan(cardData) == Wrong_Pan)
		{
			printf("It is a wrong pan!");
			return 0;
		}

		ST_terminalData_t term_data;
		ST_terminalData_t* termData = &term_data;

		if (getTransactionDate(termData) == Wrong_Date)
		{
			printf("It is a wrong date!");
			return 0;
		}
		if (isCardExpired(card_data, term_data) == Expired_Card)
		{
			printf("Your card is expired.");
			return 0;
		}
		if (setMaxAmount(termData) == Invalid_Max_Amount)
		{
			printf("Your amount is invalid max amount.");
			return 0;
		}
		if (getTransactionAmount(termData) == Invalid_Amount)
		{
			printf("The amount is invalid.");
			return 0;
		}
		if (isBelowMaxAmount(termData) == Exceed_Max_Amount)
		{
			printf("You exceed the max amount.");
			return 0;
		}
	
    

		ST_transaction_t trans_Data;
		ST_transaction_t* transData = &trans_Data;
		
		transData->cardHolderData = card_data;
		transData->terminalData = term_data;	
	
		EN_transState_t recieveData;

		recieveData= recieveTransactionData(transData);
		
			if (recieveData == Declined_Stolen_Card)
			{
				printf("It's a declined stolen card.");
				return 0;
			}

			else if (recieveData == Declined_Invalid_Card)
			{
				saveTransaction(transData);
				printf("It's a declined invalid card.");
				return 0;
			}

			else if (recieveData == Declined_Insuffecient_Fund)
			{
				saveTransaction(transData);
				printf("It is a declined insuffecient fund.");
				return 0;
			}

			else if (recieveData == Internal_Server_Error)
			{
				saveTransaction(transData);
				printf("It is an internal server error.");
				return 0;
			}

			else (recieveData == Approved);
			{
					printf("Successfull Transaction\n");
					getTransaction(transData);
					return 0;
			}
	}
