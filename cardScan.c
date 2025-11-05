#include <stdio.h>
#include <stdbool.h>
#include "clearCls.h"
#include "cardScan.h"
#include "cardStructure.h"
#include "printcards.h"
#include "remoteopen.h"
#include "safeinput.h"
#include "colorpallet.h"
#include "timeDelay.h"

void cardScan(CARDLIST *cardList, char* buff, size_t inputBufferSize, long* numValueOfInput, INPUT_RESULT *inputResult){
    int cardnum;
    while(true){
        cardsInSystem(cardList, buff, inputBufferSize,  numValueOfInput, inputResult);//bara så att du inte behöver memmorera kortnummer

        printf("CURENTLY LAMP IS: OFF\n"); 

        *inputResult = ValidateResult(CYAN"Scan card (i dont actiualy have any harware so pleas typ the number...) or X.Return to main menu\n"RESET, buff, sizeof(buff), numValueOfInput, 110001, cardList ->allCards[cardList ->amountOfCards -1].cardUid);
        if(*inputResult == INPUT_EXIT){
            return;
        }

        cardnum = (int)*numValueOfInput;   

        //send card to remoteopen for acces eval if inputed cardUid exist
       for(int i = 0; i < cardList ->amountOfCards; i++){ 
          if(cardnum == cardList->allCards[i].cardUid){
               remoteOpen(&cardList ->allCards[i]); 
               break;
            }else if(cardnum != cardList->allCards[i].cardUid && i == cardList ->amountOfCards -1){
                 printf(RED"Card not found in system\n");
                 timeDelay(3);
            }
        }
        clearCls();
        *inputResult = ValidateResult(YELLOW"       Option\n=======================\n"CYAN"[1] Scan another card \n[X] Return to main menu\n=======================\n"RESET,
                                              buff, sizeof(buff), numValueOfInput, 1, 1);

        if(*inputResult == INPUT_EXIT){
            return;
        }
        continue;
    }
}