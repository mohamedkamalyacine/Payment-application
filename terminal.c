#include "../Types.h"
#include "../Card/card.h"
#include "terminal.h"
#include <time.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    //printf("Enter the Transaction Date in format DD/MM/YYYY : ");
    //scanf("%s", &(termData->transactionDate));

    time_t today;
    today = time(NULL);

    strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%Y", localtime(&today));

    printf("%s\n", termData->transactionDate);
    if(strlen(termData->transactionDate) != 10)
        {
            printf("Wrong Date Format %d\n", WRONG_DATE);
            return WRONG_DATE;
        }
    else
        {
            printf("Accepted Date Format %d\n", DONE);
            return DONE;
        }
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    if(cardData.cardExpirationDate[3] < termData.transactionDate[8])
        {
            printf("Declined Expired Card %d\n", EXPIRED_CARD);
            return EXPIRED_CARD;
        }

    else if(cardData.cardExpirationDate[3] == termData.transactionDate[8])
        {
            if(cardData.cardExpirationDate[4] < termData.transactionDate[9])
                {
                    printf("Declined Expired Card %d\n", EXPIRED_CARD);
                    return EXPIRED_CARD;
                }

            else if(cardData.cardExpirationDate[4] == termData.transactionDate[9])
                {
                    if(cardData.cardExpirationDate[0] < termData.transactionDate[3])
                    {
                        printf("Declined Expired Card %d\n", EXPIRED_CARD);
                        return EXPIRED_CARD;
                    }
                    else if(cardData.cardExpirationDate[0] > termData.transactionDate[3])
                        return DONE;
                    else if(cardData.cardExpirationDate[1] == termData.transactionDate[4])
                        {
                            if(cardData.cardExpirationDate[1] == termData.transactionDate[4])
                                {
                                    printf("Your card will be expired this month %d\n", DONE);
                                    return DONE;
                                }
                        }
                    else if(cardData.cardExpirationDate[1] < termData.transactionDate[4])
                    {
                        printf("Declined Expired Card %d\n", EXPIRED_CARD);
                        return EXPIRED_CARD;
                    }
                }
            else
            {
                printf("Accepted card %d\n", DONE);
                return DONE;
            }
        }
    else
    {
        printf("Accepted card %d\n", DONE);
        return DONE;
    }
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    scanf("%f", &(termData->transAmount));

    if(termData->transAmount <= 0)
    {
        printf("Invalid Amount %d\n", INVALID_AMOUNT);
        return INVALID_AMOUNT;
    }

    printf("Valid Amount %d\n", DONE);
    return DONE;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    termData->maxTransAmount = 5000;

    if(termData->maxTransAmount <= 0)
        {
            //printf("Invalid Maximum Amount\n");
            return INVALID_MAX_AMOUNT;
        }
    else
        {
            //printf("Accepted Max Amount\n");
            return DONE;
        }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount > termData->maxTransAmount)
        {
            printf("Exceed Maximum Amount\n");
            return EXCEED_MAX_AMOUNT;
        }
    else
        {
            printf("Approved Amount\n");
            return DONE;
        }
}
