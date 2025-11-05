#include <time.h>

void timeDelay(const int delayTime){
int retTime = time(0) + delayTime; 
    while (time(0) < retTime)
	    ;
        return;
}