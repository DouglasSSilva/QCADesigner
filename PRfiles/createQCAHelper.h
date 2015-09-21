#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void findData (double axis, int dAxis, FILE* qcaFile, FILE* tempQCAFile, char delim);
void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFile, int totalofLines);
