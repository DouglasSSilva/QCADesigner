#include <stdio.h>
#include <stdlib.h>

void createQFile(char* input, char* output);
void getUseData(FILE* useFile, FILE* qcaFile);
void readQCAFileBuildNewOne(int useX, int useY, char* fileName,FILE* qcaFile);
