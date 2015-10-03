#include "createQCAHelper.h"

void changeXYData (double *xyData, FILE* qcaFile, FILE* tempQCAFile, char delim){

  char line;
  double Axis = 0.0;
  int counter;
  for (counter = 0; counter < 2; counter++){
    //get char by char from line until the delim so we can put the new value
    //after it
    line = fgetc(tempQCAFile);
    fputc(line,qcaFile);
    while (line != delim){
      line = fgetc(tempQCAFile);
      fputc(line,qcaFile);
    }
    //updating with the new values;
    fscanf(tempQCAFile,"%lf",&Axis);
    Axis += xyData[counter];
    fprintf(qcaFile,"%lf\n",Axis);
    line = fgetc(tempQCAFile);
  }

}

void fprintUnchanbleLines(FILE* tempQCAFile, FILE* qcaFile, int totalofLines){
  char line[100];
  int counter;
  for(counter = 0; counter < totalofLines; counter++ ){
    fgets(line, sizeof line, tempQCAFile);
    fprintf(qcaFile, "%s", line);
  }
}

void getDatafromUseFile(FILE* useFile, QCAData* data, int totalofGates){
  int i;
  char line [100];
  char* fName;
  for(i = 0; i < totalofGates; i++){
    fgets(line, sizeof line, useFile);
    //getting the gate data and storing it inside the structure QCADAta for each
    //gate inside the design
    fscanf(useFile, "Gate: %d", &data[i].gateType);
    fgets(line, sizeof line, useFile);
    fgets(line, sizeof line, useFile);
    fscanf(useFile, "useX: %d\n", &data[i].useX);
    fscanf(useFile, "useY: %d\n", &data[i].useY);
    fscanf(useFile, "fixedX: %d\n", &data[i].fixedX);
    fscanf(useFile, "fixedY: %d\n", &data[i].fixedY);
    fgets(line, sizeof line, useFile);
    fscanf(useFile, "FileName: %s\n", line);
    //organizing the data so we have only the fileName we want;
    fName = strstr(line, " ");
    fName = strtok(fName, "\n");
    data[i].fileName = (char*) malloc( (sizeof (char)) * strlen(fName));
    strcpy(data[i].fileName, fName);
    memmove(data[i].fileName, data[i].fileName+1, strlen(data[i].fileName));

  }
}
void printQcaHeader(FILE* tempQCAFile, FILE* qcaFile){
  char line[100];
  int counter = 0;
  while(!feof(tempQCAFile)){
    if(counter > 34){
      break;
    }
    fgets(line, sizeof line, tempQCAFile);
    fprintf(qcaFile, "%s",line);
    counter++;
  }
}


char* getFileLine(FILE* tempQCAFile){
  char line[100];
  fgets(line, sizeof line, tempQCAFile);
  strcpy(line,  strtok(line, "\n"));
  return (char*) line;
}

int getTotalofDots(FILE* tempQCAFile, FILE* qcaFile, char delim){
  char line;
  int totalofDots;
  line = fgetc(tempQCAFile);
  fputc(line,qcaFile);
  while (line != delim){
    line = fgetc(tempQCAFile);
    fputc(line,qcaFile);
  }
  fscanf(tempQCAFile, "%d", &totalofDots);
  fprintf(qcaFile, "%d\n",totalofDots);
  line = fgetc(tempQCAFile);
  return totalofDots;
}


int getFixedFile(int gateType){
    if (gateType  == 2 || gateType == 5){
        return 0;
    }
    else{
      return 1;
    }
}

double* getXY(double *xyData, FILE* qcaFile, FILE* tempQCAFile, char delim){

  char line;
  double Axis[2] = {0.0, 0.0};
  int counter;
  for (counter = 0; counter < 2; counter++){
    //get char by char from line until the delim so we can put the new value
    //after it
    line = fgetc(tempQCAFile);
    fputc(line,qcaFile);
    while (line != delim){
      line = fgetc(tempQCAFile);
      fputc(line,qcaFile);
    }
    //updating with the new values;
    fscanf(tempQCAFile,"%lf",&Axis[counter]);
    Axis[counter] += xyData[counter];
    fprintf(qcaFile,"%lf\n",Axis[counter]);
    line = fgetc(tempQCAFile);
  }
  return Axis;
}
