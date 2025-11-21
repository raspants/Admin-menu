#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "clearCls.h"
#include "encryption.h"
#include "fileHandeling.h"
#include "addRemoveAcces.h"
#include "cardStructure.h"
#include "timeDelay.h"

void readFromFileBuffer(const char *buffer, size_t buffLength,  CARDLIST *cardList){
    
    size_t position = 0;
    int successfulScan = 0;

    successfulScan = sscanf(buffer + position, "%d", &cardList ->amountOfCards);
    if(successfulScan != 1 || cardList ->amountOfCards <= 0){
        cardList ->amountOfCards = 0;
        return;
    }

    cardList->allCards = malloc(sizeof(Card) * cardList ->amountOfCards);
        
    if(!cardList -> allCards){
        printf("Error: memory allocation failed");
        timeDelay(5);
        cardList ->amountOfCards = 0;
        return;
    }    
    
    const char *lineStart = strchr(buffer, '\n');
    if(!lineStart){
        return;
    }
    lineStart++;


    for(int i = 0; i < cardList ->amountOfCards; i++){
        successfulScan = sscanf(lineStart, " %d %d %17[0-9- :]", &cardList ->allCards[i].cardUid, 
                                                                 &cardList ->allCards[i].status, 
                                                                 cardList ->allCards[i].date);
        if(successfulScan != 3){
            break;
        }
            
        const char *nextLine = strchr(lineStart, '\n');
        if(!nextLine){
            break;
        }
        lineStart = nextLine +1;
                 
    }
    
}

char* wrightToFileBuffer(CARDLIST *cardList, size_t *outLength){
    
    if(!cardList || cardList ->amountOfCards <= 0){
        *outLength = 0;
        return NULL;
    }
   
    
    size_t bufferSize = 128 + cardList ->amountOfCards *64;
    char *buff = malloc(bufferSize);

    if(!buff){
        return NULL;
    }

    size_t position = 0;

    int written = snprintf(buff + position, bufferSize - position, "%d\n", cardList ->amountOfCards);
    position += written;

    for(int i = 0; i < cardList ->amountOfCards; i++){
        written = snprintf(buff + position, bufferSize - position, "%d %d %s\n", 
                                                                    cardList ->allCards[i].cardUid, 
                                                                    cardList ->allCards[i].status, 
                                                                    cardList ->allCards[i].date);
        position += written;
        
        if(position + 64 >= bufferSize){
            bufferSize *= 2;
            char *temp = realloc(buff, bufferSize);
            if(!temp){
                free(buff);
                *outLength = 0;
                return NULL;
            }
            buff = temp;
        }
        
    }         
    
    *outLength = position;
    return buff;
}

void importFromFile(const char *importFilename, const char *filename, CARDLIST *cardList, const char *password){
    
    clearCls();
    //void readFromFile( char *filename, CARDLIST *cardList, int *amountOfCards){
    FILE *fp = fopen(importFilename, "r");
    if(fp == NULL){
        printf("Error: Failed to open importfile %s\n", importFilename);
        timeDelay(5);
        return;
    }

    char line[256];
    int amountUnique = 0;
    int alreadyStored = 0;

    while (fgets(line, sizeof(line), fp)){

        Card temp;

        if(sscanf(line, " %d %d %17[0-9- :]", &temp.cardUid, &temp.status, temp.date) != 3){ //scan in line from import doc to temp profile
            continue; // if invalid data
        } 

        bool uniqueUid = true;
        for(int i = 0; i < cardList ->amountOfCards; i++){
            if(cardList->allCards[i].cardUid == temp.cardUid){
                uniqueUid = false;
                alreadyStored++;
                break;
            }    
        }
        if(uniqueUid){
            cardList ->allCards = realloc(cardList ->allCards, sizeof(Card) * (cardList->amountOfCards + 1));
            
            if(!cardList->allCards){
                printf("Failed to reallocate memory\n");
                timeDelay(3);
                return;
            }
            int insertionPoint = sortCardArray(cardList, &temp.cardUid); //sorts the array befor injecting a new profile
            cardList->allCards[insertionPoint] = temp;
            cardList->amountOfCards++;
            amountUnique++;

        }                                                 
    }
    

    saveEncryptedCardList(filename, cardList, password);
    printf("Data importation successful\n%d new caraprofiles added to system\n%d caraprofiles already in system and were not imported", amountUnique, alreadyStored);
    timeDelay(5);
    fclose(fp); 
}

