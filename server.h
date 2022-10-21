#ifndef _SERVER_H_
#define _SERVER_H_

typedef unsigned long           uint32_t;

typedef enum EN_transState_t
{
    DECLINED_INSUFFECIENT_FUND = -30,
    DECLINED_STOLEN_CARD,
    INTERNAL_SERVER_ERROR,
    APPROVED = 20
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transSequenceNum;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef enum EN_serverError_t
{
    SAVING_FAILED = -50,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE,
    ACCEPTED = 40
}EN_serverError_t;

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transSequenceNum, ST_transaction_t *transData);

#endif
