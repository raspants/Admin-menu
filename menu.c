#include <stdio.h>
#include "menu.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void printMenue(){
    clearCls();
    printf(GREEN"\n\n\n==============================\n");
    printf(BOLD YELLOW"          Admin menu\n");
    printf(GREEN"==============================\n");
    printf(CYAN" [1] Remote open door \n");
    printf(" [2] List all cards in system\n");
    printf(" [3] Add/remove access\n");
    printf(" [4] SCAN CARD\n");
    printf(" [5] Exit\n");
    printf(GREEN"==============================\n\n\n"RESET);
}