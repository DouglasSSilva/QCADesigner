#include "usedata.h"
#include "createQcaFile.h"
const char* gateArray[6] = {"inverter", "majorityGate", "andUSE", "orUSE", "andNormal", "orNormal"};//vetor com todos as portas implementadas
const char* orientationArray[5] = {"westEast", "southNorth", "eastWest", "northSouth", "Normal"}; //orientação

const char* convertFile(char* input){
  FILE* inputFile; // .txt
  FILE* useFile; // .txt
  qcaUseGate* Gate;
  int totalofGates;
  char useFileName[200], qcaFileName[200];
  inputFile = fopen(input,"r");

  if (input == NULL){
    printf("file not found");
    exit(1);
  }

  //get the name of the files we are going to create;
  strcpy(useFileName,"files/");
  char fileName[100];
  fgets(fileName, sizeof fileName, inputFile);
  fileName[strlen(fileName) -1] = '\0';
  strcat(useFileName, (const char*)fileName);

  //get the qca file name setting in the exact folder to find it
  strcpy(qcaFileName,"files/");
  fgets(fileName, sizeof fileName, inputFile);
  fileName[strlen(fileName) -1] = '\0';
  strcat(qcaFileName, (const char*)fileName);

  //print the header so we identify the file
  useFile = fopen (useFileName,"w");
  totalofGates = getTotalofGates(inputFile);
  Gate = (qcaUseGate*) malloc(totalofGates*sizeof(qcaUseGate));
  printHeader(useFile, useFileName);
  readInput(inputFile, totalofGates, Gate);
  fclose(inputFile);

  createUseFile(useFile,totalofGates, Gate);

  fclose(useFile);
  free(Gate);

  getDataCreateFile(useFileName, qcaFileName);
  return qcaFileName;
}

int getTotalofGates(FILE* input){
    int totalofGates;
    fscanf(input, "%d \n", &totalofGates);
    return totalofGates;
}

void readInput(FILE* input,int totalofGates, qcaUseGate* Gate){
  int i;
  for(i = 0; i < totalofGates; i++){
    fscanf(input, "%d %d %d %d %d %d", &Gate[i].gateType, &Gate[i].gateOrientation, &Gate[i].useX, &Gate[i].useY,&Gate[i].fixedX, &Gate[i].fixedY);
  }
}

void createUseFile(FILE* output, int totalofGates, qcaUseGate* Gate){

  /*Create a file with the data from each gate,
   this file will be read so we know wich file to use while
   running the algorithm */
  int orientation;
  int i;
  int gateName = 0;
  fprintf(output, "Total of gates: %d\n", totalofGates);
  fprintf(output, "-----------------------------------------------------------------------\n");

  for (i = 0; i<totalofGates; i++){
    if(Gate[i].gateType < 2){
      gateName = Gate[i].gateType;
    }
    else{
      gateName = 1;

    }
    orientation = getFileOrientation(Gate[i].gateOrientation, Gate[i].useX, Gate[i].useY);
    fprintf(output, "Gate: %d %s\n", Gate[i].gateType, gateArray[Gate[i].gateType] );
    fprintf(output, "Gate Orientation: %s\n",  orientationArray[orientation]);
    fprintf(output, "useX: %d\n", Gate[i].useX);
    fprintf(output, "useY: %d\n", Gate[i].useY);
    fprintf(output, "fixedX: %d\n", Gate[i].fixedX);
    fprintf(output, "fixedY: %d\n", Gate[i].fixedY);
    fprintf(output, "FileName: %s%s.qca\n",gateArray[gateName],orientationArray[orientation]);
    fprintf(output, "-----------------------------------------------------------------------\n");
  }
}

int getFileOrientation(int orientation, int useX, int useY){

  if(orientation == 0){
    return (useY % 2 == 0) ? 0 : 2;
  }
  else if(orientation == 1){
    return (useX % 2 == 0) ? 1 : 3;
  }
  else{
    return 4;
  }
}



void printHeader(FILE* output,char* outputName){
  fprintf(output, "-------------------------------USEFile %s----------------------------\n",outputName);
  fprintf(output, "-----------------------------------------------------------------------\n");
  fprintf(output, "-----------------------------------------------------------------------\n");
}
