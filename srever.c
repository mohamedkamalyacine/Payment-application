#include "../Types.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"

/*ST_accountsDB_t validAccounts[255] = {0, {10002000300040005000}};
ST_transaction_t transaction[255] = {{{0},{0},{0}}, {0,0,{0}}, 0, 0};*/

ST_accountsDB_t validAccounts[255] = {[0].balance = 1000, [0].primaryAccountNumber = {'1','1','1','1','2','2','2','2','3','3','3','3','4','4','4','4'},
                                      [1].balance = 2000, [1].primaryAccountNumber = {'1','0','0','0','2','0','0','0','3','0','0','0','4','0','0','0'},
                                      [2].balance = 3000, [2].primaryAccountNumber = {'1','1','1','1','0','0','0','0','2','2','2','2','3','3','3','3'},
                                      [3].balance = 4000, [3].primaryAccountNumber = {'1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0'}};

ST_transaction_t transaction[255] = {
                                        [0].cardHolderData.cardHolderName = {'\0'},
                                        [0].cardHolderData.primaryAccountNumber = {'\0'},
                                        [0].cardHolderData.cardExpirationDate = {'\0'},
                                        [0].terminalData.transAmount = 0,
                                        [0].terminalData.maxTransAmount = 0,
                                        [0].terminalData.transactionDate = {'\0'},
                                        [0].transState = DECLINED_STOLEN_CARD,
                                        [0].transSequenceNum = 0
                                     };

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    //printf("passing from recieve = %0.2f\n",termData->transAmount);
    if(termData->transAmount >= validAccounts[0].balance)
    {
        //printf("Low Balance %d\n", LOW_BALANCE);
        return LOW_BALANCE;
    }

    printf("Accepted Balance %d\n", ACCEPTED);
    return ACCEPTED;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    uint8_t i;

    for(i=0; i<=strlen(cardData->primaryAccountNumber); i++)
    {
        if(cardData->primaryAccountNumber[i] != validAccounts[0].primaryAccountNumber[i])
        {
            //printf("Invalid Card %d\n", DECLINED_STOLEN_CARD);
            return DECLINED_STOLEN_CARD;
        }
        else
            continue;
    }

    printf("valid Card %d\n", ACCEPTED);
    return ACCEPTED;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static uint32_t sequence = 100000;
    uint8_t i;
    for(i=0; i<=strlen(transData->cardHolderData.cardHolderName); i++)
    { transaction[0].cardHolderData.cardHolderName[i] = transData->cardHolderData.cardHolderName[i]; }
    printf("Name --> %s\n", transaction[0].cardHolderData.cardHolderName);

    for(i=0; i<=strlen(transData->cardHolderData.cardExpirationDate); i++)
    { transaction[0].cardHolderData.cardExpirationDate[i] = transData->cardHolderData.cardExpirationDate[i]; }
    printf("EXP Date --> %s\n", transaction[0].cardHolderData.cardExpirationDate);

    for(i=0; i<=strlen(transData->terminalData.transactionDate); i++)
    { transaction[0].terminalData.transactionDate[i] = transData->terminalData.transactionDate[i]; }
    printf("Transaction Date --> %s\n", transaction[0].terminalData.transactionDate);

    transaction[0].terminalData.transAmount = transData->terminalData.transAmount;
    printf("Transaction Amount --> %0.2f\n", transaction[0].terminalData.transAmount);

    transaction[0].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
    printf("MAX Transaction Amount --> %0.2f\n", transaction[0].terminalData.maxTransAmount);

    transaction[0].transSequenceNum = transData->transSequenceNum;
    //printf("Sequence Number --> %d\n", transaction[0].transSequenceNum);

    transaction[0].transState = transData->transState;

    if(transaction[0].transState == DECLINED_INSUFFECIENT_FUND)
    {
        transData->transSequenceNum = sequence;
        transaction[0].transSequenceNum = transData->transSequenceNum;
        printf("Sequence Number --> %d\n", transaction[0].transSequenceNum);
        sequence++;
        return LOW_BALANCE;
    }

    else if(transaction[0].transState == DECLINED_STOLEN_CARD)
    {
        /*transData->transSequenceNum = sequence;
        transaction[0].transSequenceNum = transData->transSequenceNum;
        printf("Sequence Number --> %d\n", transaction[0].transSequenceNum);
        sequence++;*/
        return ACCOUNT_NOT_FOUND;
    }

    else
        {/*Do_Nothing*/}

    transData->transSequenceNum = sequence;
    transaction[0].transSequenceNum = transData->transSequenceNum;
    printf("Sequence Number --> %d\n", transaction[0].transSequenceNum);
    sequence++;
    return APPROVED;
}

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    int8_t checkAccount, checkAmount, checkSaving;

    checkAccount = isValidAccount((&transData->cardHolderData));
    checkAmount = isAmountAvailable(&(transData->terminalData));

    //transaction[0].transState = DECLINED_STOLEN_CARD;

    if(transaction[0].transState == DECLINED_STOLEN_CARD)
    {
        return DECLINED_STOLEN_CARD;
    }
    else if(checkAccount == DECLINED_STOLEN_CARD)
    {
        return checkAccount;
    }
    else if(checkAmount == LOW_BALANCE)
    {
        return DECLINED_INSUFFECIENT_FUND;
    }
    else
    {
        checkSaving = saveTransaction(transData);
        validAccounts[0].balance = validAccounts[0].balance - transData->terminalData.transAmount;
        printf("Card Balance = %0.2f\n", validAccounts[0].balance);

        return APPROVED;
    }
}
