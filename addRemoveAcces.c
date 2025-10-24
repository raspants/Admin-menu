#include <time.h>
#include <stdio.h>
#include "addRemoveAcces.h"


int addRemoveAccess(const char *filename, CARDLIST *cardList, int *option, int *amountOfCards, char *inputBuffer, long *numValueOfInput){
    
    int acces;

    switch (*option){
    case 1: //For adding new user
        cardList->allCards = realloc(cardList->allCards, (sizeof(Card) * (*amountOfCards +1)));
        
        int newCard = 110001;

        if(*amountOfCards == 0){ //kan evntuellt bli problem om man har precis "fel" kortnummer i txt filen i förhållande till mängden användare
            cardList ->allCards[*amountOfCards].cardUid = newCard;
        }else{    
            while(true){
                for(int i = 0; i < *amountOfCards; i++){
                    if(cardList ->allCards[i].cardUid == newCard){
                        newCard++;
                    }else{
                        cardList ->allCards[*amountOfCards].cardUid = newCard;
                        break;
                    }
                }
                break;
            }
        }
        while(true){
            if(GetInput("Enter acces status, 0.No acces, 1.Acces | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 

            acces = (int)*numValueOfInput;//parse from long to int, wold be extream edge case to get overflow 
            if(acces == 1 || acces == 0){
                cardList ->allCards[*amountOfCards].status = acces;
                break;
            }else{
                printf("Invalid input\n");   
                continue;
            }
        }
        
        time_t timeFetch = time(NULL);
        struct tm tm = *localtime(&timeFetch);
        
        int timeAndDate = (tm.tm_year + 1990) * 10000 + (tm.tm_mon +1) * 100 + (tm.tm_mday);
        cardList ->allCards[*amountOfCards].date = timeAndDate;

        //printf("Enter todays date in this format: YYYYMMDD\n");//ska autoskanna datum
        //scanf(" %d", &cardList ->allCards[*amountOfCards].date);///

        *amountOfCards = *amountOfCards + 1;

        reWrihtToFile(filename, cardList, amountOfCards);
        return 0;

    //for altering acces/removing profile    
    case 2:

        int cardnum;
        int index;
        bool foundcard = false;
        int action;

        printf("These are the curent cards in the system:\n");
        cardsInSystem(cardList);

        while(true){
            if(GetInput("Enter the UID of the cardprofile you want to Acces  | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 

            cardnum = (int)*numValueOfInput;
            for(int i = 0; i < *amountOfCards; i++){
                if(cardList ->allCards[i].cardUid == cardnum){
                    printf(" Card UID: %d  was found\n", cardnum); 
                    index = i;
                    foundcard = true;
                    break;
                }
            }
            if(!foundcard){
                printf("No card with Uid: %d was found, reenter a valid Uid\n",cardnum);
                continue;
            }               
        } 

        while(true){
            if(GetInput("1.Adjust acces, 2.Remove a profile  | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 
            break;
        }
    
        action = (int)*numValueOfInput;
        if(action == 1){
            while(true){
                if(GetInput("Shold the card have acces or not? 0.No, 1.Yes\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                    if(INPUT_EXIT){
                        return INPUT_EXIT;
                    }else{
                        continue;
                    }
                }  
                acces = (int)*numValueOfInput;
                if(acces == 1){
                    cardList ->allCards[index].status = 1;
                    reWrihtToFile(filename, cardList, amountOfCards);
                    printf("Acces has been updated and added on the card\n");
                    return 0;
                }else if(acces == 0){
                    cardList ->allCards[index].status = 0;
                    reWrihtToFile(filename, cardList, amountOfCards);
                    printf("Acces has been updated uppdated and removed on the card\n");
                    return 0;
                }else{
                    printf("Invalid input\n");
                }
            }  
           
        }else if(action == 2){            
            printf("Are you sure you want to REMOVE the allcards profile? 1.Yes, 2.No\n");
 
            while(true){
                if(GetInput("Are you sure you want to REMOVE the allcards profile? 1.Yes, 2.No\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                    if(INPUT_EXIT){
                        return INPUT_EXIT;
                    }else{
                        continue;
                    }
                } 

                int removalVerification;
                removalVerification = (int)*numValueOfInput;

                if(removalVerification == 1){
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
                }else{
                    printf("Profile with Uid: %d will not be removed\n", cardnum);
                    return 0;
                }
            }                         
        }else{
            printf("Invalid input\n"); 
        }
    default:
       return 0;
    }   
}#include <time.h>
#include <stdio.h>
#include "addRemoveAcces.h"


int addRemoveAccess(const char *filename, CARDLIST *cardList, int *option, int *amountOfCards, char *inputBuffer, long *numValueOfInput){
    
    int acces;

    switch (*option){
    case 1: //For adding new user
        cardList->allCards = realloc(cardList->allCards, (sizeof(Card) * (*amountOfCards +1)));
        
        int newCard = 110001;

        if(*amountOfCards == 0){ //kan evntuellt bli problem om man har precis "fel" kortnummer i txt filen i förhållande till mängden användare
            cardList ->allCards[*amountOfCards].cardUid = newCard;
        }else{    
            while(true){
                for(int i = 0; i < *amountOfCards; i++){
                    if(cardList ->allCards[i].cardUid == newCard){
                        newCard++;
                    }else{
                        cardList ->allCards[*amountOfCards].cardUid = newCard;
                        break;
                    }
                }
                break;
            }
        }
        while(true){
            if(GetInput("Enter acces status, 0.No acces, 1.Acces | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 

            acces = (int)*numValueOfInput;//parse from long to int, wold be extream edge case to get overflow 
            if(acces == 1 || acces == 0){
                cardList ->allCards[*amountOfCards].status = acces;
                break;
            }else{
                printf("Invalid input\n");   
                continue;
            }
        }
        
        time_t timeFetch = time(NULL);
        struct tm tm = *localtime(&timeFetch);
        
        int timeAndDate = (tm.tm_year + 1990) * 10000 + (tm.tm_mon +1) * 100 + (tm.tm_mday);
        cardList ->allCards[*amountOfCards].date = timeAndDate;

        //printf("Enter todays date in this format: YYYYMMDD\n");//ska autoskanna datum
        //scanf(" %d", &cardList ->allCards[*amountOfCards].date);///

        *amountOfCards = *amountOfCards + 1;

        reWrihtToFile(filename, cardList, amountOfCards);
        return 0;

    //for altering acces/removing profile    
    case 2:

        int cardnum;
        int index;
        bool foundcard = false;
        int action;

        printf("These are the curent cards in the system:\n");
        cardsInSystem(cardList);

        while(true){
            if(GetInput("Enter the UID of the cardprofile you want to Acces  | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 

            cardnum = (int)*numValueOfInput;
            for(int i = 0; i < *amountOfCards; i++){
                if(cardList ->allCards[i].cardUid == cardnum){
                    printf(" Card UID: %d  was found\n", cardnum); 
                    index = i;
                    foundcard = true;
                    break;
                }
            }
            if(!foundcard){
                printf("No card with Uid: %d was found, reenter a valid Uid\n",cardnum);
                continue;
            }               
        } 

        while(true){
            if(GetInput("1.Adjust acces, 2.Remove a profile  | Press X to go back main menu\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                if(INPUT_EXIT){
                    return INPUT_EXIT;
                }else{
                    continue;
                }
            } 
            break;
        }
    
        action = (int)*numValueOfInput;
        if(action == 1){
            while(true){
                if(GetInput("Shold the card have acces or not? 0.No, 1.Yes\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                    if(INPUT_EXIT){
                        return INPUT_EXIT;
                    }else{
                        continue;
                    }
                }  
                acces = (int)*numValueOfInput;
                if(acces == 1){
                    cardList ->allCards[index].status = 1;
                    reWrihtToFile(filename, cardList, amountOfCards);
                    printf("Acces has been updated and added on the card\n");
                    return 0;
                }else if(acces == 0){
                    cardList ->allCards[index].status = 0;
                    reWrihtToFile(filename, cardList, amountOfCards);
                    printf("Acces has been updated uppdated and removed on the card\n");
                    return 0;
                }else{
                    printf("Invalid input\n");
                }
            }  
           
        }else if(action == 2){            
            printf("Are you sure you want to REMOVE the allcards profile? 1.Yes, 2.No\n");
 
            while(true){
                if(GetInput("Are you sure you want to REMOVE the allcards profile? 1.Yes, 2.No\n", inputBuffer,sizeof(inputBuffer), numValueOfInput) != INPUT_RESULT_OK){
                    if(INPUT_EXIT){
                        return INPUT_EXIT;
                    }else{
                        continue;
                    }
                } 

                int removalVerification;
                removalVerification = (int)*numValueOfInput;

                if(removalVerification == 1){
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
                }else{
                    printf("Profile with Uid: %d will not be removed\n", cardnum);
                    return 0;
                }
            }                         
        }else{
            printf("Invalid input\n"); 
        }
    default:
       return 0;
    }   
}