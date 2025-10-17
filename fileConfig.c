#include <stdio.h>
FILE *fp;

void fileRead(FILE *fp, int *amountOfCards){
    if(fp == NULL){
        printf("Error: Failed to open file\n");
    }else{
        printf("File opend succesfully\n");
        fscanf(fp, " %d", amountOfCards);
    }
}
void fileWright(FILE *fp, int *amountOfCards){
    if(fp == NULL){
        printf("Error: Failed to open file\n");
    }else{
        printf("File opend succesfully\n");
        fprintf(fp, " %d", *amountOfCards);  
    }   
}

/*void fileCardWright(FILE *fp, int *amountOfCards){
    if(fp == NULL){
        printf("Error: Failed to open file\n");
    }else{
        printf("File opend succesfully\n");
        fprintf(fp, " %d", *amountOfCards);  
    }   
}*/


