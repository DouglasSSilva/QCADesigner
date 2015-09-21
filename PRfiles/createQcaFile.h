#include "createQCAHelper.h"
void createQFile(char* input, char* output);
void getUseData(FILE* useFile, FILE* qcaFile);
void readQCAFileBuildNewOne(int useX, int useY, char* fileName,FILE* qcaFile, char* gateType, int fixed);
void changeQCADesignObject(int dx, int dy, FILE* tempQCAFile, FILE* qcaFile, int fixed);
void changeQCADesignObjectArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile,char* line);
void changeCellDotArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile);
void changeLabelArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile);
void setNewObjectArea(FILE* tempQCAFile, FILE* qcaFile, double x, double y, int dx, int dy);
