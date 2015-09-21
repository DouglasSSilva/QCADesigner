#include "createQcaHelper.h"

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
