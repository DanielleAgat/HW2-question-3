//Student's name: Danielle Agat Levi
//Student's ID: 313357329

/* This program gets from the user strings array and an array of cells.
 * Then it removes those cells from the strings array and prints the array after the changes.
 */

#include <stdio.h>
#include <stdlib.h>

#define END_OF_STR '\0'
#define ENTER '\n'

char** setPtrToCharsArray(char** str_array){
    char** res;
    int size, i;
    int str_array_row, str_array_col;

    scanf("%d", &size); // Get number of ptrs
    res = (char**)malloc(sizeof(char*)*(size+1)); // Add 1 for NULL at the end

    for (i = 0; i < size; i++){
        scanf("%d", &str_array_row);
        scanf("%d", &str_array_col);
        res[i] = str_array[str_array_row] + str_array_col;
    }
    res[size] = NULL; // Set the last one to NULL
    return res;
}

//This function gets a pointer to an array of strings and an array of pointers to chars in those string, and removes the chars of the pointers array.
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char** ptr_to_chars_array);

//This function gets a number of strings from the user, separated by ENTER, and returns an array of strings.
char** getStrArrayInput(int* pSize);

//This function scans a line of strings.
char* scanLine();

//This function gets an str array and prints it.
void printArray(char** str_array,int size);

//This function prints a given string.
void println(char* line);

//This function frees a strings array.
void freeArray(char** str_array,int size);

//This method checks if memory allocation succeded.
void checkIfMallocSucceeded(void* ptr);


int main(){
    char** str_array;
    unsigned int str_array_size;
    char** ptr_to_chars_array;
    unsigned int res;

    str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)
    ptr_to_chars_array = setPtrToCharsArray(str_array);
    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);
    printArray(str_array, str_array_size - res);

    // Free memory
    freeArray(str_array, str_array_size - res);
    free(ptr_to_chars_array);
}


unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char** ptr_to_chars_array){

}


char** getStrArrayInput(int* pSize){
    int size;
    scanf("%d",&size);

    char** str_array = (char**)malloc(sizeof(char*) * size);
    checkIfMallocSucceeded(str_array);

    for(int i=0; i<size; i++){
        str_array[i] = scanLine();
    }
}

char* scanLine(){
    int phySize = 2,logSize=0;
    char* line = (char*)malloc(sizeof(char)*phySize);
    checkIfMallocSucceeded(line);

    char scanned = getchar();
    while(scanned != ENTER ){ //scans a string until Enter is being scanned
        if(logSize < phySize){
            line[logSize++] = scanned;
            scanned = getchar();
        }else{
            line = (char*)realloc(line,sizeof(char)*phySize * 2);
            checkIfMallocSucceeded(line);
            phySize *= 2;
        }
    }

    if(phySize > logSize){
        line[logSize++] = END_OF_STR;
        if(phySize > logSize) {
            line = (char*)realloc(line, sizeof(char) * logSize);
            checkIfMallocSucceeded(line);
        }
    }else{
        line = (char*)realloc(line,sizeof(char)*(++logSize));
        checkIfMallocSucceeded(line);
        line[logSize] = END_OF_STR;
    }

    return line;
}

void printArray(char** str_array,int size){
    for(int i=0; i<size; i++)
        println(str_array[i]);
}

void println(char* line){
    for(int i=0; line[i] != '\0'; i++)
        printf(line[i]);
}

void freeArray(char** str_array,int size){
    for(int i=(size-1); i >=0 ; i--)
        free(str_array[i]);
}

void checkIfMallocSucceeded(void* ptr){
    if(ptr == NULL){
        printf("ERROR: Out of memory!\n");
        exit(1);
    }
}