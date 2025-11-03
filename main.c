#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "printcards.h"
#include "remoteopen.h"
#include "fileHandeling.h"
#include "addRemoveAcces.h"
#include "cardStructure.h"
#include "adminprofile.h"
#include "cardScan.h"
#include "safeinput.h"
#include "clearCls.h"
#define INPUT_BUFF_SIZE 64


int main(){
    CARDLIST cardList;
    cardList.allCards = NULL;
    cardList.amountOfCards = 0;
    const char filename[] = "data.txt";
    char inputBuffer[INPUT_BUFF_SIZE]; // store user input
    long numValueOfInput;
    INPUT_RESULT inputResult; //stores the return from GETINPUT
  
    readFromFile(filename,&cardList, &cardList.amountOfCards); //retreve data form file

    while(true){
       
        printMenue();
        int option;
        int subOption;

        inputResult = ValidateResult("       Select option\n\n", inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 9);
    
        option = (int)numValueOfInput;
        switch(option){
        case 1:
            remoteOpen(&admin); //calls remotedoor open with admin profile whome hase acces
            break;
        case 2:
            if(cardList.amountOfCards > 0 && cardList.allCards != NULL){ //check if there are cards in system
                cardsInSystem(&cardList, inputBuffer, INPUT_BUFF_SIZE, &numValueOfInput, &inputResult);   // list all cards for user
            }else{
                printf("There are curently no cards in the system\n");
            }
            break;

        case 3:
   
                inputResult = ValidateResult("\nDo you want to 1.Add, 2.Adjust/Remove profile? | Press X to go back\n",  inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 2);
                if(inputResult == INPUT_EXIT){
                    break;
                }
                option = (int)numValueOfInput;
             

            if(option == 1){ 
                do {
                    addRemoveAccess(filename,&cardList, &option, &cardList.amountOfCards, inputBuffer, INPUT_BUFF_SIZE, &numValueOfInput, &inputResult);
                    
                    inputResult = ValidateResult("Do you want to add another user? 1.Yes, X.Return to main menu\n", inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 1);
                    if(inputResult == INPUT_EXIT){
                        break;
                    }
                    subOption = (int)numValueOfInput;    
                     
                }while(subOption == 1); 
                break;
            }else if(option == 2){ //adjust or remove card profile
                do{
                    if(cardList.amountOfCards == 0){
                        printf("No cards curently in system\n");
                        break;
                    }

                    addRemoveAccess(filename,&cardList, &option, &cardList.amountOfCards, inputBuffer, INPUT_BUFF_SIZE,  &numValueOfInput, &inputResult);
                    
                    inputResult = ValidateResult("Do you want to acces another card profile? 1.Yes, X.Return to main menu\n", inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 1);
                    if(inputResult == INPUT_EXIT){
                        break;
                    }
                    subOption = (int)numValueOfInput;   
                    
                }while(subOption == 1);
                break;
            }   
        case 4:
            cardScan(&cardList, inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, &inputResult);
            break; 

        case 5:
            free(cardList.allCards);
            return 0;

        default:
            printf("Invalid option\n");
            continue;
        }
    }
}