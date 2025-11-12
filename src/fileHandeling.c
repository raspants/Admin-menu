#include <stdio.h>
#include <stdlib.h>
#include "fileHandeling.h"
#include "cardStructure.h"
#include "timeDelay.h"

void readFromFile( char *filename, CARDLIST *cardList, int *amountOfCards){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: Failed to open file %s\n", filename);

        //fp = fopen(filename, "w");
        timeDelay(5);
        *amountOfCards = 0;
        return;
    }
    if( fscanf(fp, " %d", &cardList ->amountOfCards) != 1){
        printf("Error: Faild reading user count");
        timeDelay(5);
        *amountOfCards = 0;
        fclose(fp);
        reWrihtToFile(filename, cardList, amountOfCards);
        return;
    }

    cardList->allCards = malloc((sizeof(Card) * (*amountOfCards)));
        
    if( cardList -> allCards == NULL){
        printf("Error: memory allocation failed");
        timeDelay(5);
        fclose(fp);
        return;
    }
    for(int i = 0; i < *amountOfCards; i++){
        if(fscanf(fp, " %d %d %17[0-9- :]", &cardList ->allCards[i].cardUid, &cardList ->allCards[i].status, cardList ->allCards[i].date) != 3){
            printf("Error reading card at line: %d\n", i +2 );
            timeDelay(5);
            *amountOfCards = i;
        }        
    }
    fclose(fp);
}

void reWrihtToFile(const char *filename, CARDLIST *cardList, int *amountOfCards){
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error: Failed to open file %s\n", filename);
        timeDelay(5);
        return;
    }
    
    fprintf(fp, "%d\n", cardList ->amountOfCards);
    
    for(int i = 0; i < *amountOfCards; i++){
        if(fprintf(fp, "%d %d %s\n", cardList ->allCards[i].cardUid, cardList ->allCards[i].status, cardList ->allCards[i].date) <0){
            
            perror("ERROR: Filed to wriht data for card\n");
            timeDelay(5);
            fclose(fp);
        }
    }         
    
    fclose(fp);
}


