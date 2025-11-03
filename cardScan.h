#include <stdio.h>
#include "cardStructure.h"
#include "printcards.h"
#include "remoteopen.h"
#include "safeinput.h"

#ifndef CARDSCAN_H
#define CARDSCAN_H

void cardScan(CARDLIST *cardList, char* buff, size_t inputBufferSize, long* numValueOfInput, INPUT_RESULT *inputResult);

#endif