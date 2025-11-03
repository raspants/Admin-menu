#include "cardScan.h"
#include "safeinput.h"


void cardScan(CARDLIST *cardList, char* buff, size_t inputBufferSize, long* numValueOfInput, INPUT_RESULT *inputResult){
    int cardnum;
    while(true){
        cardsInSystem(cardList, buff, inputBufferSize,  numValueOfInput, inputResult);//bara så att du inte behöver memmorera kortnummer

        printf("CURENTLY LAMP IS: OFF\n"); 

        *inputResult = ValidateResult("Scan card (i dont actiualy have any harware so pleas typ the number...) or X.Return to main menu\n", buff, sizeof(buff), numValueOfInput, 110001, cardList ->allCards[cardList ->amountOfCards -1].cardUid);
        if(*inputResult == INPUT_EXIT){
            return;
        }

        cardnum = (int)*numValueOfInput;   

        //send card to remoteopen for acces eval if inputed cardUid exist
       for(int i = 0; i < cardList ->amountOfCards; i++){ 
          if(cardnum == cardList->allCards[i].cardUid){
               remoteOpen(cardList ->allCards[i]); 
            }else if(cardnum != cardList->allCards[i].cardUid && i == cardList ->amountOfCards -1){
                 printf("Card not found in system\n");
            }
        }
       
        *inputResult = ValidateResult("1.Scan another? or X.Return to main menu\n", buff, sizeof(buff), numValueOfInput, 1, 1);
        if(*inputResult == INPUT_EXIT){
            return;
        }
        continue;
    }
}