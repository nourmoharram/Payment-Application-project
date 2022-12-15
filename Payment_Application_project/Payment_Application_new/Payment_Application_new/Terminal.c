#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Card.h"
#include"Terminal.h"
typedef struct tm Date;
/*array to carry data of terminal during transactions*/
ST_terminalData_t Terminal_data_holder[4];
ST_terminalData_t* ptr_to_terminal = &Terminal_data_holder;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t Error_type = TERMINAL_OK;
	time_t Current_time = time(NULL);
	Date* Current_t = localtime(&Current_time);
	uint32_t day;
	uint32_t month;
	uint32_t year;
	uint32_t day_tenth;
	uint32_t day_unit;
	uint32_t month_tenth;
	uint32_t month_unit;
	uint32_t year_thousand;
	uint32_t year_hundred;
	uint32_t year_tenth;
	uint32_t year_unit;

	day = Current_t->tm_mday;

	month = Current_t->tm_mon + 1; /*since months start count by january equal 0*/

	year = Current_t->tm_year + 1900; /*since it counts year from 1900 so we add 1900 to get current year*/

	day_tenth = day / 10 + 48; /*divide day by 10 to get the tenth number of day*/
	day_unit = day % 10 + 48; /*the modules of day value will get the value of unit number of days*/
	
	month_tenth = month / 10 + 48; /*divide month by 10 to get the tenth number of month*/
	month_unit = month % 10 + 48; /*the modules of month value will get the value of unit number of month*/

	year_thousand= year / 1000 + 48;  /*divide by 1000 to get the thousand number */
	year_hundred= (year / 100) % 10 + 48; /*divide by 100 to get 20 and then modulas 20 equal 0*/
	year_tenth= (year / 10) % 10 + 48;   /*divide by 10 to get 202 and modulas of 202 equal 2*/
	year_unit= year % 10 + 48;          /*modulas of 2022 by 10 equal 2*/

	/*store every time in its element in the array of transaction date*/
	/*48 represent '0' in ascii*/
	termData->transactionDate[0] = day_tenth;
	termData->transactionDate[1] = day_unit;
	/*'/' equal 47 in ascii table*/
	termData->transactionDate[2] = 47;

	termData->transactionDate[3] = month_tenth;
	termData->transactionDate[4] = month_unit;

	/*'/' equal 47 in ascii table*/
	termData->transactionDate[5] = 47;

	termData->transactionDate[6] = year_thousand;
	termData->transactionDate[7] = year_hundred;
	termData->transactionDate[8] = year_tenth;
	termData->transactionDate[9] = year_unit;

	termData->transactionDate[10] = '\0';   /*end of array of string*/

	return Error_type;
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t Error_type = 0;
	uint8_t Expiration_year_date;
	uint8_t Transaction_year_date;
	uint8_t Expiration_month_date;
	uint8_t Transaction_month_date;
	/*sum the values of MM/YY of both expiration date and transaction date to be compared with each other*/
	Expiration_month_date = (cardData->cardExpirationDate[0]) + (cardData->cardExpirationDate[1]);
	Transaction_month_date = (termData->transactionDate[3]) + (termData->transactionDate[4]);
	Expiration_year_date = (cardData->cardExpirationDate[3]) + (cardData->cardExpirationDate[4]);
	Transaction_year_date = (termData->transactionDate[8]) + (termData->transactionDate[9]);

	if (Expiration_year_date < Transaction_year_date)
	{
		printf("card is expired! \n");
		Error_type = EXPIRED_CARD;
	}
	else if (Expiration_year_date == Transaction_year_date)
	{
		if (Expiration_month_date < Transaction_month_date)
		{
			printf("card is expired! \n");
			Error_type = EXPIRED_CARD;
		}
		else
		{
			printf("card is valid \n");
			Error_type = TERMINAL_OK;
		}
	}
	else
	{
		printf("card is valid \n");
		Error_type = TERMINAL_OK;
	}
	return Error_type;

}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t Error_type = 0;
	float transaction_value = 0;
	printf("enter the value of transaction \n");
	scanf_s("%f", &transaction_value);
	/*check the value of transaction*/
	if (transaction_value <= 0)
	{
		printf("Invalid transaction value \n");
		Error_type = INVALID_AMOUNT;
	}
	else
	{
		printf("valid transaction value \n");
		termData->transAmount = transaction_value;
		Error_type = TERMINAL_OK;
	}
	return Error_type;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData,float maxAmount)
{
	EN_terminalError_t Error_type = 0;
	
	if (maxAmount <= 0)
	{
		printf("Invalid  maximum amount \n");
		Error_type = INVALID_MAX_AMOUNT;
	}
	else
	{
		printf("the maximum amount of transaction is:%0.1f \n",maxAmount);
		termData->maxTransAmount = maxAmount;
		Error_type = TERMINAL_OK;
	}
	return Error_type;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t Error_type = 0;

	if (termData->transAmount > termData->maxTransAmount)
	{
		printf("entered transaction amount exceeded the max allowed amount \n");
		Error_type = EXCEED_MAX_AMOUNT;

	}
	else
	{
		printf("entered transaction amount not exceeded the max allowed amount \n");
		Error_type = TERMINAL_OK;
	}
	return Error_type;
}
