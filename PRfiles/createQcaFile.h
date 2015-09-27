#include "createQCAHelper.h"


void getDataCreateFile(char* input, char* output);
void getUseData(FILE* useFile, FILE* qcaFile);
void createQCAFile(FILE* qcaFile, QCAData * data, int totalofGates);
void printQCADesignObject(FILE* tempQCAFile,FILE* qcaFile, double* dxdy);
void printDotArea(FILE* tempQCAFile,FILE* qcaFile, double* dxdy);
void changeDesignObjectLabel(FILE* tempQCAFile, FILE* qcaFile, double* dxdy);
void parseGatewithoutFixedCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy);
void parseGatewithFixedCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy, double* fixeddxdy, int gateType);
