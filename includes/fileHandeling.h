#ifndef FILEHANDELING_H
#define FILEHANDELING_H

#include "cardStructure.h"

void readFromFile( char *filename, CARDLIST *cardList, int *amountOfCards);
void reWrihtToFile(const char *filename, CARDLIST *cardList, int *amountOfCards);

#endif

