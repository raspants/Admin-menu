#ifndef CARDSTRUCTURE_H
#define CARDSTRUCTURE_H


typedef struct{
    int cardUid; 
    int status;
    char date[18];
    } Card;
typedef struct{
    Card *allCards;
    int amountOfCards;
} CARDLIST;

#endif