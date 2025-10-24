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

int main(){
    CARDLIST cardList;
    cardList.allCards = NULL;
    cardList.amountOfCards = 0;
    const char filename[] = "data.txt";
    char inputBuffer[64]; // store user input
    long numValueOfInput;
    INPUT_RESULT inputResult; //stores the return from GETINPUT
  
    readFromFile(filename,&cardList, &cardList.amountOfCards); //retreve data form file

    while(true){
        printMenue();
        int option;
        int subOption;

        inputResult = ValidateResult("Select menu option\n", inputBuffer,sizeof(inputBuffer), &numValueOfInput, 1, 9);
    
        option = (int)numValueOfInput;
        switch(option){
        case 1:
            remoteOpen(&admin); //calls remotedoor open with admin profile whome hase acces
            break;
        case 2:
            if(cardList.amountOfCards > 0 && cardList.allCards != NULL){ //check if there are cards in system
                cardsInSystem(&cardList);   // list all cards for user
            }else{
                printf("There are curently no cards in the system\n");
            }
            break;

        case 3:

            do{    
                inputResult = ValidateResult("\nDo you want to 1.Add, 2.Adjust/Remove profile? | Press X to go back\n",  inputBuffer,sizeof(inputBuffer), &numValueOfInput, 1, 2);
                if(inputResult == INPUT_EXIT){
                    break;
                }
               

                subOption  = (int)numValueOfInput;
                
            }while(subOption != 1 && subOption != 2);    

            if(subOption == 1){ 
                do {
                    addRemoveAccess(filename,&cardList, &subOption, &cardList.amountOfCards, inputBuffer, &numValueOfInput, &inputResult);
                    inputResult = ValidateResult("Do you want to add another user? 1.Yes, X.Return to main menu\n", inputBuffer,sizeof(inputBuffer), &numValueOfInput, 1, 1);
                    if(inputResult == INPUT_EXIT){
                        break;
                    }

                    


                    subOption = (int)numValueOfInput;    
                    if(subOption != 1){
                        printf("Nonvalid option\n");
                        continue;
                    }    
                    
                }while(subOption == 1); 
                break;
            }else if(subOption == 2){ //adjust or remove vard profile
                do{
                    if(cardList.amountOfCards == 0){
                        printf("No cards curently in system\n");
                        break;
                    }

                    inputResult = addRemoveAccess(filename,&cardList, &subOption, &cardList.amountOfCards, inputBuffer, &numValueOfInput, &inputResult);
                    if(inputResult == INPUT_EXIT){
                        break;
                    }
                
                    inputResult = ValidateResult("Do you want to acces another card profile? 1.Yes, X.Return to main menu\n", inputBuffer,sizeof(inputBuffer), &numValueOfInput, 1, 1);
                    if(inputResult == INPUT_EXIT){
                        break;
                    }
                    subOption = (int)numValueOfInput;   
                    if(subOption != 1){
                        printf("Nonvalid option\n");
                        continue;
                    }    
                }while(subOption == 1);
            }
            
        case 4:
            //spara data innan stännga?
            free(cardList.allCards);
            return 0;
        case 9:
            cardScan(&cardList);
            break; 
        default:
            printf("Invalid option\n");
            continue;
        }
    }
}