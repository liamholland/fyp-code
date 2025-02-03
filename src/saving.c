#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saving.h"

#define SAVE_FILE_NAME "results.csv"

int appendToResults(int* conflictArray, int numIterations) {
    FILE* results = fopen(SAVE_FILE_NAME, "r");
    FILE* temp = fopen("temp.csv", "w");

    if(results == NULL) {
        results = fopen(SAVE_FILE_NAME, "w+");
    }

    //write the new data

    char line[1024];
    int lineNum = 0;

    while(fgets(line, 1024, results)) {
        
        //stop the write if a line exceeds the buffer size
        if(strchr(line, "\n") == NULL) {
            printf("line length has exceeded buffer size; aborting write\n");
            fclose(results);
            fclose(temp);

            remove("temp.csv"); //we conserve the previously saved data

            return 1;
        }

        //remove newline from end of line
        line[strcspn(line, "\n")] = '\0';

        if(lineNum < numIterations) {
            fprintf(temp, "%s,%d\n", line, conflictArray[lineNum]);
        }
        else {
            fprintf(temp, "%s,\n", line);   //just add another empty column
        }

        lineNum++;
    }

    //count the number of columns in the old file

    rewind(results);
    fgets(line, 1024, results); //get the first line of the file again
    int numCols = 0;
    for(int i = 0; i < strlen(line); i++) {
        if(line[i] == ',') {
            numCols++;
        }
    }

    fclose(results);

    //construct a string of ',' characters, to fill in empty space
    //this covers the case of the new data being longer than any of the old data

    char* emptyColString;
    if(numCols > 0) {
        //construct the empty col string
        emptyColString = (char*)malloc(sizeof(char) * (numCols + 1));
        for(int i = 0; i < numCols; i++) {
            emptyColString[i] = ',';
        }

        emptyColString[numCols] = '\0';
    }

    //append any leftover data in the new array

    while (lineNum < numIterations) {
        if(numCols > 0) {
            fprintf(temp, "%s,%d\n", emptyColString, conflictArray[lineNum]);
        }
        else {
            fprintf(temp, "%d\n", conflictArray[lineNum]);
        }
        lineNum++;
    }

    fclose(temp);

    remove(SAVE_FILE_NAME);
    rename("temp.csv", SAVE_FILE_NAME);

    return 0;
}

int addBufferColumnToResults(int numColumns) {
    if(numColumns > 10) {
        printf("why would you even want more than 10 empty columns\n");
        return 1;
    }
    
    FILE* results = fopen(SAVE_FILE_NAME, "r");
    FILE* temp = fopen("temp.csv", "w");

    if(results == NULL) {
        printf("cannot add buffer column to non-existent file\n");
        return 1;
    }

    //construct a string of columns

    char columns[11];
    for(int i = 0; i < numColumns; i++) {
        columns[i] = ',';
    }

    columns[numColumns] = '\0'; //string null terminator

    char line[1024];
    while(fgets(line, 1024, results)) {
        //remove newline from end of line
        line[strcspn(line, "\n")] = '\0';

        //rewrite the line with extra columns
        fprintf(temp, "%s%s\n", line, columns);
    }

    fclose(results);
    fclose(temp);

    remove(SAVE_FILE_NAME);
    rename("temp.csv", SAVE_FILE_NAME);

    return 0;
}
