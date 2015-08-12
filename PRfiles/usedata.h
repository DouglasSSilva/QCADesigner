#include <stdio.h>
#include <stdlib.h>

const char* gateArray[2] = {"inverter", "majorityGate"};//vetor com todos as portas implementadas
const char* orientationArray[4] = {"westEast", "southNorth", "eastWest", "northSouth"}; //orientação
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
