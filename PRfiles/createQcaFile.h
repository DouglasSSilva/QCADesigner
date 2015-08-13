#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createQFile(char* input, char* output);
void getUseData(FILE* useFile, FILE* qcaFile);
void readQCAFileBuildNewOne(int useX, int useY, char* fileName,FILE* qcaFile);
void changeQCADesignObject(int dx, int dy, FILE* tempQCAFile, FILE* qcaFile);
void changeQCADesignObjectArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile,char* line);
void changeCellDotArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile);
void changeLabelArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile);
void setNewObjectArea(FILE* tempQCAFile, FILE* qcaFile, double x, double y, int dx, int dy);
void findData (double axis, int dAxis, FILE* qcaFile, FILE* tempQCAFile, char delim);
void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFile, int totalofLines);
