#include <stdio.h>
#include <stdlib.h>
#include "cardStructure.h"

#ifndef FILEHANDELING_H
#define FILEHANDELING_H

void readFromFile(const char *filename, CARDLIST *cardList, int *amountOfCards);
void reWrihtToFile(const char *filename, CARDLIST *cardList, int *amountOfCards);

#endif

