#include "createQcaFile.h"
#define cellSize= 20;
#define gridSize= 5*cellsize;

void createQFile(char* input, char* output){
  FILE* useFile = fopen(input, "r");
  FILE* qcaFile = fopen(output, "w");
  if(useFile == NULL){
    printf ("the file was not found");
    exit(0);
  }
  char line[100];
  int i ;
  for (i = 0; i< 3; i++){
    fgets(line, sizeof line, useFile);
    printf("%s", line);
  }

}

void getUseData(FILE* useFile, FILE* qcaFile){
  int useX, useY;
  char fileName[50];
  while (!feof(useFile)){
    fgets(line, sizeof line, useFile);
    fgets(line, sizeof line, useFile);
    fscanf(useFile, "%d", useX);
    fscanf(useFile, "%d", useY);
    fscanf(useFile, "%s", fileName);
    fgets(fileName, sizeof fileName, useFile);
    readQCAFileBuildNewOne(useX, useY, fileName, qcaFile);
  }
}

void readQCAFileBuildNewOne(int useY, int useY, char* fileName,FILE* qcaFile){

  int dx = useX * gridSize;
  int dy = useY * gridSize;
  File* tempQCAFile = fopen (fileName, "r");
  char line[100];


}
