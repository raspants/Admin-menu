#include <time.h>
#include <stdio.h>
#include "cardStructure.h"

void remoteOpen(Card *profile){ 
    
    if(profile ->status == 1){
    printf("CURENTLY LAMP IS: Green\n");
    int retTime = time(0) + 3; //testas sleep() och Sleep()
    while (time(0) < retTime)
	    ;
    }
    else{
        printf("CURENTLY LAMP IS: RED\n");
        int retTime = time(0) + 3; //testas sleep() och Sleep()
        while (time(0) < retTime)
            ;
    }
}