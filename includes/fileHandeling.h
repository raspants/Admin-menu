#ifndef FILEHANDELING_H
#define FILEHANDELING_H

#include "cardStructure.h"

void readFromFileBuffer(const char *buffer, size_t buffLength,  CARDLIST *cardList);
char* wrightToFileBuffer(CARDLIST *cardList, size_t *outLength);
void importFromFile(const char *importFilename, const char *filename, CARDLIST *cardList, const char *password);

#endif

