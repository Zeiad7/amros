#include "../Card/Card.h"
#include <stdio.h>
#include <string.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("Enter the cardholder's name (20-24 alphabetic characters): ");
	scanf(" %[^\n]*c", cardData->cardHolderName);
	if( cardData->cardHolderName == NULL|| strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24 )
	{
		return WRONG_NAME;
	}
	return CARD_OK;
	}

void getCardHolderNameTest(void)
{
    ST_cardData_t cardData;
    EN_cardError_t result;

    printf("Tester Name: Zeiad Mohamed\n");
    printf("Function Name: getCardHolderName\n");
    printf("\n**********************************\n");

    // Test Case 1: Valid cardholder name
    printf("Test Case 1:\n");
    printf("Input Data:Zeiad Mohamed Abuzeid\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardHolderName(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_NAME");
    printf("\n**********************************\n");

    // Test Case 2: Cardholder name with less than 20 characters
    printf("Test Case 2:\n");
    printf("Input Data:Zeiad\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_NAME");
    printf("\n**********************************\n");

    // Test Case 3: Cardholder name with more than 24 characters
    printf("Test Case 3:\n");
    printf("Input Data:Zeiad Mohamed Abuzeid Rashad\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_NAME");
    printf("\n**********************************\n");

    // Test Case 4: NULL cardholder name
    printf("Test Case 4:\n");
    printf("Input Data:NULL\n");
    printf("Expected Result: WRONG_NAME\n");
    result = getCardHolderName(NULL);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_NAME");

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    char ExpiryDate[6];

    printf("Enter the card expiry date as MM/YY: ");
    scanf("%s", ExpiryDate);
    
    if (strlen(ExpiryDate) != 5 || ExpiryDate == NULL || ExpiryDate[2] != '/' ||
        !isdigit(ExpiryDate[0]) || !isdigit(ExpiryDate[1]) ||
        !isdigit(ExpiryDate[3]) || !isdigit(ExpiryDate[4]))
    {
        return WRONG_EXP_DATE;
    }

    int month = (ExpiryDate[0] - '0') * 10 + (ExpiryDate[1] - '0');
    int year = (ExpiryDate[3] - '0') * 10 + (ExpiryDate[4] - '0');

    if (month < 1 || month > 12 || year < 20 || year > 35)
    {
        return WRONG_EXP_DATE;
    }

    return CARD_OK;
}

void getCardExpiryDateTest(void)
{
    printf("Tester Name: Zeiad Mohamed\n");
    printf("Function Name: getCardExpiryDate\n");

    ST_cardData_t cardData;
    EN_cardError_t result;

    // Test Case 1: Valid card expiry date
    printf("Test Case 1:\n");
    printf("Input Data: 05/25\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");

    printf("\n**********************************\n");

    // Test Case 2: Card expiry date with less than 5 characters
    printf("Test Case 2:\n");
    printf("Input Data: 05/2\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
    printf("\n**********************************\n");

    // Test Case 3: Card expiry date with more than 5 characters
    printf("Test Case 3:\n");
    printf("Input Data: 052/55\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
    printf("\n**********************************\n");

    // Test Case 4: Card expiry date with wrong format
    printf("Test Case 4:\n");
    printf("Input Data: 05-25\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
    printf("\n**********************************\n");

    // Test Case 5: NULL card expiry date
    printf("Test Case 5:\n");
    printf("Input Data: NULL\n");
    printf("Expected Result: WRONG_EXP_DATE\n");
    result = getCardExpiryDate(NULL);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    
    printf("Enter card PAN: ");
    scanf("%20s", cardData->primaryAccountNumber);
    
    if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 || cardData->primaryAccountNumber == NULL)
    {
        return WRONG_PAN;
    }

    return CARD_OK;
}
void getCardPANTest(void)
{
    ST_cardData_t cardData;
    EN_cardError_t result;

    printf("Tester Name: zeiad\n");
    printf("Function Name: getCardPAN\n");
    printf("\n**********************************\n");

    // Test Case 1 : Valid PAN
    printf("Test Case 1:\n");
    printf("Input Data:12345678912345678\n");
    printf("Expected Result: CARD_OK\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_PAN");
    printf("\n**********************************\n");

    // Test Case 2 : PAN more than 19
    printf("Test Case 2:\n");
    printf("Input Data:12345678912345678912\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_PAN");
    printf("\n**********************************\n");

    // Test Case 3 : PAN less than 16
    printf("Test Case 3:\n");
    printf("Input Data:123\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_PAN");
    printf("\n**********************************\n");

    // Test Case 4 : NULL PAN
    printf("Test Case 4:\n");
    printf("Input Data:NULL\n");
    printf("Expected Result: WRONG_PAN\n");
    result = getCardPAN(&cardData);
    printf("Actual Result: %s\n", result == CARD_OK ? "CARD_OK" : "WRONG_PAN");
}


