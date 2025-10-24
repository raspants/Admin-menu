#ifndef __SAFE_INPUT_H
#define __SAFE_INPUT_H
#include <stdbool.h>
#include <ctype.h> 
#include "cardStructure.h"

typedef enum {
    INPUT_RESULT_OK,
    INPUT_RESULT_NO_INPUT,
    INPUT_RESULT_TOO_LONG,
    INPUT_RESULT_INVALID,
    INPUT_EXIT
} INPUT_RESULT;

void bufferFlush();
INPUT_RESULT GetInput(char* prompt, char* buff, int maxSize, long *numValueOfInput, const int rangeValueMin, const int rangeValueMax);

INPUT_RESULT ValidateResult(char* prompt, char* buff, int maxSize, long* numValueOfInput, const int rangeValueMin, const int rangeValueMax); 

#endif