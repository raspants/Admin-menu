#ifndef CARDSINSYSTEM_H
#define CARDSINSYSTEM_H
typedef struct{
    int cardUid; 
    int status;
    int date;
    } Card;

void cardsInSystem(Card *users, int *amountOfCards);

#endif