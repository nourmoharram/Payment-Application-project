#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include"Card.h"
/*array to carry data of card during transaction*/
ST_cardData_t Card_data_holder[4];
ST_cardData_t* ptr_to_card = &Card_data_holder;

EN_cardError_t getCardHolderName(ST_cardData_t* CardData)
{
	EN_cardError_t getCardHolderName_Error;
	uint8_t User_Name[25];
	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t flag = 1;
	printf("please enter card holder name: ");
	/*function used to scan string from user*/
	gets(User_Name);
	printf("\n");
	printf("name enterd is %s \n",User_Name);
	while (flag != 0)
	{
		if (User_Name[i] != '\0')
		{
			if (User_Name[i] != ' ')
			{
				if ((User_Name[i] >= 'a' && User_Name[i] <= 'z') || (User_Name[i] >= 'A' && User_Name[i] <= 'Z'))
				{
					counter++;
				}

			}
			i++;
		}
		else
		{
			flag = 0;
		}
	}
	
	if (counter < 20 || counter >24)
	{
		printf("the card holder name is invalid \n");
		getCardHolderName_Error = WRONG_NAME;
		
	}
	else
	{
		printf(" name is valid \n");
		for (int i = 0; i < counter; i++)
		{
			CardData->cardHolderName[i] = User_Name[i];
		}
		 getCardHolderName_Error= CARD_OK;
	}
	return getCardHolderName_Error;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t getCardExpirtDate_Error;
	uint8_t Date[6] = { 0 };
	uint8_t counter = 0;
	uint8_t flag = 0;
	uint8_t month_tenth;
	uint8_t month_unit;
	int i = 0;
	printf("Enter card expiry date in format MM/YY:");
	gets(Date);
	printf("\n");

	/*check that the entered data is valid*/
	while (Date[i] != '\0')
	{
		counter++;
		if ((Date[i] < '0' || Date[i] > '9') && i != 2 && i != 5)
		{
			flag = 1;
		}
		i++;
	}
	if (counter != 5 || flag == 1)
	{
		printf("expire date entered is invalid \n");
		 getCardExpirtDate_Error = WRONG_EXP_DATE;
	}
	else
	{
		month_tenth = (Date[0] - '0') * 10;
		month_unit = (Date[1] - '0');
		/*check that the month numbers less than or equal 12 and format has '/' at index 2 */
		if ((month_tenth+month_unit)<= 12 && Date[2] == '/')
		{
			/*assign the expiry date to the card data*/
			for (int i = 0; i < 6; i++) {
				cardData->cardExpirationDate[i] = Date[i];
			}
			printf("the expiry date is %s \n", cardData->cardExpirationDate);
			printf("valid expiry date \n");
			getCardExpirtDate_Error = CARD_OK;
		}
		else {
			printf("invalid expiry date! \n");
			getCardExpirtDate_Error = WRONG_EXP_DATE;
		}
	}
	return getCardExpirtDate_Error;

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t getCardPAN_Error;
	uint8_t PAN[20];
	uint8_t counter = 0;
	uint8_t flag_for_numbers = 0;
	uint8_t flag = 1;
	printf("enter the PAN value of range from 16 to 19: ");
	gets(PAN);
	printf("\n");
	printf("the entered PAN number is %s \n", PAN);
	while (flag != 0)
	{
		if (PAN[counter] != '\0')
		{
			if (PAN[counter] > '9' || PAN[counter] < '0')
			{
				flag_for_numbers = 1;
			}
			counter++;
		}
		else
		{
			flag = 0;
		}
	}
	if (counter < 16 || counter > 19 || flag_for_numbers == 1)
	{
		printf("wrong pan format \n");
		getCardPAN_Error = WRONG_PAN;
	}
	else
	{
		printf("valid entered PAN value \n");
		for (int i = 0; i < counter; i++)
		{
			cardData->primaryAccountNumber[i] = PAN[i];
		}

		getCardPAN_Error = CARD_OK;
	}

	return getCardPAN_Error;
}

