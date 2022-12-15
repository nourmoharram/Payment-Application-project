#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include"Server.h"

/*array to store transactions history*/
ST_transaction_t array_of_transactions[255] = { 0 };
/*pointer for transactions data*/
ST_transaction_t* ptrtoTransaction = array_of_transactions;

/*global pointer to carry the address of chosen account*/
ST_accountsDB_t* ptrtoaccount = 0;

/*counter to be incremented with every transaction process*/
uint32_t Sequence_number = 1;
/*create global variable to store transaction status*/
EN_transState_t Transaction_status_value;
/*data base of server*/
ST_accountsDB_t accountsDB[255] =
{
	{8000.0,RUNNING,"1863547896321456"},
	{2000.0,BLOCKED,"7896541233698524"},
	{8000.0,RUNNING,"1111222233334444"},
	{10000.0,BLOCKED,"1463978521479652"},
	{3000.0,RUNNING,"4444555566667777"},
	{9000.0,BLOCKED,"1789654123698745"},
	{5000.0,RUNNING,"1478456321789635"},
	{8500.0,BLOCKED,"7891233579514589"},
	{7500.0,RUNNING,"9853674129875634"},
	{1000.0,BLOCKED,"7856941236987456"}
};
/*global pointer to access the data base and to compare PAN with PAN from card module*/
ST_accountsDB_t* ptrtoDatabase = &accountsDB;


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t Error_type;
	EN_serverError_t valid_account_error;
	uint8_t blocked_account_error;
	float is_amount_available_error;
	float New_Balance;
	valid_account_error = isValidAccount(ptr_to_card, ptrtoDatabase);
	if (valid_account_error != 0)
	{
		printf("Fraud card! \n");
		Transaction_status_value = FRAUD_CARD;
		Error_type = FRAUD_CARD;
	}
	else
	{
		blocked_account_error = isBlockedAccount(ptrtoaccount);
		if (blocked_account_error != 0)
		{
			printf("Declined Stolen Card! \n");
			Transaction_status_value = DECLINED_STOLEN_CARD;
			Error_type = DECLINED_STOLEN_CARD;
		}
		else
		{
			is_amount_available_error = isAmountAvailable(ptr_to_terminal, ptrtoaccount);
			if (is_amount_available_error != 0)
			{
				printf("Declined Insuffecient fund \n");
				Transaction_status_value = DECLINED_INSUFFECIENT_FUND;
				Error_type = DECLINED_INSUFFECIENT_FUND;
			}
			else
			{
				New_Balance = (ptrtoaccount->balance) - (ptr_to_terminal->transAmount);
				ptrtoaccount->balance -= ptr_to_terminal->transAmount;
				printf("New balance of the bank account = %0.1f \n", New_Balance);
				Error_type = APPROVED;
				Transaction_status_value = APPROVED;
				printf("Transaction has completed successfully! \n");
			}
		}
	}
	
	return Error_type;

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t Error_type = 0;
	int result;
	accountRefrence = accountsDB;
	/*check the PAN from terminal and compare it with PANs in data base*/
	for (int i = 0; i < 10; i++)
	{
		/*strcmp function used to compare two strings and return 0 if they are equal*/
		result = strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber);
		if (result == 0)
		{
			printf("Account found! \n");
			Error_type = SERVER_OK;
			ptrtoaccount = accountRefrence;
			return SERVER_OK;
			break;
		}
		accountRefrence++;
	}
	if (ptrtoaccount == 0)
	{
		printf("Account Not found! \n");
		Error_type = ACCOUNT_NOT_FOUND;
	}
	
	return Error_type;
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t Error_type = 0;

	if (accountRefrence->state == 0)
	{
		printf("Account is active! \n");
		Error_type = SERVER_OK;
	}
	else
	{
		printf("Account is blocked! \n");
		Error_type = BLOCKED_ACCOUNT;
	}
	return Error_type;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t Error_type;
	if ((termData->transAmount) > (accountRefrence->balance))
	{
		printf("Low balance in the account! \n");
		Error_type = LOW_BALANCE;
	}
	else
	{
		printf("Balance is valid! \n");
		Error_type = SERVER_OK;
	}
	return Error_type;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t Error_type;
	transData->transState = Transaction_status_value;
	transData->transactionSequenceNumber = Sequence_number;
	/*strcpy function used to copy string from the next argument to the first argument*/
	strcpy((array_of_transactions[Sequence_number].cardHolderData.cardHolderName), ptr_to_card->cardHolderName);

	strcpy((array_of_transactions[Sequence_number].cardHolderData.cardExpirationDate), ptr_to_card->cardExpirationDate);

	strcpy((array_of_transactions[Sequence_number].cardHolderData.primaryAccountNumber), ptr_to_card->primaryAccountNumber);

	strcpy((array_of_transactions[Sequence_number].terminalData.transactionDate),ptr_to_terminal->transactionDate);

	array_of_transactions[Sequence_number].terminalData.transAmount = ptr_to_terminal->transAmount;

	array_of_transactions[Sequence_number].transactionSequenceNumber = Sequence_number;

	array_of_transactions[Sequence_number].transState = Transaction_status_value;
	Sequence_number++;
	ptr_to_card++;
	ptr_to_terminal++;
	Error_type = SERVER_OK;
	listSavedTransactions();

	return Error_type;
}


void listSavedTransactions(void)
{
	for (int i = 1; i < Sequence_number; i++)
	{
		printf("######################################################################## \n");
		printf("###########################List_Saved_Transactions###################### \n");
		printf("Transaction Sequence Number:%d \n", i);
		printf("******************************* \n");
		printf("Transaction Date:%s \n",(array_of_transactions[i].terminalData.transactionDate));
		printf("******************************* \n");
		printf("Transaction Amount:%0.1f \n",array_of_transactions[i].terminalData.transAmount);
		printf("******************************* \n");
		switch (array_of_transactions[i].transState)
		{
		case 0:
			printf("Transaction State is APPROVED! \n");
			break;
		case 1: 
			printf("Transaction State is DECLINED_INSUFFECIENT_FUND \n");
			break;
		case 2:
			printf("Transaction State is DECLINED_STOLEN_CARD \n");
			break;
		case 3: 
			printf("Transaction State is FRAUD_CARD \n");
			break;
		case 4:
			printf("Transaction State is INTERNAL_SERVER_ERROR \n");
			break;
		}
		printf("******************************* \n");
		printf("Terminal Max Amount:%d \n", 10000);
		printf("******************************* \n");
		printf("Cardholder Name:%s \n", (array_of_transactions[i].cardHolderData.cardHolderName));
		printf("******************************* \n");
		printf("PAN: %s \n", (array_of_transactions[i].cardHolderData.primaryAccountNumber));
		printf("******************************* \n");
		printf("Card Expiration Date:%s\n", array_of_transactions[i].cardHolderData.cardExpirationDate);
		printf("######################################################################## \n");

	}
}
