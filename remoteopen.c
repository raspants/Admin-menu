//#include <time.h>
#include <stdio.h>
#include "cardStructure.h"
#include "timeDelay.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLD    "\033[1m"

void remoteOpen(Card *profile){ 
    
    if(profile ->status == 1){
    printf("CURENTLY LAMP IS: "BOLD GREEN"Green"RESET"\n");
    timeDelay(3);
    }
    else if(profile ->status == 0){
        printf("CURENTLY LAMP IS: "BOLD RED"RED"RESET"\n");
        timeDelay(3);
       }else{
        printf("Card not found in system\n");
    }
    return;
}