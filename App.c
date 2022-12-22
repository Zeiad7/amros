#include"../Application/App.h"
#include"../Card/Card.h"

void appStart(void)
{
    uint8_t transactionState;
    
    ST_cardData_t cardData1;
    ST_terminalData_t termData1;
    ST_accountsDB_t accountRefrence1;
    EN_transState_t transState = APPROVED;
    float maxAmount =5000;
    //CARD
    if (getCardHolderName(&cardData1) == WRONG_NAME)
    {
        printf("Declined.\nWrong Name!\n");
        return;
    }
    if (getCardExpiryDate(&cardData1) == WRONG_EXP_DATE)
    {
        printf("Declined.\nWrong expiry date!\n");
        return;
    }
    if (getCardPAN(&cardData1) == WRONG_PAN)
    {
        printf("Declined.\nWrong Primary Account Number!\n");
        return;
    }
    //TERMINAL
    if (getTransactionDate(&termData1) == WRONG_DATE)
    {
        printf("Declined.\nWrong Date!\n");
        return;
    }
    if (isCardExpired(&cardData1, &termData1) == EXPIRED_CARD)
    {
        printf("Declined.\nExpired card!\n");
        return;
    }
    if (getTransactionAmount(&termData1) == INVALID_AMOUNT)
    {
        printf("Declined.\nInvalid amount!\n");
        return;
    }
    if (setMaxAmount(&termData1, maxAmount) == INVALID_MAX_AMOUNT)
    {
        printf("Declined.\nINVALID MAX AMOUNT!\n");
        return;
    }
    if (isBelowMaxAmount(&termData1) == EXCEED_MAX_AMOUNT)
    {
        printf("Declined.\nYou can't Exceed %f that is the Maximum amount.\n", maxAmount);
        return;
    }
    ST_transaction_t trans = { cardData1 , termData1 };
    if (isValidAccount(&cardData1, &accountRefrence1) == ACCOUNT_NOT_FOUND)
    {
            transState = FRAUD_CARD;
            printf("Declined.\nFRAUD CARD!\n");
    }
      else
        {
            if (isBlockedAccount(&accountRefrence1) == BLOCKED_ACCOUNT)
            {
                transState = DECLINED_STOLEN_CARD;
                printf("Declined.\n STOLEN CARD!\n");
            }
            else
            {

                if (isAmountAvailable(&trans, &accountRefrence1) == LOW_BALANCE)
                {
                    transState = DECLINED_INSUFFECIENT_FUND;
                    printf("Declined.\nINSUFFECIENT FUND!\n");
                }
                else
                {
                    printf("Balance before transaction: %f\n", accountRefrence1.balance);
                    accountRefrence1.balance -= trans.terminalData.transAmount;
                    printf("Balance after transaction: %f\n", accountRefrence1.balance);

                }
            }
        }

        if (saveTransaction(&trans) == SAVING_FAILED)
        {
            transState = INTERNAL_SERVER_ERROR;
            printf("INTERNAL SERVER ERROR!\n");
        }
        return 0;
    
   
}
int main()
{
    appStart();
    return 0;
}