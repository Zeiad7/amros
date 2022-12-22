#include"../Server/Server.h"

ST_accountsDB_t accountsDB[255] = {
    {2000.0, RUNNING, "8989374615436851"},
    {100000.0, BLOCKED, "5807007076043875"},
    {300.0, RUNNING, "1234567890123456"},
    {50.0, RUNNING, "9876543210987654"},
    {1000.0, RUNNING, "5555555555555555"},
    {2000.0, RUNNING, "6666666666666666"},
    {3000.0, BLOCKED, "7777777777777777"},
    {4000.0, RUNNING, "8888888888888888"},
    {5000.0, RUNNING, "9999999999999999"},
    {6000.0, RUNNING, "0000000000001111"}
};

ST_transaction_t transactionsDB[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    ST_cardData_t cardData;
    ST_accountsDB_t* accountRefrence = NULL;
    EN_transState_t transState = APPROVED;
    
    if (isValidAccount(&cardData, &accountRefrence) == ACCOUNT_NOT_FOUND)
    {
        transState = FRAUD_CARD;
        printf("Declined.\nFRAUD CARD!\n");
    }
    else
    {
        if (isBlockedAccount(accountRefrence) == BLOCKED_ACCOUNT)
        {
            transState = DECLINED_STOLEN_CARD;
            printf("Declined.\n STOLEN CARD!\n");
        }
        else
        {

            if (isAmountAvailable(&transData, accountRefrence) == LOW_BALANCE)
            {
                transState = DECLINED_INSUFFECIENT_FUND;
                printf("Declined.\nINSUFFECIENT FUND!\n");
            }
            else
            {
              
                printf("Balance before transaction: %f\n", accountRefrence->balance);
                accountRefrence->balance -= transData->terminalData.transAmount;
                printf("Balance after transaction: %f\n", accountRefrence->balance);

            }
        }
    }

    if (saveTransaction(transData) == SAVING_FAILED)
    {
        transState = INTERNAL_SERVER_ERROR;
        printf("INTERNAL SERVER ERROR!\n");
    }
    return transState;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    for (int i = 0; i < 255; i++) {
        if (strcmp((char*)cardData->primaryAccountNumber, (char*)accountsDB[i].primaryAccountNumber) == 0) {
            *accountRefrence = accountsDB[i];
            return SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

void isValidAccountTest(void)
{
    printf("Tester Name: ZEIAD\n");
    printf("Function Name: isValidAccount\n");
    printf("\n***********************************************\n");

    // Test Case 1: Valid account
    ST_cardData_t cardData = { .primaryAccountNumber = "8989374615436851" };
    ST_accountsDB_t accountRef;
    printf("Test Case 1:Valid account\n");
    printf("Input Data: primaryAccountNumber = %s\n", cardData.primaryAccountNumber);
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", isValidAccount(&cardData, &accountRef) == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    printf("\n***********************************************\n");

    // Test Case 2: Invalid account
    ST_cardData_t cardData1 = { .primaryAccountNumber = "1234567890123444" };
    ST_accountsDB_t accountRef1;
    printf("Test Case 2:Invalid account\n");
    printf("Input Data: primaryAccountNumber = %s\n", cardData1.primaryAccountNumber);
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: %s\n", isValidAccount(&cardData1, &accountRef1) == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
    printf("\n***********************************************\n");

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (accountRefrence->state == BLOCKED)
    {
        return BLOCKED_ACCOUNT;
    }
    return SERVER_OK;
}
void isBlockedAccountTest(void)
{
    ST_accountsDB_t runningAccount = { 2000.0, RUNNING, "8989374615436851" };
    ST_accountsDB_t blockedAccount = { 100000.0, BLOCKED, "5807007076043875" };

    printf("Tester Name: zeiad\n");
    printf("Function Name: isBlockedAccount\n");
    printf("\n***********************************************\n");

    printf("Test Case 1:\n");
    printf("Input Data: runningAccount\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", isBlockedAccount(&runningAccount) == SERVER_OK ? "SERVER_OK" : "BLOCKED_ACCOUNT");
    printf("\n***********************************************\n");

    printf("Test Case 2:\n");
    printf("Input Data: blockedAccount\n");
    printf("Expected Result: BLOCKED_ACCOUNT\n");
    printf("Actual Result: %s\n", isBlockedAccount(&blockedAccount) == SERVER_OK ? "SERVER_OK" : "BLOCKED_ACCOUNT");
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
    if (termData->transAmount > accountRefrence->balance)
    {
        return LOW_BALANCE;
    }
    return SERVER_OK;
}
void isAmountAvailableTest(void)
{
    ST_accountsDB_t Account = { 2000.0, RUNNING, "8989374615436851" };
    ST_terminalData_t terminal1 = { 1000.0 };
    ST_terminalData_t terminal2 = { 2500.0 };

    printf("Tester Name: zeiad\n");
    printf("Function Name: isAmountAvailable\n");
    printf("\n***********************************************\n");

    printf("Test Case 1:\n");
    printf("Input Data: account1, terminal1\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: %s\n", isAmountAvailable(&terminal1, &Account) == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
    printf("\n***********************************************\n");

    printf("Test Case 2:\n");
    printf("Input Data: account1, terminal2\n");
    printf("Expected Result: LOW_BALANCE\n");
    printf("Actual Result: %s\n", isAmountAvailable(&terminal2, &Account) == SERVER_OK ? "SERVER_OK" : "LOW_BALANCE");
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    static uint32_t sequenceNumber = 1;
    for (int i = 0; i < 255; i++)
    {
        if (transactionsDB[i].transactionSequenceNumber == 0)
        {
            transactionsDB[i].cardHolderData = transData->cardHolderData;
            transactionsDB[i].terminalData = transData->terminalData;
            transactionsDB[i].transState = transData->transState;
            transactionsDB[i].transactionSequenceNumber = sequenceNumber;
            sequenceNumber++;
            return SERVER_OK;
        }
    }
    return SAVING_FAILED;
}
void listSavedTransactions(void)
{
    for (int i = 0; i < 255; i++)
    {
        if (transactionsDB[i].transactionSequenceNumber != 0)
        {
            printf("#########################\n");
            printf("Transaction Sequence Number: %d\n", transactionsDB[i].transactionSequenceNumber);
            printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
            printf("Transaction Amount: %.2f\n", transactionsDB[i].terminalData.transAmount);
            printf("Transaction State: %d\n", transactionsDB[i].transState);
            printf("Terminal Max Amount: %.2f\n", transactionsDB[i].terminalData.maxTransAmount);
            printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
            printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
            printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
        }
    }
}
void listSavedTransactionsTest(void)
{
    printf("Tester Name: Zeiad\n");
    printf("Function Name: listSavedTransactions\n");

    // Test Case 1:
    printf("Test Case 1:\n");
    printf("Input Data:\n");
    ST_transaction_t transData1 = {
        {"8989374615436851","0922" },{100.0, },APPROVED,1,};
    saveTransaction(&transData1);
    printf("Expected Result: List of saved transactions\n");
    printf("Actual Result:\n");
    listSavedTransactions();
}
void recieveTransactionDataTest(void)
{
    printf("Tester Name: zeiad\n");
    printf("Function Name: recieveTransactionData\n");
    ST_transaction_t transData;
    EN_transState_t actualResult;

    // Test Case 1:
    printf("Test Case 1:\n");
    printf("Input Data:\n");
    strcpy(transData.cardHolderData.cardHolderName, "Zeiad Nohamed");
    strcpy(transData.cardHolderData.primaryAccountNumber, "8989374615436851");
    strcpy(transData.cardHolderData.cardExpirationDate, "09/25");
    strcpy(transData.terminalData.transactionDate, "02/12/2022");
    transData.terminalData.transAmount = 300;
    transData.terminalData.maxTransAmount = 500;
    printf("Cardholder Name: %s\n", transData.cardHolderData.cardHolderName);
    printf("PAN: %s\n", transData.cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transData.cardHolderData.cardExpirationDate);
    printf("Transaction Date: %s\n", transData.terminalData.transactionDate);
    printf("Transaction Amount: %.2f\n", transData.terminalData.transAmount);
    printf("Terminal Max Amount: %.2f\n", transData.terminalData.maxTransAmount);
    printf("Expected Result: APPROVED\n");
    printf("Actual Result: %s\n",recieveTransactionData(&transData) == APPROVED ? "APPROVED" : "FRAUD_CARD");

    // Test Case 2:
    printf("Test Case 2:\n");
    printf("Input Data:\n");
    strcpy(transData.cardHolderData.cardHolderName, "John Smith");
    strcpy(transData.cardHolderData.primaryAccountNumber, "5807007076043876");
    strcpy(transData.cardHolderData.cardExpirationDate, "09/25");
    strcpy(transData.terminalData.transactionDate, "02/12/2022");
    transData.terminalData.transAmount = 300;
    transData.terminalData.maxTransAmount = 500;
    printf("Cardholder Name: %s\n", transData.cardHolderData.cardHolderName);
    printf("PAN: %s\n", transData.cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transData.cardHolderData.cardExpirationDate);
    printf("Transaction Date: %s\n", transData.terminalData.transactionDate);
    printf("Transaction Amount: %.2f\n", transData.terminalData.transAmount);
    printf("Terminal Max Amount: %.2f\n", transData.terminalData.maxTransAmount);
    printf("Expected Result: FRAUD_CARD\n");
    printf("Actual Result: %s\n", recieveTransactionData(&transData) == APPROVED ? "APPROVED" : "FRAUD_CARD");

    // Test Case 3:
    printf("Test Case 3:\n");
    printf("Input Data:\n");
    strcpy(transData.cardHolderData.cardHolderName, "John Smith");
    strcpy(transData.cardHolderData.primaryAccountNumber, "5807007076043875");
    strcpy(transData.cardHolderData.cardExpirationDate, "09/25");
    strcpy(transData.terminalData.transactionDate, "02/12/2022");
    transData.terminalData.transAmount = 2000;
    transData.terminalData.maxTransAmount = 500;
    printf("Cardholder Name: %s\n", transData.cardHolderData.cardHolderName);
    printf("PAN: %s\n", transData.cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n", transData.cardHolderData.cardExpirationDate);
    printf("Transaction Date: %s\n", transData.terminalData.transactionDate);
    printf("Transaction Amount: %.2f\n", transData.terminalData.transAmount);
    printf("Terminal Max Amount: %.2f\n", transData.terminalData.maxTransAmount);
    printf("Expected Result: DECLINED_INSUFFECIENT_FUND\n");
    printf("Actual Result: %s\n", recieveTransactionData(&transData) == APPROVED ? "APPROVED" : "DECLINED_INSUFFECIENT_FUND");
}
    