#include "cardScan.h"
#include "safeinput.h"


void cardScan(CARDLIST *cardList, char* buff, int maxSize, long* numValueOfInput, INPUT_RESULT *inputResult){
    int cardnum;
    while(true){
        cardsInSystem(cardList);//bara så att du inte behöver memmorera kortnummer

        printf("CURENTLY LAMP IS: OFF\n"); 

        *inputResult = ValidateResult("Scan card (i dont actiualy have any harware so pleas typ the number...) or X.Return to main menu\n", buff, sizeof(buff), numValueOfInput, 110001, 999999);
        if(*inputResult == INPUT_EXIT){
            return;
        }

        cardnum = (int)*numValueOfInput;   

        for(int i = 0; i < cardList ->amountOfCards; i++){
            if(cardnum == cardList->allCards[i].cardUid){
                remoteOpen(cardList ->allCards[i]); 
            }   
        }
        printf("Card not found\n");
        remoteOpen(cardList ->allCards[cardList ->amountOfCards +1]);
        *inputResult = ValidateResult("1.Scan another? or X.Return to main menu\n", buff, sizeof(buff), numValueOfInput, 1, 1);
        if(*inputResult == INPUT_EXIT){
            return;
        }
        continue;
    }
}