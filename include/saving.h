#ifndef SAVING
#define SAVING

//appends a new column to the data made up of the number of conflicts at row i
//i think it makes more sense to save them in columns, even if it is more complicated to code
int appendToResults(int* conflictArray, int numIterations);

//adds an empty column to the results file
int addBufferColumnToResults(int numColumns);

#endif