#ifndef CARDSTRUCTURE_H
#define CARDSTRUCTURE_H


typedef struct{
    int cardUid; 
    int status;
    int date;
    } Card;
typedef struct{
    Card *allCards;
    int amountOfCards;
} CARDLIST;

#endif