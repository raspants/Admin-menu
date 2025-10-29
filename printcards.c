#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "printcards.h"
#include "clearCls.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void dynamicHeaderLinePrint(int *lineLegnth, const char *character){
    for(int i = 0; i < *lineLegnth; i++){  
        printf("%c", *character);
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
    for(int i = 0; i < legnthDate +14; i++){
        printf("-");    
    }
    printf("|\n");
}

void cardsInSystem(CARDLIST *cardList, char *inputBuffer, long *numValueOfInput, INPUT_RESULT *inputResult){
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


    int fullDisplaywidth = longestUid + 57; // 57 is the amount of static charakters
    //_____________________________________________________________________________________

    dynamicHeaderLinePrint(&fullDisplaywidth, "=");
    printf(" %*s\n ",(longestUid + 34), "All cards in system");
    dynamicHeaderLinePrint(&fullDisplaywidth, "=");

    dynamicHeaderLinePrint(&fullDisplaywidth, "-");
    for (Card *card = cardList->allCards; card < cardList->allCards + cardList->amountOfCards; card++){
        char curentStatus[25];
        if(card ->status == 0){
            strcpy(curentStatus, "No Acces Added to system");
        }else{
            strcpy(curentStatus, "   Acces Added to system");
        }
        
        printf("| Uid: %-*d | %s | Eddit date: %s |\n",longestUid, card ->cardUid, curentStatus, card ->date);
        
        allCardDevideLines(&longestUid, (int)sizeof(curentStatus), (int)strlen(card ->date));
    }   

        *inputResult = ValidateResult("X to go back to main menu\n",  inputBuffer,sizeof(inputBuffer), numValueOfInput, 1, 1);
        if(*inputResult == INPUT_EXIT)
            ;
                    
}