#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "safeinput.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"


bool parseLong(const char *str, long *val)
{
    char *temp;
    bool rc = true;
    errno = 0;
    *val = strtol(str, &temp, 0);

    if (temp == str || *temp != '\0' ||
        ((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE))
        rc = false;

    return rc;
}



bool parseFloat(const char *str, float *val)
{
    char *temp;
    bool rc = true;
    errno = 0;
    *val = strtof(str, &temp);

    if (temp == str || *temp != '\0' )
        rc = false;

    return rc;
}



INPUT_RESULT GetInput(char* prompt, char* buff, int maxSize, long* numValueOfInput, const int rangeValueMin, const int rangeValueMax)
{

	if (prompt != NULL && strlen(prompt) > 0)
	{
		printf("%s", prompt);
	}

	if (fgets(buff, maxSize, stdin) == NULL || (strlen(buff) == 1 && buff[0] == '\n')) // treat as empty
	{
		printf(BOLD RED"ERROR_MESSAGE: NO_INPUT_DETECTED\n"RESET);
		
		return INPUT_RESULT_NO_INPUT; 
	}

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.

	if (buff[strlen(buff) - 1] != '\n') {
		int extra = 0;
		char ch;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;

		if (extra == 1) {
        	printf(BOLD RED"ERROR_MESSAGE: INVALID_INPUT_LEGNT, allowed length :%d characters.\n"RESET, maxSize - 2);
        	return INPUT_RESULT_TOO_LONG;
		}
	}

	buff[strlen(buff) - 1] = '\0';
	

	if(toupper(buff[0]) == 'X' && buff[1] == '\0') // if input 'X' aka user vants to go a back to main menu
		return INPUT_EXIT;
    
	if(!parseLong(buff, numValueOfInput)) // if input not a number
	{
		printf(BOLD RED"ERROR_MESSAGE: INVALID_INPUT_TYPE\n"RESET);
		return INPUT_RESULT_INVALID;
	}
    
	
	if((int)*numValueOfInput > rangeValueMax || (int)*numValueOfInput < rangeValueMin){
		printf(BOLD RED"ERROR_MESSAGE: INPUT_OUT_OF_RANGE\n"RESET);
		return INPUT_RESULT_INVALID;
	}

	// Otherwise remove newline and give string back to caller.

	return INPUT_RESULT_OK;
}
INPUT_RESULT ValidateResult(char* prompt, char* buff, int maxSize, long* numValueOfInput,  const int rangeValueMin, const int rangeValueMax){
	INPUT_RESULT result;
	while(true){
		result = GetInput(prompt, buff, maxSize, numValueOfInput, rangeValueMin, rangeValueMax);
		if(result == INPUT_EXIT){
			return INPUT_EXIT;
		}
		if(result == INPUT_RESULT_OK){
			return INPUT_RESULT_OK;
		}
		continue;
	}
}

