#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cardStructure.h"
#include "printcards.h"
#include "safeinput.h"
#include "fileHandeling.h"



#ifndef ADDREMOVEACCES_H
#define ADDREMOVEACCES_H

int addRemoveAccess(const char *filename, CARDLIST *cardList, int *choise, int *amountOfCards, char *inputBuffer, long *numValueOfInput, INPUT_RESULT *inputResult);

#endif