#ifndef ADDREMOVEACCES_H
#define ADDREMOVEACCES_H

#include "cardStructure.h"
#include "safeinput.h"

int addRemoveAccess(const char *filename, CARDLIST *cardList, int *option,
                    int *amountOfCards, char *inputBuffer, size_t inputBufferSize, 
                    long *numValueOfInput, INPUT_RESULT *inputResult, const char* password);

int sortCardArray(CARDLIST *cardList, int *newCard);

#endif