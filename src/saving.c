#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saving.h"

#define CONFLICTS_SAVE_FILE_NAME "conflicts.csv"
#define RESULTS_SAVE_FILE_NAME "results.csv"

#define LINE_BUFFER_SIZE 5012

#define FULL_FILE_NAME_LENGTH 30

//variables to allow for custom file names
char conflictsFullName[FULL_FILE_NAME_LENGTH] = CONFLICTS_SAVE_FILE_NAME;
char resultsFullName[FULL_FILE_NAME_LENGTH] = RESULTS_SAVE_FILE_NAME;

int appendToResults(int* conflictArray, int numIterations) {
    FILE* results = fopen(conflictsFullName, "r");
    FILE* temp = fopen("temp.csv", "w");

    if(results == NULL) {
        results = fopen(conflictsFullName, "w+");
    }

    //write the new data

    char line[LINE_BUFFER_SIZE];
    int lineNum = 0;

    while(fgets(line, LINE_BUFFER_SIZE, results)) {
        
        //stop the write if a line exceeds the buffer size
        if(strchr(line, '\n') == NULL) {
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

    if(lineNum < numIterations) {
        //count the number of columns in the old file
        rewind(results);
        fgets(line, LINE_BUFFER_SIZE, results); //get the first line of the file again
        int numCols = 0;
        for(int i = 0; i < strlen(line); i++) {
            if(line[i] == ',') {
                numCols++;
            }
        }

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
    }

    fclose(results);
    fclose(temp);

    remove(conflictsFullName);
    rename("temp.csv", conflictsFullName);

    return 0;
}

int addBufferColumnToConflictsFile(int numColumns) {
    if(numColumns > 10) {
        printf("why would you even want more than 10 empty columns\n");
        return 1;
    }
    
    FILE* results = fopen(conflictsFullName, "r");
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

    remove(conflictsFullName);
    rename("temp.csv", conflictsFullName);

    return 0;
}

int saveColouringData(int benchmark, int numNodesStart, int numNodesEnd, int numiterations, 
    int numAgents, int numColours, int finalNumConflicts, int numMissedNodes, double time)
{
    FILE* results = fopen(resultsFullName, "a");

    fprintf(results, "%d,%d,%d,%d,%d,%d,%d,%d,%.4f\n",
        benchmark,
        numNodesStart,
        numNodesEnd,
        numiterations,
        numAgents,
        numColours,
        finalNumConflicts,
        numMissedNodes,
        time
    );

    fclose(results);

    return 0;
}

int addBufferRowToResultsFile(int numRows) {
    FILE* results = fopen(resultsFullName, "a");

    for(int i = 0; i < numRows; i++) {
        fprintf(results, "\n");
    }

    fclose(results);

    return 0;
}

int addHeadersToResultsFile(char* optionalDescription) {
    FILE* results = fopen(resultsFullName, "a");

    if(optionalDescription != NULL) {
        fprintf(results, "%s\n", optionalDescription);
    }

    fprintf(results, "benchmark, starting nodes, final nodes, iterations, agents, colours, conflicts, missed nodes, time (s)\n");

    fclose(results);

    return 0;
}

int setFileNamePrepend(const char* name) {
    if(name == NULL) {
        printf("no name provided\n");
        return 1;
    }

    int nameLength = strlen(name);
    int conflictsLength = strlen(CONFLICTS_SAVE_FILE_NAME);
    int resultsLength = strlen(RESULTS_SAVE_FILE_NAME);

    if(nameLength > FULL_FILE_NAME_LENGTH - conflictsLength) {
        printf("provided name too long\n");
        return 1;
    }

    //create conflicts name
    memcpy(conflictsFullName, name, nameLength);
    memcpy(conflictsFullName + nameLength, CONFLICTS_SAVE_FILE_NAME, conflictsLength);

    //create results name
    memcpy(resultsFullName, name, nameLength);
    memcpy(resultsFullName + nameLength, RESULTS_SAVE_FILE_NAME, resultsLength);

    return 0;
}
