#ifndef TEST_H
#define TEST_H
#include"Server.h"
/*card functions test*/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);
/*terminal function test*/
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
/*server functions test*/
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

extern ST_transaction_t* ptrtoTransaction;


#endif // !TEST_H
