#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "menu.h"

void remoteOpen();
void cardsInSystem();
 
typedef struct{
    int cardUid; 
    int status;
    int date;
    } Card;
    Card users[10];


void addRemoveAccess(Card *card, int *choise){
 
    if(choise == 1){
        //int cardUid; gör slumpmässiga tal sen
        //int date; ska autoskanna datum
        printf("Enter new card number, five didgits\n");
        scanf(" %d", &card ->cardUid);
        printf("Enter acces status, 0.No acces, 1.Acces\n");
        scanf(" %d", &card ->status);
        printf("Enter todays date in this format: YYYY-MM-DD\n");
        scanf(" %d", &card ->date);
    }else if(choise == 2){
        /*tuf kod som tar bor användare
        1.vilken användare vill du ta bort? baserat på kortnummer
        2. meddela info och fråga igen för att bekräfta.
        3.stäm av om användare finns.
        */
    }
}

void cardsInSystem(Card *user){
    printf("All cards in system\n");
    char curentStatus[25];
        if(user ->status == 0){
            strcpy(curentStatus, "No Acces Added to system");
        }else{
            strcpy(curentStatus, "Acces Added to system");
        } 
        printf("Uid: %d   %s:    %d", users ->cardUid, curentStatus, users ->date);
}

int main(){
    int numberOfCards = 0;//Lagras i .txt och läses in när man öppnar programet
    while(true){
        printMenue();
        int option;
        scanf(" %d", &option);
        switch(option){
            case 1:
                remoteOpen();
                break;
            case 2:
                if(numberOfCards > 0){
                    for(int i = 0; i < numberOfCards; i++){
                    cardsInSystem(&users[i]);
                    }
                }else{
                    printf("There are curently no users in the system\n");
                    break;
                }
            case 3:
               int choise;
                printf("Do you want to add or remove a user? 1.Add, 2.Remove\n");
                scanf(" %d", &choise);
                if(choise == 1 || choise == 2){
                    addRemoveAccess(&users[numberOfCards], &choise);
                }else{
                    printf("Error: %d is not a valid choise");
                }
                break;
            case 4:
                goto exit;
            case 9:
            //code
            break;
            default:
            printf(" %d is invalid input\n", option);
            continue;

        } 
    }
    exit:
    return 0;
}

void remoteOpen(){ 
    printf("CURENTLY LAMP IS: Green\n");
    int retTime = time(0) + 3;
    while (time(0) < retTime)
	    ;
}
