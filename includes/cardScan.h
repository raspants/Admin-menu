#ifndef CARDSCAN_H
#define CARDSCAN_H

#include "cardStructure.h"
#include "safeinput.h"

void cardScan(CARDLIST *cardList, char* buff, size_t inputBufferSize, long* numValueOfInput, INPUT_RESULT *inputResult);

#endif