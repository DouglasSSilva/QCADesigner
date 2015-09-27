#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QCAData{
    int useX, useY;
    int fixedX, fixedY;
    int gateType;
    char *fileName;
}QCAData;


void changeXYData (double *xyData, FILE* qcaFile, FILE* tempQCAFile, char delim);
void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFile, int totalofLines);
void getDatafromUseFile(FILE* useFile, QCAData* data, int totalofGates);
void printQcaHeader(FILE* tempQCAFile, FILE* qcaFile);
char* getFileLine(FILE* tempQCAFile);
int getTotalofDots(FILE* tempQCAFile, FILE* qcaFile, char delim);
int getFixedFile(int gateType);
void printonFixedDataArea(FILE* fixedGateFile, FILE* qcaFile, FILE* tempQCAFile, char delim);
double* getXY(double *xyData, FILE* qcaFile, FILE* tempQCAFile, char delim);
