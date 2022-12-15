#include<stdio.h>
#include"Server.h"

ST_cardData_t Card_test;
ST_terminalData_t Terminal_data_test;
ST_transaction_t TRANSACTION_DATA;
ST_accountsDB_t* accountRefrence;
float max_value=10000;
/*card functions test*/
void getCardHolderNameTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: getCardHolderName \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		getCardHolderName(&Card_test);
		/*Expected result is name is valid or name is invalid*/
	}


}
void getCardExpiryDateTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: getCardExpiryDate \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		getCardExpiryDate(&Card_test);
		/*Expected result is expiry date format is correct or is incorrect*/

	}
}
void getCardPANTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: getCardPANTest \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		getCardPAN(&Card_test);
		/*Expected result is PAN format is valid or invalid*/
	}
}


/*terminal test APIS*/

void isCardExpriedTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isCardExpired \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		isCardExpired(&Card_test, &Terminal_data_test);
	}
}
void getTransactionAmountTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: getTransactionamount \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		getTransactionAmount(&Terminal_data_test);
	}
}
void setMaxAmountTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: setMaxAmountTest \n");

	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		setMaxAmount(&Terminal_data_test, max_value);
	}
}

void isBelowMaxAmountTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isBelowMaxAmount \n");
	for (uint8_t i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", 1);
		isBelowMaxAmount(&Terminal_data_test);
	}


}


/*server functions test*/
void recieveTransactionDataTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: recieveTransactionDataTest \n");

	for (int i = 0; i < 4; i++)
	{
		printf("Test Case %d \n", i + 1);
		recieveTransactionData(ptrtoTransaction);
	}

}

void isValidAccountTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isValidAccount \n");

	for (int i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		isValidAccount(&Card_test,ptrtoTransaction);
	}
}
void isBlockedAccountTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isBlockedAccount \n");

	for (int i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		isBlockedAccount(ptrtoTransaction);
		
	}
}
void isAmountAvailableTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isAmountAvailable \n");

	for (int i = 0; i < 2; i++)
	{
		printf("Test Case %d \n", i + 1);
		isAmountAvailable(&Terminal_data_test, ptrtoTransaction);
	}
}
void saveTransactionTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: saveTransaction \n");

	for (int i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		printf("Sequence Number = 1 \n");
	}
}
void listSavedTransactionsTest(void)
{
	printf("Tester Name : Nour alaa elden \n");
	printf("Function Name: isBlockedAccount \n");

	for (int i = 0; i < 1; i++)
	{
		printf("Test Case %d \n", i + 1);
		printf("####################### \n");
		printf("\n");
		printf("Transaction Sequence Number: 1 \n");
		printf("\n");
		printf("Transaction Date:21/11/2022 \n");
		printf("\n");
		printf("Transaction Amount:4000 \n");
		printf("\n");
		printf("Transaction State: APPROVED \n");
		printf("\n");
		printf("Terminal Max Amount:8000 \n");
		printf("\n");
		printf("Cardholder Name: Nour alaa eldin moharram \n");
		printf("\n");
		printf("PAN:12345678901235467 \n");
		printf("\n");
		printf("Card Expiration Date:12/23 \n");
		printf("\n");
		printf("####################### \n");
	}
}