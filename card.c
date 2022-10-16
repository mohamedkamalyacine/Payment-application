#include <strings.h>
#include <string.h>
#include "../Types.h"
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    scanf("%[^\n]", &(cardData->cardHolderName));
    //gets(cardData->cardHolderName);

    if(strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) > 24)
        {
            printf("Wrong Name %d\n", WRONG_NAME);
            return WRONG_NAME;
        }
    else
        {
            printf("Accepted Name %d\n", OK);
            return OK;
        }

}

EN_cardError_t getCardExpirationDate(ST_cardData_t* cardData)
{
    uint8_t i;

    scanf("%s", &(cardData->cardExpirationDate));

    if(strlen(cardData->cardExpirationDate) < 5 || strlen(cardData->cardExpirationDate) > 5)
        {
            printf("Wrong Format\n");
            return WRONG_EXP_DATE;
        }


    for(i=0; i<strlen(cardData->cardExpirationDate); i++)
    {
        if(cardData->cardExpirationDate[i] >= 48 && cardData->cardExpirationDate[i] <= 57)
        {
            if(i==2)
                {
                    printf("Wrong EXP Date %d\n", WRONG_EXP_DATE);
                    return WRONG_EXP_DATE;
                }
            else
                continue;
        }
        else if(i==2 && cardData->cardExpirationDate[i] == '/')
            continue;
        else
            {
                printf("Wrong Expiration Date\n");
                return WRONG_EXP_DATE;
            }
    }
    printf("Accepted format %d\n",OK);
    return OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    scanf("%s",&(cardData->primaryAccountNumber));

    printf("length of pan = %d\n", strlen(cardData->primaryAccountNumber));

    if(strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
        {
            printf("Wrong PAN Number %d\n", WRONG_PAN);
            return WRONG_PAN;
        }
    printf("Accepted PAN %d\n", OK);
    return OK;
}
