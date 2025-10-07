#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void remoteOpen(){ 
    printf("CURENTLY LAMP IS: Green\n");
    int retTime = time(0) + 3;
    while (time(0) < retTime)
	    ;
}

int main(){
    while(true){
        printf("Admin menu\n");
        printf("1. Remote open door\n");
        printf("2. List all cards in system\n");
        printf("3. Add/remove access\n");
        printf("4. Exit\n");
        printf("9. FAKE TEST SCAN CARD\n");
        printf("Select option\n");

        int option;
        scanf(" %d", &option);
        switch(option){
            case 1:
                remoteOpen();
                break;
            case 2:
                //code
                break;
            case 3:
                //code
                break;
            case 4:
                goto exit;
        } 
    }
    exit:
    return 0;
}