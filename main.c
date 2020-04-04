//Student's name: Danielle Agat Levi
//Student's ID: 313357329

/* This program gets from the user strings array and an array of cells.
 * Then it removes those cells from the strings array and prints the array after the changes.
 */

#include <stdio.h>
#include <stdlib.h>

#define END_OF_STR '\0'
#define ENTER '\n'

//A given function - sets pointers to cells in a char matrix.
char** setPtrToCharsArray(char** str_array);

//This function gets a pointer to an array of strings and an array of pointers to chars in those string, and removes the chars of the pointers array.
unsigned int RemoveFromStrArray(char ***str_array, unsigned int str_array_size, char** ptr_to_chars_array);

//This function replace all values of a given pointers array into ENTER.
int replaceArrWithFlags(char** ptr_to_chars_array);

//This function gets an array of strings and removes the empty strings from it.
char** removeEmptyCells(char** str_array, unsigned int str_array_size);

//This function gets an array of strings and removes all the '\n' chars from it.
// If there's left empty strings then it returns the amount.
int removeFlagsFromArr(char** str_array, unsigned int* pSize);

//This function gets a string and removes all the '\n' chars in it
int removeFlagsFromStr(char* str , unsigned int* pSize);

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
    replaceArrWithFlags(ptr_to_chars_array);
    unsigned int numOfRemovedCells = removeFlagsFromArr(*str_array,&str_array_size);
    *str_array = removeEmptyCells(*str_array,str_array_size);
    return numOfRemovedCells;
}

int replaceArrWithFlags(char** ptr_to_chars_array){
    int size = 0;
    for(int i=0; ptr_to_chars_array[i] != NULL ; i++){
        *(ptr_to_chars_array[i]) = ENTER; // Changes the pointer's value to '\n' (since we know '\n' will never appear inside our given strings
        size++;
    }
    return size;
}

char** removeEmptyCells(char** str_array, unsigned int str_array_size){
    int index = 0;
    char** temp = (char**)malloc(str_array_size * sizeof(char*));
    checkIfMallocSucceeded(temp);
    for(int i=0; index < str_array_size ; i++){
        if(*(str_array[i]) != END_OF_STR){
            temp[index] = str_array[i];
//            println(temp[index]);
            index++;
        }
    }
    free(str_array);
    return temp;
}

int removeFlagsFromArr(char** str_array, unsigned int* pSize){
    int size = *pSize, strSize, removedFlagsStr,emptyCells = 0;
    for(int i=0 ; i < size ; i++){
        removedFlagsStr = removeFlagsFromStr(str_array[i],&strSize);
        if(strSize == 0){ // Meaning there is only one char - the EOF char
            emptyCells++;
        }else if(removedFlagsStr != 0) { //If the array's size was changes then reallocate memory
            str_array[i] = (char*)realloc(str_array[i],sizeof(char)*strSize);
            checkIfMallocSucceeded(str_array[i]);
        }
    }
    *pSize = (size - emptyCells);
    return emptyCells;
}

int removeFlagsFromStr(char* str , unsigned int* pSize){
    int removedFlags = 0, validChars = 0, index =0;

    for(int i=0; str[index] != END_OF_STR ; i++,index++){
        while(str[i] == ENTER){ //Skip all flags
            removedFlags++;
            i++;
        }
        if(str[i] != END_OF_STR){
            validChars++;
        }
        if(removedFlags != 0) //insert a valid char into the temp array
            str[index] = str[i];
    }
    *pSize = validChars;
    return removedFlags;
}


char** getStrArrayInput(int* pSize){
    int size;
    scanf("%d",&size);

    char** str_array = (char**)malloc(sizeof(char*) * size);
    checkIfMallocSucceeded(str_array);

    for(int i=0; i<size; i++){
        str_array[i] = scanLine();
    }

    *pSize = size;
    return str_array;
}

char* scanLine(){
    int phySize = 2,logSize=0;
    char* line = (char*)malloc(sizeof(char)*phySize);
    checkIfMallocSucceeded(line);

    char scanned;
    while((scanned = getchar())== ENTER); //Emptying the buffer from previous inputs.

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
        printf("%c",line[i]);
    printf("\n");
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