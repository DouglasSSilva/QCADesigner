#include "createQCAHelper.h"


void getDataCreateFile(char* input, char* output);
void getUseData(FILE* useFile, FILE* qcaFile);
void createQCAFile(FILE* qcaFile, QCAData * data, int totalofGates);
void printQCADesignObject(FILE* tempQCAFile,FILE* qcaFile, double* dxdy);
void printDotArea(FILE* tempQCAFile,FILE* qcaFile, double* dxdy);
void changeDesignObjectLabel(FILE* tempQCAFile, FILE* qcaFile, double* dxdy);
void parseGateNormalCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy);
void parseGateEspecialCell(int* foundfixed, int gateType, FILE* qcaFile, double*dxdy,  double* fixeddxdy, FILE* tempQCAFile);
void parseGate(FILE* tempQCAFile, FILE* qcaFile, double* dxdy, double* fixeddxdy, QCAData data);
void printFixedDotArea(FILE* fixedGateFile, FILE* tempQCAFile,FILE* qcaFile, double* dxdy);
void printFixedDataDesignObject(double *dxdy, FILE* fixedGateFile, FILE* qcaFile, FILE* tempQCAFile);
