#include <stdio.h>
#include "cardStructure.h"
#include "timeDelay.h"
#include "colorpallet.h"

void remoteOpen(Card *profile){ 
    
    if(profile ->status == 1){
    printf(CYAN"CURENTLY LAMP IS: "BOLD GREEN"Green"RESET"\n");
    timeDelay(3);
    }
    else if(profile ->status == 0){
        printf(CYAN"CURENTLY LAMP IS: "BOLD RED"RED"RESET"\n");
        timeDelay(3);
       }else{
        printf(RED"Card not found in system\n"RESET);
        timeDelay(3);
    }
    return;
}