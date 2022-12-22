#include "../Terminal/Terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    char date[11];
    printf("Enter transaction date (DD/MM/YYYY): ");
    scanf("%s", date);

    if (date == NULL || strlen(date) < 10 || date[2] != '/' || date[5] != '/')
    {
        return WRONG_DATE;
    }
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    if (day > 31 || month > 12 || year < 2022)
    {
        return WRONG_DATE;
    }
    for (int i = 0; i < 10; i++)
    {
        termData->transactionDate[i] = date[i];
    }

    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    // Compare card expiry month and year with transaction expiry month and year
    if (cardData->cardExpirationDate[3] < termData->transactionDate[8])
    {
        return EXPIRED_CARD;
    }
    else if (cardData->cardExpirationDate[3] == termData->transactionDate[8])
    {
        if (cardData->cardExpirationDate[4] < termData->transactionDate[9])
        {
            return EXPIRED_CARD;
        }
        else if (cardData->cardExpirationDate[4] == termData->transactionDate[9])
        {
            if (cardData->cardExpirationDate[0] < termData->transactionDate[3])
            {
                return EXPIRED_CARD;
            }
            else if (cardData->cardExpirationDate[0] == termData->transactionDate[3])
            {
                if (cardData->cardExpirationDate[1] < termData->transactionDate[4])
                {
                    return EXPIRED_CARD;
                }
                else
                {
                    return TERMINAL_OK;
                }
            }
            else
            {
                return TERMINAL_OK;
            }
        }
        else
        {
            return TERMINAL_OK;
        }
    }
    else
    {
        return TERMINAL_OK;
    }
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    printf("Enter transaction amount: ");
    scanf("%f", &termData->transAmount);

    if (termData->transAmount <= 0)
    {
        return INVALID_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
        return TERMINAL_OK;
    }
}

void isBelowMaxAmountTest(void)
{
    ST_terminalData_t termData;

    printf("Tester Name: ZEIAD\n");
    printf("Function Name: isBelowMaxAmount\n");

    // Test Case 1
    printf("Test Case 1:\n");
    printf("Input Data:\n");
    termData.transAmount = 100;
    termData.maxTransAmount = 200;
    printf("Transaction amount: %.2f\n", termData.transAmount);
    printf("Maximum allowed amount: %.2f\n", termData.maxTransAmount);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", isBelowMaxAmount(&termData) == TERMINAL_OK ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");

    // Test Case 2
    printf("Test Case 2:\n");
    printf("Input Data:\n");
    termData.transAmount = 200;
    termData.maxTransAmount = 200;
    printf("Transaction amount: %.2f\n", termData.transAmount);
    printf("Maximum allowed amount: %.2f\n", termData.maxTransAmount);
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", isBelowMaxAmount(&termData) == TERMINAL_OK ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");

    // Test Case 3
    printf("Test Case 3:\n");
    printf("Input Data:\n");
    termData.transAmount = 300;
    termData.maxTransAmount = 200;
    printf("Transaction amount: %.2f\n", termData.transAmount);
    printf("Maximum allowed amount: %.2f\n", termData.maxTransAmount);
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", isBelowMaxAmount(&termData) == TERMINAL_OK ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    if (maxAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
}
void setMaxAmountTest(void)
{
    ST_terminalData_t termData;

    printf("Tester Name: ZEIAD\n");
    printf("Function Name: setMaxAmount\n");

    // Test Case 1
    printf("Test Case 1:\n");
    printf("Input Data:\n");
    printf("Maximum allowed amount: 100\n");
    printf("Expected Result: TERMINAL_OK\n");
    printf("Actual Result: %s\n", setMaxAmount(&termData, 100) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");

    // Test Case 2
    printf("Test Case 2:\n");
    printf("Input Data:\n");
    printf("Maximum allowed amount: 0\n");
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", setMaxAmount(&termData, 0) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");

    // Test Case 3
    printf("Test Case 3:\n");
    printf("Input Data:\n");
    printf("Maximum allowed amount: -100\n");
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    printf("Actual Result: %s\n", setMaxAmount(&termData, -100) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");
}
