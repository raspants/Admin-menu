#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "menu.h"
#include "timeDelay.h"
#include "printcards.h"
#include "remoteopen.h"
#include "fileHandeling.h"
#include "addRemoveAcces.h"
#include "cardStructure.h"
#include "adminprofile.h"
#include "cardScan.h"
#include "safeinput.h"
#include "clearCls.h"
#include "colorpallet.h"
#include "encryption.h"
#define INPUT_BUFF_SIZE 64
#define CARD_DATA "data/data.enc"
#define IMPORT_DATA "data/import.txt"


int main(){

    CARDLIST cardList;
    cardList.allCards = NULL;
    cardList.amountOfCards = 0;
    char filename[] = CARD_DATA;
    char inputBuffer[INPUT_BUFF_SIZE]; // store user input
    long numValueOfInput;
    INPUT_RESULT inputResult; //stores the return from GETINPUT
    char *fileBuffer = NULL;
    size_t buffLength = 0;
    char confirmation[64];
    char password[64];
    bool authantiaction = false;
    
    clearCls();

    FILE *fp = fopen(CARD_DATA, "rb");
    if(!fp){
        while(true){
            printf("No data found.\nPlease choose a password: ");
            if(fgets(password, sizeof(password), stdin) == NULL){
                continue;
            }
            password[strcspn(password, "\n")] = 0;

            printf("Confirm password: ");
            if(fgets(confirmation, sizeof(confirmation), stdin) == NULL){
                continue;
            }
            confirmation[strcspn(confirmation, "\n")] = 0;

            if(strcmp(password, confirmation) == 0){
                printf("Password was set\n");
                timeDelay(2);
                saveEncryptedCardList(filename, &cardList, password);
                printf("Encrypted data file has been created\n");
                timeDelay(2);
                break;
            }else{
                printf("Passwords do not match, try again.");
                timeDelay(3);
            }
        }

    }else{
        fclose(fp);
    }

    while(!authantiaction){
        printf("Enter password: ");
        if(fgets(password, sizeof(password), stdin) == NULL){
            continue;
        }
        password[strcspn(password, "\n")] =0;

        if(decryptFile(&fileBuffer, &buffLength, filename, password) == 0){
            readFromFileBuffer(fileBuffer, buffLength, &cardList);
            free(fileBuffer);
            authantiaction = true;
        }else{
            printf("Incorrect password, try again");
            timeDelay(1);
            clearCls();
        }
    }
   

    while(true){
       
        printMenue();
        
        int option;
        int subOption;

        inputResult = ValidateResult(YELLOW"       Select option\n\n"CYAN""RESET">", inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 5);
        if(inputResult != INPUT_RESULT_OK){
            continue;
        }
        option = (int)numValueOfInput;
        switch(option){
        case 1:
            remoteOpen(&admin); //calls remotedoor open with admin profile whom has access
            break;
        case 2:
            if(cardList.amountOfCards > 0 && cardList.allCards != NULL){ //check if there are cards in system
                cardsInSystem(&cardList, inputBuffer, INPUT_BUFF_SIZE, &numValueOfInput, &inputResult);   // list all cards for user
            }else{
                printf(CYAN"There are curently no cards in the system\n"RESET);
                timeDelay(2); //to second delay to display message before clear in cli
            }
            break;

        case 3:
                clearCls();
                inputResult = ValidateResult(YELLOW"Option\n"
                                                GREEN"=======================\n"CYAN
                                                "[1] Add new profil\n"
                                                "[2] Adjust/Remove profile\n"
                                                "[X] Return to main menu\n"
                                                GREEN"=======================\n"RESET
                                                ">",  inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 2);

                if(inputResult == INPUT_EXIT){
                    break;
                }
                option = (int)numValueOfInput;
                

            if(option == 1){ 
                do {
                    addRemoveAccess(filename,&cardList, &option, &cardList.amountOfCards, inputBuffer, INPUT_BUFF_SIZE, &numValueOfInput, &inputResult, password);
                    
                    inputResult = ValidateResult(YELLOW"Do you want to add another user\n"
                                                   CYAN"[1] Yes\n[X] Return to main menu\n"
                                                   ">"RESET, inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 1);
                                                   
                    if(inputResult == INPUT_EXIT){
                        break;
                    }
                    subOption = (int)numValueOfInput;    
                     
                }while(subOption == 1); 
                break;
            }else if(option == 2){ //adjust or remove card profile
                do{
                    if(cardList.amountOfCards == 0){
                        printf(CYAN"No cards currently in system\n"RESET);
                        timeDelay(2);
                        break;
                    }

                    addRemoveAccess(filename,&cardList, &option, &cardList.amountOfCards, inputBuffer, INPUT_BUFF_SIZE,  &numValueOfInput, &inputResult, password);
                    
                    inputResult = ValidateResult(YELLOW"Do you want to access another card profile\n"
                                                    CYAN"[1] Yes\n"
                                                        "[X] Return to main menu\n"RESET
                                                        ">", inputBuffer,INPUT_BUFF_SIZE, &numValueOfInput, 1, 1);

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
            importFromFile(IMPORT_DATA, CARD_DATA, &cardList, password);
            break;

        case 6:
            free(cardList.allCards);
            return 0;

        default:
            printf(RED"Invalid option\n");
            timeDelay(2);
            continue;
        }
    }
}