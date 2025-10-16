#include <time.h>
#include <stdio.h>

void remoteOpen(){ 
    printf("CURENTLY LAMP IS: Green\n");
    int retTime = time(0) + 3;
    while (time(0) < retTime)
	    ;
}