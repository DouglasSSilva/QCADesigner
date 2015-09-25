#include "createQCAHelper.h"

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

void getDatafromUseFile(FILE* useFile, QCAData* data, int totalofGates){
  int i;
  char line [100];
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
    data[i].fileName = strstr(line, " ");
    data[i].fileName = strtok(data[i].fileName, "\n");
    memmove(data[i].fileName, data[i].fileName+1, strlen(data[i].fileName) -1);
  }
}
