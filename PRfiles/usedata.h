#include <stdio.h>
#include <stdlib.h>


typedef struct qcaUseGate{

    int useX;
    int useY;
    int gateType;
    int gateOrientation;


}qcaUseGate;
int getTotalofGates(FILE* input);
void convertFile(char* input, char* output);
void readInput(FILE* input,int totalofGates, qcaUseGate* Gate);
void createUseFile(FILE* output, int totalofGates, qcaUseGate* Gate);
void printHeader(FILE* output,char* outputName);
int getFileOrientation(int orientation, int useX, int useY);
