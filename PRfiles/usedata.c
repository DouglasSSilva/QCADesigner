#include "usedata.h"
const char* gateArray[2] = {"inverter", "majorityGate"};//vetor com todos as portas implementadas
const char* orientationArray[4] = {"westEast", "southNorth", "eastWest", "northSouth"}; //orientação

void convertFile(char* input, char* output){
  FILE* inputFile; // .txt
  FILE* useFile; // .txt
  qcaUseGate* Gate;
  int totalofGates;
  inputFile = fopen(input,"r");
  if (input == NULL){
    printf("file not found");
    exit(1);
  }
  useFile = fopen (output,"w");
  totalofGates = getTotalofGates(inputFile);
  Gate = (qcaUseGate*) malloc(totalofGates*sizeof(qcaUseGate));
  printHeader(useFile, output);
  readInput(inputFile, totalofGates, Gate);
  fclose(inputFile);
  createUseFile(useFile,totalofGates, Gate);
  fclose(useFile);
  free(Gate);
}

int getTotalofGates(FILE* input){
    int totalofGates;
    fscanf(input, "%d \n", &totalofGates);
    return totalofGates;
}

void readInput(FILE* input,int totalofGates, qcaUseGate* Gate){
  int i;
  for(i = 0; i < totalofGates; i++){
    fscanf(input, "%d %d %d %d \n", &Gate[i].useX, &Gate[i].useY, &Gate[i].gateType, &Gate[i].gateOrientation);
  }
}

void createUseFile(FILE* output, int totalofGates, qcaUseGate* Gate){
  int orientation;
  int i;
  for (i = 0; i<totalofGates; i++){
    orientation = getFileOrientation(Gate[i].gateOrientation, Gate[i].useX, Gate[i].useY);
    fprintf(output, "Gate: %s \n", gateArray[Gate[i].gateType]);
    fprintf(output, "Gate Orientation: %s \n",  orientationArray[orientation]);
    fprintf(output, "useX: %d \n", Gate[i].useX);
    fprintf(output, "useY: %d \n", Gate[i].useY);
    fprintf(output, "FileName: %s_%s.qca \n",gateArray[Gate[i].gateType],orientationArray[orientation]);
    fprintf(output, "-----------------------------------------------------------------------\n");
  }
}

int getFileOrientation(int orientation, int useX, int useY){

  if(useX % 2 == 0) {//USEX par
      if (useY % 2 == 0){//USEY par
        return (orientation == 0) ? 0 : 1;
      }
      else {//USEY impar
        return (orientation == 0) ? 0 : 3;
      }
    }
  else{//USEX impar
    if (useY % 2 == 0){//USEY par
      return (orientation == 0) ? 2 : 1;
    }
    else {//USEY impar
      return (orientation == 0) ? 2 : 3;
    }
  }

}



void printHeader(FILE* output,char* outputName){
  fprintf(output, "-------------------------------USEFile %s----------------------------\n",outputName);
  fprintf(output, "-----------------------------------------------------------------------\n");
  fprintf(output, "-----------------------------------------------------------------------\n");
}
