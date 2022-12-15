#ifndef APP_HEADER
#define APP_HEADER
#include"Server.h"
#include"Test.h"
/*card module return states*/
EN_cardError_t Card_Name_return=WRONG_NAME;
EN_cardError_t Card_expirydate_return=WRONG_EXP_DATE;
EN_cardError_t Card_PAN_return=WRONG_PAN;
/*terminal module return states*/
EN_terminalError_t is_cardxpired_return=EXPIRED_CARD ;
EN_terminalError_t get_transacamount_return=EXPIRED_CARD ;
EN_terminalError_t set_max_return=EXPIRED_CARD;
EN_terminalError_t is_below_max_amount_return=EXPIRED_CARD;
EN_terminalError_t date_return=EXPIRED_CARD;
/*server module return states*/
EN_transState_t recieve_data_return=FRAUD_CARD;
/*pointer to transactions array*/
//extern ST_terminalData_t Terminal_data_test;
/*main application function*/
void appStart(void);

#endif // !APP_HEADER
