#include <stdio.h>
#include <string.h>

typedef struct{
    int cardUid; 
    int status;
    int date;
    } Card;

void cardsInSystem(FILE *fp, Card *users, int *amountOfCards){
    printf("All cards in system\n");
    for(Card *card = users; card < users + *amountOfCards; card++){
        char curentStatus[25];
        if(card ->status == 0){
            strcpy(curentStatus, "No Acces Added to system");
        }else{
            strcpy(curentStatus, "Acces Added to system");
        }
        
        printf("Uid:%d  %s:  %d\n", card ->cardUid, curentStatus, card ->date);
    } 
        
} 