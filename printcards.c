#include <stdio.h>
#include <string.h>
#include "printcards.h"

void cardsInSystem(CARDLIST *cardList){
    printf("All cards in system\n");
    for (Card *card = cardList->allCards; card < cardList->allCards + cardList->amountOfCards; card++){
        char curentStatus[25];
        if(card ->status == 0){
            strcpy(curentStatus, "No Acces Added to system");
        }else{
            strcpy(curentStatus, "Acces Added to system");
        }
        
        printf("Uid:%d  %s:  %d\n", card ->cardUid, curentStatus, card ->date);
    }     
}