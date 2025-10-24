#include "cardScan.h"

void cardScan(CARDLIST *cardList){
    int cardnum;
    cardsInSystem(cardList);//bara så att du inte behöver memmorera kortnummer
    printf("Scan card (i dont actiualy have any harware so pleas typ the number...\n)");
    printf("CURENTLY LAMP IS: OFF\n");
    scanf(" %d", &cardnum);

    for(int i = 0; i < cardList ->amountOfCards; i++){
        if(cardnum == cardList->allCards[i].cardUid){
              remoteOpen(cardList ->allCards[i]);
              return;     
        }   
    }
    printf("Card not found\n");
    remoteOpen(cardList ->allCards[cardList ->amountOfCards +1]);
    return;
}