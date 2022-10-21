#include "../Types.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

void appStart(void)
{
    ST_cardData_t card_1;
    ST_terminalData_t term_1;
    ST_transaction_t transaction_1;

    int8_t recieveMessage;

    //=======================Get All Card Data=================================
    printf("Enter Card Name : ");           getCardHolderName(&card_1);
    printf("Enter Expiration Date : ");     getCardExpirationDate(&card_1);
    printf("Enter Card PAN : ");            getCardPAN(&card_1);

    //=======================Get All Terminal Data=============================
    printf("Transaction Date in format DD/MM/YYYY : ");
    getTransactionDate(&term_1);

    if(isCardExpired(card_1, term_1) == EXPIRED_CARD)
        return 0;

    printf("Enter Transaction Amount : ");  getTransactionAmount(&term_1);
    setMaxAmount(&term_1);

    if(isBelowMaxAmount(&term_1) == EXCEED_MAX_AMOUNT)
        return 0;

    //=======================Server Side=======================================

    transaction_1.cardHolderData = card_1;
    transaction_1.terminalData = term_1;

    recieveMessage = recieveTransactionData(&transaction_1);

    switch (recieveMessage)
    {
    case DECLINED_STOLEN_CARD:
        printf("Card is declined\n");
        break;

    case DECLINED_INSUFFECIENT_FUND:
        printf("Amounnt is not available\n");
        break;

    case INTERNAL_SERVER_ERROR:
        printf("Server Error");
        break;

    case APPROVED:
        printf("transaction is finished\n");
        break;
    default:
        break;
    }

    /*if(recieveMessage == DECLINED_STOLEN_CARD)
    {
        printf("Invalid Card %d\n", DECLINED_STOLEN_CARD);
        return 0;
    }
    else if(recieveMessage == DECLINED_INSUFFECIENT_FUND)
    {
        printf("Low Balance %d\n", LOW_BALANCE);
        return 0;
    }
    else if(recieveMessage == INTERNAL_SERVER_ERROR)
        {
            printf("Server Error %d\n", INTERNAL_SERVER_ERROR);
        }
    else
        printf("Transction is Finished %d\n",ACCEPTED);*/

}
