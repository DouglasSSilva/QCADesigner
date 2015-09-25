#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QCAData{
    int useX, useY;
    int fixedX, fixedY;
    int gateType;
    char *fileName;
}QCAData;


void findData (double axis, int dAxis, FILE* qcaFile, FILE* tempQCAFile, char delim);
void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFiltae, int totalofLines);
void getDatafromUseFile(FILE* useFile, QCAData* data, int totalofGates);
