#include<stdio.h>
#include<stdlib.h>
#include"App.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

float MAX_ALLOWED_AMOUNT = 10000;
int counter = 0;
uint8_t flag = 1;
int main()
{
	int decision;
	while (1)
	{
		printf("write 1 to start program or write anything to end program \n");
		scanf_s("%d", &decision);
		system("cls");

		if (decision == 1)
		{
			appStart();
			printf("write 1 to return to main menu or write 0 to end program \n");
			scanf_s("%d", &decision);
			if (decision == 0)
			{
				printf("program ended \n");
				break;
			}

		}
		else
		{
			printf("program ended \n");
			break;
		}
	}
}
void appStart(void)
{
	system("cls");
	counter++;

	do
	{
		Card_Name_return = getCardHolderName(ptr_to_card);
		system("cls");
	} while (Card_Name_return != CARD_OK);
	printf("********************************************************* Transaction number %d******************************************\n", counter);
	do
	{
		Card_expirydate_return = getCardExpiryDate(ptr_to_card);
	} while (Card_expirydate_return != CARD_OK);
	do
	{
		Card_PAN_return = getCardPAN(ptr_to_card);
	} while (Card_PAN_return != CARD_OK);
	date_return = getTransactionDate(ptr_to_terminal);
	if (date_return != TERMINAL_OK)
	{
		printf("System time failed! \n");
	}
	else
	{
		is_cardxpired_return = isCardExpired(ptr_to_card, ptr_to_terminal);
		if (is_cardxpired_return != TERMINAL_OK)
		{
			printf("Card is Expired Please go to bank and Renew the card! \n");
		}
		else
		{
			do
			{
				get_transacamount_return = getTransactionAmount(ptr_to_terminal);
			} while (get_transacamount_return != TERMINAL_OK);
			set_max_return = setMaxAmount(ptr_to_terminal, MAX_ALLOWED_AMOUNT);
			if (set_max_return != TERMINAL_OK)
			{
				printf("invalid Maximum amount value of transactions \n");
			}
			else
			{
				is_below_max_amount_return = isBelowMaxAmount(ptr_to_terminal);
				if (is_below_max_amount_return == EXCEED_MAX_AMOUNT)
				{
					printf("transaction amount exceeded maximum amount allowed ! \n");
				}
				else
				{
					recieveTransactionData(ptrtoTransaction);
					saveTransaction(ptrtoTransaction);
				}
			}
		}
	}
}
