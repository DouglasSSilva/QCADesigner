#include "createQcaFile.h"
#define cellSize 20;
#define gridSize 5*cellSize;

const char* changeableAreas[4] = {"[TYPE:QCADCell]", "[TYPE:QCADDesignObject]", "[TYPE:CELL_DOT]", "[TYPE:QCADLabel]"};
const char* finishedAreas[5] = {"[#TYPE:CELL_DOT]", "[#TYPE:QCADLabel]", "[#TYPE:QCADLayer]", "[#TYPE:DESIGN]", "[#TYPE:QCADCell]"};
const char* fixedCells[2] = {"positiveFixed.qca", "negativeFixed.qca"};

void getDataCreateFile(char* input, char* output){
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
  fclose (qcaFile);
}

void getUseData(FILE* useFile, FILE* qcaFile){
  QCAData* data;
  int totalofGates;
  fscanf(useFile,"Total of gates: %d\n", &totalofGates);
  data =(QCAData *) malloc(sizeof (QCAData) * totalofGates);
  getDatafromUseFile(useFile, data, totalofGates);
  //the data was gathered, we can close the useFile now and start the creation
  //of the qcaFile;
  fclose(useFile);
  free(data);
}
