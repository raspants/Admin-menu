#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "printcards.h"
#include "remoteopen.h"

void remoteOpen();
void cardsInSystem();
 
Card users[10];


void addRemoveAccess(Card *users, int choise, int *amountOfCards){
    //int cardUid; gör slumpmässiga tal sen
    switch (choise)
    {
    case 1: //For adding new users
        printf("Enter new users number, five didgits\n");
        scanf(" %d", &users ->cardUid);
        printf("Enter acces status, 0.No acces, 1.Acces\n");
        scanf(" %d", &users ->status);
        printf("Enter todays date in this format: YYYYMMDD\n");//ska autoskanna datum
        scanf(" %d", &users ->date);
        *amountOfCards = *amountOfCards + 1;
        break;
    case 2:
        int cardnum; //for altering acces/removing profile
        printf("These are the curent cards in the system:\n");
        cardsInSystem(users, amountOfCards);
        printf("Enter the Uid of the users you want to Acces:\n");
        scanf(" %d", &cardnum);

        for(Card *card = users; card < users + *amountOfCards; card++){
            if(card ->cardUid == cardnum){
                printf(" Card: %d  was found, Do you want to 1.Adjust acces or 2.Remove a profile?\n", cardnum);
                scanf(" %d", &choise);
                if (choise == 1){
                    printf("shold the users have acces or not? 1.Yes, 2.No\n");
                    scanf(" %d", &choise);
                    if(choise == 1){
                        card ->status = 1;
                        printf("Acces has been updated and added on the users\n");
                    }else if(choise == 2){
                        card ->status = 0;
                        printf("Acces has been updated uppdated and removed on the users\n");
                    }
                }else if(choise == 2){            
                    printf("Are you want to sure you want to REMOVE the users profile? 1.Yes, 2.No\n");
                    scanf(" %d", &choise);
                    if(choise == 1){
                        card ->status = 1;
                        *amountOfCards = *amountOfCards -1;
                        printf("Acces has been updated\n");
                    }else{
                        printf("Unexpected error, somthing went wrong\n");
                    }
                }    
            } 
        }
        printf("No users with Uid nr: %d was found.",users ->cardUid);
            break;
    default:
        break;
    }   
}
void fileRead(FILE *fp, int *amountOfCards){
    
    //Lagras i .txt och läses in när man öppnar programet
   
    if(fp == NULL){
        printf("Error: Failed to read file\n");
    }else{
        printf("File reed succesfully\n");
        fscanf(fp, " %d", amountOfCards);
    }
    
}

int main(){
    int amountOfCards;
    FILE *fp;
    fp = fopen("data.txt", "r");
    fileRead(fp, &amountOfCards);
    fclose(fp);
    printf(" %d!!!\n", amountOfCards);///Ta bort sen
    
    while(true){
        printMenue();
        int option;
        scanf(" %d", &option);
        switch(option){
            case 1:
                remoteOpen();
                break;
            case 2:
                if(amountOfCards > 0){
                    cardsInSystem(users, &amountOfCards);
                }else{
                    printf("There are curently no users in the system\n");
                    break;
                }
                break;
            case 3:
                int choise;
                printf("Do you want to 1.Add or 2.Adjust/Remove profile?\n");
                scanf(" %d", &choise);
                start:
                if(choise == 1){
                    addRemoveAccess(&users[amountOfCards], choise, &amountOfCards);
                    //amountOfCards++;
                    printf(" %d", amountOfCards);
                    printf("Do you want to add another user? 1.Yes, 2.No\n");
                    scanf(" %d", &choise);
                    if(choise == 1){
                        goto start;
                    }else{
                        break;
                    }
                }else if(choise == 2){
                    printf("Hello");
                    addRemoveAccess(users, choise, &amountOfCards);
                    //amountOfCards--;
                }else{
                    printf("Error: %d is not a valid choise", choise);
                }
                break;
            case 4:
                //spara data innan stännga?
                return 0;
            case 9:
                break;
            default:
                printf("Error: %d is invalid input\n", option);
                continue;

        } 
    }
  
    return 0;
}



