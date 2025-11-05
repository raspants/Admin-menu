#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "safeinput.h"
#include "printcards.h"
#include "clearCls.h"
#include "colorpallet.h"

void dynamicHeaderLinePrint(int *lineLegnth, const char *character){
    for(int i = 0; i < *lineLegnth; i++){  
        printf(GREEN"%c"RESET, *character);
    }
     printf("\n");
}
void allCardDevideLines(int *longestUid, int legntBuff, int legnthDate){
    printf("|");
    for(int i = 0; i < *longestUid + 7; i++){
        printf("-");    
    }
    printf("|");
    for(int i = 0; i <= (int)legntBuff; i++){
        printf("-");    
    }
    printf("|");
    for(int i = 0; i < legnthDate +17; i++){
        printf("-");    
    }
    printf("|\n");
}

void cardsInSystem(CARDLIST *cardList, char *inputBuffer, size_t inputBufferSize, long *numValueOfInput, INPUT_RESULT *inputResult){
    clearCls();

    int longestUid = 0; //just for fun so the border scales with legnth of card Uid
    
    for(int i = 0; i < cardList->amountOfCards; i++){

        int cardUid = cardList ->allCards[i].cardUid;
        int uidLength = 0;
        bool divisionPossible = true;
        while(divisionPossible){
            if(!cardUid){
                if(uidLength > longestUid){
                    longestUid = uidLength;
                }
                divisionPossible = false;
            }else{
                uidLength++;
                cardUid /= 10;
            }
        }    
    }


    int fullDisplaywidth = longestUid + 67; // 65 is the amount of static charakters
    //_____________________________________________________________________________________

    dynamicHeaderLinePrint(&fullDisplaywidth, "=");
    printf(" %*s\n",(longestUid + 38), YELLOW"All cards in system"RESET);
    dynamicHeaderLinePrint(&fullDisplaywidth, "=");

    dynamicHeaderLinePrint(&fullDisplaywidth, "-");
    if(cardList->amountOfCards == 0){
        printf(" %*s", (fullDisplaywidth / 2), YELLOW"No cards in System\n");
        dynamicHeaderLinePrint(&fullDisplaywidth, "-");
        int clear;
        while((clear = getchar()) != '\n' && clear != EOF);
        *inputResult = ValidateResult(CYAN"[X] Return to main menu\n"RESET,  inputBuffer, inputBufferSize, numValueOfInput, 1, 1);
        return;
    }

    for (Card *card = cardList->allCards; card < cardList->allCards + cardList->amountOfCards; card++){
        char curentStatus[25];
        if(card ->status == 0){
            strcpy(curentStatus, "No Acces Added to system");
        }else{
            strcpy(curentStatus, "   Acces Added to system");
        }
        
        printf("|"CYAN" Uid: %-*d "RESET"|"CYAN" %s "RESET"|"CYAN" Creation date: %s "RESET"|\n",longestUid, card ->cardUid, curentStatus, card ->date);
        
        allCardDevideLines(&longestUid, (int)sizeof(curentStatus), (int)strlen(card ->date));
    }   
    
    *inputResult = ValidateResult(CYAN"[X] Continue\n"RESET,  inputBuffer, inputBufferSize, numValueOfInput, 1, 1);
    if(*inputResult == INPUT_EXIT)
        return;
                    
}