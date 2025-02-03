#ifndef SAVING
#define SAVING

//appends a new column to the data made up of the number of conflicts at row i
//i think it makes more sense to save them in columns, even if it is more complicated to code
int appendToResults(int* conflictArray, int numIterations);

//adds an empty column to the results file
int addBufferColumnToConflictsFile(int numColumns);

//saves micellaneous data about the colouring run to a csv file
int saveColouringData(int benchmark, int numNodesStart, int numNodesEnd, int numiterations, 
    int numAgents, int numColours, int finalNumConflicts, int numMissedNodes, double time);

//adds a newline character to the file
int addBufferRowToResultsFile(int numRows);

//adds column headers to the results file
//if you do not want the description, pass `NULL`
int addHeadersToResultsFile(char* optionalDescription);

#endif