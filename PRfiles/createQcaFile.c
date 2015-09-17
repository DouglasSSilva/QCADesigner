#include "createQcaFile.h"
#define cellSize 20;
#define gridSize 5*cellSize;

const char* changeableAreas[4] = {"[TYPE:QCADCell]", "[TYPE:QCADDesignObject]", "[TYPE:CELL_DOT]", "[TYPE:QCADLabel]"};
const char* finishedAreas[5] = {"[#TYPE:CELL_DOT]", "[#TYPE:QCADLabel]", "[#TYPE:QCADLayer]", "[#TYPE:DESIGN]", "[#TYPE:QCADCell]"};
const char* fixedCells[2] = {"positiveFixed.qca", "negativeFixed.qca"};
void createQFile(char* input, char* output){
  FILE* useFile = fopen(input, "r");
  /*file with the data we want,takes from every qca file in the input and create
  a huge one to be loaded on qcaDesigner*/
  FILE* qcaFile = fopen(output, "w");
  char line[100];

  int i;
  for (i = 0; i< 3; i++){
    fgets(line, sizeof line, useFile);
  }

  getUseData(useFile, qcaFile);
  fclose(useFile);
  fclose (qcaFile);
}

void getUseData(FILE* useFile, FILE* qcaFile){
  int useX, useY, fixed;
  char line [100];
  char *gateType;
  char fileName[100];
  int counter;
  while (!feof(useFile)){
    fgets(line, sizeof line, useFile);
    if(strcmp(line,"end") == 0){
      break;
    }
    gateType = strtok(line, " - \n");
    for(counter = 0; counter < 2; counter ++){
        gateType = strtok (NULL, " - \n");
    }
    fgets(line, sizeof line, useFile);
    fscanf(useFile, "useX: %d\n", &useX);
    fscanf(useFile, "useY: %d\n", &useY);
    fscanf(useFile, "fixed: %d\n", &fixed);
    fgets(fileName, sizeof fileName, useFile);
    memmove(fileName+0,fileName+10,50);
    strcpy(fileName, strtok(fileName," "));
    fgets(line, sizeof line, useFile);
    readQCAFileBuildNewOne(useX, useY, fileName, qcaFile, gateType,fixed);
  }
 fprintf(qcaFile, "%s\n",finishedAreas[2]);
  fprintf(qcaFile, "%s\n",finishedAreas[3]);
}

void readQCAFileBuildNewOne(int useX, int useY, char* fileName,FILE* qcaFile, char* gateType, int fixed){

  int dx = useX * gridSize;
  int dy = useY * gridSize;
  // finding the file path;
  char path[100];
  strcpy(path,"gates/");
  strcat(path, (const char*)fileName);
  FILE* tempQCAFile = fopen(path, "r");
  if(tempQCAFile == NULL){
    printf("error: file not found %s \n", path);
    exit(1);
  }
  char line[100];
  int i;
  int position = ftell(qcaFile);
  if( position == 0 ){
    fprintUnchanbleLines(tempQCAFile, qcaFile, 35);
  }
  else {
    for (i = 0; i < 35; i++){
        fgets(line, sizeof line, tempQCAFile);
    }
  }
  //eliminando o cabeçalho do arquivo qca;
  changeQCADesignObject(dx, dy, tempQCAFile, qcaFile, gateType);
  fclose(tempQCAFile);
}

void changeQCADesignObject(int dx, int dy, FILE* tempQCAFile, FILE* qcaFile, char* gateType, int fixed){
  char line[100];
  while (!feof(tempQCAFile)){
      fgets(line, sizeof line, tempQCAFile);
      line[strlen(line) -1] = '\0';
      if(strcmp(line, changeableAreas[0]) == 0){
          fprintf(qcaFile, "%s\n", line);
      }
      else if (strcmp(line, changeableAreas[1]) == 0){
          changeQCADesignObjectArea(dx, dy, tempQCAFile, qcaFile, line);
      }
      else if (strcmp(line, changeableAreas[2]) == 0){
          fprintf(qcaFile, "%s\n", line);
          changeCellDotArea(dx, dy, tempQCAFile, qcaFile);
      }
      else if (strcmp(line, changeableAreas[3]) == 0){
          fprintf(qcaFile, "%s\n", line);
          changeLabelArea(dx, dy, tempQCAFile, qcaFile);
      }
      else if (strcmp(line, finishedAreas[2]) == 0){
        continue;
      }
      else if (strcmp(line, finishedAreas[3]) == 0){
        break;
      }
      else if (strcmp(line, finishedAreas[4]) == 0){
        fprintf(qcaFile, "%s\n", line);
      }
      else{
        fprintf(qcaFile, "%s\n", line);
      }
  }
}


void changeQCADesignObjectArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile,char* line, char* gateType, int fixed){

  double x = 0.0;
  double y = 0.0;
  fprintf(qcaFile, "%s\n", line);
  setNewObjectArea(tempQCAFile, qcaFile, x, y, dx, dy);
  fprintUnchanbleLines(tempQCAFile, qcaFile, 5);
  setNewObjectArea(tempQCAFile, qcaFile, x, y, dx, dy);
  fprintUnchanbleLines(tempQCAFile, qcaFile, 11);
}

void changeCellDotArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile){
  double x = 0.0;
  double y = 0.0;
  char line[100];
  setNewObjectArea(tempQCAFile, qcaFile, x, y, dx, dy);
  do{
    fgets(line, sizeof line, tempQCAFile);
    line[strlen(line) -1] = '\0';
    fprintf(qcaFile, "%s\n", line);
  }while(strcmp(line, finishedAreas[0]) != 0);

}

void changeLabelArea(int dx,int  dy,FILE* tempQCAFile,FILE* qcaFile){
  double x = 0.0;
  double y = 0.0;
  char line[100];
  do {
    fgets(line, sizeof line, tempQCAFile);
    line[strlen(line) -1] = '\0';
    fprintf(qcaFile, "%s\n", line);
  } while(strcmp(line,changeableAreas[1]) != 0);
  setNewObjectArea(tempQCAFile,qcaFile, x, y, dx, dy);
  fprintUnchanbleLines(tempQCAFile, qcaFile, 5);
  setNewObjectArea(tempQCAFile,qcaFile, x, y, dx, dy);
  do{
    fgets(line, sizeof line, tempQCAFile);
    line[strlen(line) -1] = '\0';
    fprintf(qcaFile, "%s\n", line);
  }while(strcmp(line, finishedAreas[1]) != 0);
}

void setNewObjectArea(FILE* tempQCAFile, FILE* qcaFile, double x, double y, int dx, int dy){
  findData(x, dx, qcaFile, tempQCAFile,'=');
  findData(y,dy,qcaFile, tempQCAFile,'=');
}

void findData (double axis, int dAxis, FILE* qcaFile, FILE* tempQCAFile, char delim){
  int i = 0;
  char data[100];
  data[i] = fgetc(tempQCAFile);
  fputc(data[i],qcaFile);
  while (data[i] != delim){
    data[i] = fgetc(tempQCAFile);
    fputc(data[i],qcaFile);
  }
  fscanf(tempQCAFile,"%lf",&axis);
  double value = axis +dAxis;
  fprintf(qcaFile,"%lf",value);
}

void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFile, int totalofLines){
  int i;
  char line[100];
  for (i = 0; i < totalofLines; i++){
      fgets(line, sizeof line, tempQCAFile);
      fprintf(qcaFile, "%s", line);
  }
}
