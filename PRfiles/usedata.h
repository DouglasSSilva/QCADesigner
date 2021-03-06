#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
  A gate has some exclusively characterístics dependind on the gate,
  and, or have fixed cells, while majority and inverter do not have,
  all gates may or may not have input and output cells in their design.
*/

typedef struct qcaUseGate{

    int useX, useY;
    int gateType, gateOrientation;
    int fixedX, fixedY;

}qcaUseGate;

int getTotalofGates(FILE* input);
const char* convertFile(char* input);
void readInput(FILE* input,int totalofGates, qcaUseGate* Gate);
void createUseFile(FILE* output, int totalofGates, qcaUseGate* Gate);
void printHeader(FILE* output,char* outputName);
int getFileOrientation(int orientation, int useX, int useY);
