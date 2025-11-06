#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clearCls.h"
#include "addRemoveAcces.h"
#include "safeinput.h"
#include "cardStructure.h"
#include "printcards.h"
#include "fileHandeling.h"
#include "timeDelay.h"
#include "colorpallet.h"

int sortCardArray(CARDLIST *cardList, int *amountOfCards, int *newCard);

int addRemoveAccess(const char *filename, CARDLIST *cardList, int *option, int *amountOfCards, char *inputBuffer, size_t inputBufferSize, long *numValueOfInput, INPUT_RESULT *inputResult){
    
    //hade kunnat göras i separata funktioner för add, remove och adjust

    switch (*option){
    case 1: //For adding new user
        clearCls();
        cardList->allCards = realloc(cardList->allCards, (sizeof(Card) * (*amountOfCards +1)));
        if (!cardList->allCards) {
            perror("realloc failed");
            exit(EXIT_FAILURE);
        }
        int newCard = 110001; //startingpoint for card Uid
        int acces;
        int insertionPoint = *amountOfCards;

        if(*amountOfCards == 0){ 
            insertionPoint = 0;
            cardList ->allCards[insertionPoint].cardUid = newCard; // assign if no cards i system
        }else{    
      
            for(int i = 0; i < *amountOfCards; i++){ 
                if(cardList ->allCards[i].cardUid <= newCard){ //check all card Uid and increas new Uid untill uniqe
                    newCard++;
                }else{ // when confirmed new Uid is uniq   
                    break;
                }
            }   
        }
        //sort cards befor injekting new card
        insertionPoint = sortCardArray(cardList, amountOfCards, &newCard); //insertionPoint to keep track where to injekt date and acces 

        time_t timeFetch = time(NULL);
        struct tm tm = *localtime(&timeFetch);
        
        unsigned short year = (tm.tm_year + 1900);
        unsigned char month =(tm.tm_mon +1);
        unsigned char day = (tm.tm_mday);
        unsigned char hour = (tm.tm_hour);
        unsigned char minute = (tm.tm_min);

        printf(YELLOW"\n\nNew cardprofile generated:"CYAN" %d\n"GREEN"=================================\n"RESET, newCard); //not inserted in array yet
    
        *inputResult = ValidateResult(YELLOW"\nEnter acces status\n"CYAN"[0] No acces\n[1] Acces\n[X] Return to main menu\n"RESET":", inputBuffer, inputBufferSize, numValueOfInput, 0, 1);
        if(*inputResult == INPUT_EXIT){
            return INPUT_EXIT;
        }
         
        acces = (int)*numValueOfInput;//parse from long to int, wold be extream edge case to get overflow 
        
        cardList ->allCards[insertionPoint].status = acces; //insert acces status at correct index
        cardList ->allCards[insertionPoint].cardUid = newCard; //incert card Uid at correct index
       
        #pragma GCC diagnostic push //ignore error message for overflow risk in formated string print
        #pragma GCC diagnostic ignored "-Wformat-truncation"

        snprintf(cardList ->allCards[insertionPoint].date, sizeof(cardList->allCards[insertionPoint].date), "%04d-%02d-%02d %02d:%02d", //insert date at correct index
                                                                                                        year, month, day, hour, minute);
        #pragma GCC diagnostic pop


        *amountOfCards += 1; //only increment after inserion of date and acces
       
        reWrihtToFile(filename, cardList, amountOfCards); //read new card regestery to file
        return 0;
        
    //for altering acces/removing profile    
    case 2:

        int cardnum;
        int index;
        bool foundcard = false;
        int action;

        

        while(true){
            clearCls();
            cardsInSystem(cardList, inputBuffer, inputBufferSize, numValueOfInput, inputResult);

            *inputResult = ValidateResult(YELLOW"Enter the UID of the cardprofile you want to Acces\n\n"CYAN"[X] Return to main menu\n :"RESET, inputBuffer, inputBufferSize, numValueOfInput, 110001, cardList ->allCards[cardList ->amountOfCards -1].cardUid);
            if(*inputResult == INPUT_EXIT){
                return INPUT_EXIT;
            }

            cardnum = (int)*numValueOfInput;
            for(int i = 0; i < *amountOfCards; i++){
                if(cardList ->allCards[i].cardUid == cardnum){
                    clearCls();
                    printf(CYAN"Card UID: %d  was found\n\n"RESET, cardnum); 
                    index = i;
                    foundcard = true;
                    break;
                }
            }
            if(!foundcard){
                printf(CYAN"No card with Uid: %d was found, reenter a valid Uid\n"RESET,cardnum);
                timeDelay(2);
                continue;
            }
            break;               
        } 

        *inputResult = ValidateResult(YELLOW"Option\n"CYAN"[1] Adjust acces\n[2] Remove a profile\n[X] Return to main menu\n"RESET, inputBuffer, inputBufferSize, numValueOfInput, 1, 2);
        if(*inputResult == INPUT_EXIT){
            return INPUT_EXIT;
        }
 
        action = (int)*numValueOfInput;
        if(action == 1){
           
            *inputResult = ValidateResult(YELLOW"\nShold the cardprofile have\n"CYAN"[0] No acces\n[1] Acces\n"RESET":", inputBuffer, inputBufferSize, numValueOfInput, 0, 1);
            if(*inputResult == INPUT_EXIT){
                return INPUT_EXIT;
            }  
            acces = (int)*numValueOfInput;
            if(acces == 1){
                cardList ->allCards[index].status = 1;
                reWrihtToFile(filename, cardList, amountOfCards);
                printf(CYAN"Acces has been updated and added on the card\n"RESET);
                timeDelay(1);
                return 0;
            }else if(acces == 0){
                cardList ->allCards[index].status = 0;
                reWrihtToFile(filename, cardList, amountOfCards);
                printf(CYAN"Acces has been updated uppdated and removed on the card\n"RESET);
                timeDelay(1);
                return 0;
            }
              
        }else if(action == 2){            
           
 
            *inputResult = ValidateResult(YELLOW"Are you sure you want to REMOVE the cards profile\n"CYAN"[1]"RED" Yes\n"CYAN"[2] No\n"RESET":", inputBuffer, inputBufferSize, numValueOfInput, 1, 2);
            if(*inputResult == INPUT_EXIT){
                return INPUT_EXIT;
            }

            action = (int)*numValueOfInput;

            if(action == 1){
                for(int i = index; i < *amountOfCards -1; i++){
                    cardList ->allCards[i] = cardList ->allCards[i +1];
                }
                *amountOfCards = *amountOfCards - 1;

                if(*amountOfCards > 0){
                    cardList->allCards = realloc(cardList->allCards, (sizeof(Card) * (*amountOfCards)));
                    reWrihtToFile(filename, cardList, amountOfCards);
                    return 0;
                }else{
                    free(cardList ->allCards);
                    cardList -> allCards = NULL;
                    reWrihtToFile(filename, cardList, amountOfCards);
                    return 0;
                }
            }   
            return 0;
        }    
    default:
       return 0;
    }   
}

int sortCardArray(CARDLIST *cardList, int *amountOfCards, int *newCard){ //sort cards in array by card Uid, used later for defining range of carUid input in serch
    
    int i = *amountOfCards -1;

    while( i >= 0 && cardList->allCards[i].cardUid > *newCard){
        cardList->allCards[i + 1] = cardList->allCards[i];
        i--;
    }
 
    return i + 1;
}