#include "createQcaFile.h"
#define cellSize 20;
#define gridSize 5*cellSize;

const char* changeableAreas[5] = {"[TYPE:QCADCell]", "[TYPE:QCADDesignObject]", "[TYPE:CELL_DOT]", "[TYPE:QCADLabel]", "[TYPE:QCADStretchyObject]"};
const char* finishedAreas[7] = {"[#TYPE:QCADDesignObject]","[#TYPE:CELL_DOT]", "[#TYPE:QCADLabel]", "[#TYPE:QCADLayer]", "[#TYPE:DESIGN]", "[#TYPE:QCADCell]",
"[#TYPE:QCADStretchyObject]"};
const char* fixedCells[2] = {"gates/positiveFixed.qca", "gates/negativeFixed.qca"};

void getDataCreateFile(char* input, char* output){
  FILE* useFile = fopen(input, "r");
  if(useFile == NULL){
    perror("error while opening the file \n");
    exit(EXIT_FAILURE);
  }
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
  createQCAFile(qcaFile, data, totalofGates);
  fclose(useFile);
  free(data);
  fprintf(qcaFile, "%s\n",finishedAreas[3] );
  fprintf(qcaFile, "%s\n",finishedAreas[4] );
  //fclose(qcaFile);
}

void createQCAFile(FILE* qcaFile, QCAData *data, int totalofGates){
  int counter;
  char fname[100];
  double dx = 0.0;
  double dy = 0.0;
  double dxdy[2] = {0.0 ,0.0}; //has the new x y positions of the gate
  double fixeddxdy[2] = {0.0, 0.0}; //has the new x y positions of a fixed cell
  FILE* tempQCAFile;
  tempQCAFile = fopen("gates/header.qca", "r");

  if(tempQCAFile == NULL){
    perror("error while opening the header file \n");
    exit(EXIT_FAILURE);
  }
  printQcaHeader(tempQCAFile, qcaFile);

  for (counter = 0; counter < totalofGates; counter++){

    strcpy(fname, "gates/");
    strcat(fname, data[counter].fileName);
    tempQCAFile = fopen(fname, "r");

    dx = data[counter].useX * gridSize;
    dy = data[counter].useY * gridSize;
    dxdy[0] = dx;
    dxdy[1] = dy;

    if(data[counter].fixedX >= 0 && data[counter].fixedY >= 0){
      dx +=    data[counter].fixedX * cellSize;
      dx += cellSize;
      dy +=    data[counter].fixedY * cellSize ;
      dy += cellSize;
      fixeddxdy[0] = dx;
      fixeddxdy[1] = dy;
    }



    if(tempQCAFile == NULL){
      perror("error while opening the temporary file  \n");
      exit(EXIT_FAILURE);
    }

    parseGate(tempQCAFile,  qcaFile, dxdy, fixeddxdy, data[counter]);
    fclose(tempQCAFile);
  }
}


void parseGate(FILE* tempQCAFile, FILE* qcaFile, double* dxdy, double* fixeddxdy, QCAData data){

  char line[100];
  double *xyFixedCheck;
  int foundfixed = 0;

  while(!feof(tempQCAFile)){
    strcpy(line,  getFileLine(tempQCAFile));

    if(strcmp(line,changeableAreas[0]) == 0){
      fprintf(qcaFile, "%s\n", line);
      strcpy(line,  getFileLine(tempQCAFile));

      if(strcmp(line,changeableAreas[1]) == 0){

        fprintf(qcaFile, "%s\n", line);
        xyFixedCheck = getXY(dxdy, qcaFile, tempQCAFile, '=');

        if(data.gateType >= 2 && foundfixed == 0 && xyFixedCheck[0] == fixeddxdy[0] && xyFixedCheck[1] == fixeddxdy[1]){

          parseGateEspecialCell(&foundfixed, data.gateType, qcaFile, dxdy, fixeddxdy, tempQCAFile);

        }

        else{

          parseGateNormalCell(tempQCAFile, qcaFile, dxdy);

        }
      }
    }
  }
}


void parseGateEspecialCell(int* foundfixed, int gateType, FILE* qcaFile, double*dxdy,  double* fixeddxdy, FILE* tempQCAFile){

  FILE* fixedGateFile;
  char line[100];
  int dotCounter, totalofDots;
  int fixedFile = 0; // getFixedFile(gateType);
  *foundfixed = 1;

  //we have a fixed cell;
  fixedFile =  getFixedFile(gateType);//getting wich fixedFile we should use for the cell
  fixedGateFile = fopen(fixedCells[fixedFile], "r");
  if(fixedGateFile == NULL){
    perror("error while opening the file \n");
    exit(EXIT_FAILURE);
  }

  strcpy(line,  getFileLine(tempQCAFile));
  fprintf(qcaFile, "%s\n", line);
  printFixedDataDesignObject(dxdy, fixedGateFile, qcaFile, tempQCAFile);
  totalofDots = getTotalofDots(tempQCAFile,qcaFile, '=');

  for(dotCounter = 0; dotCounter < totalofDots; dotCounter++){

    strcpy(line,  getFileLine(tempQCAFile));
    if(strcmp(line,changeableAreas[2]) == 0){

      fprintf(qcaFile, "%s\n", line);
      printFixedDotArea(fixedGateFile, tempQCAFile, qcaFile, dxdy);

    }

  }

  strcpy(line,  getFileLine(tempQCAFile));
  fprintf(qcaFile, "%s\n", line);
  fclose(fixedGateFile);

}

void printQCADesignObject(FILE* tempQCAFile,FILE* qcaFile, double* dxdy){

  char line[100];
  fprintUnchanbleLines(tempQCAFile, qcaFile, 4);
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  strcpy(line,  getFileLine(tempQCAFile));
  while(strcmp(line, finishedAreas[0]) != 0){
    fprintf(qcaFile, "%s\n", line);
    strcpy(line,  getFileLine(tempQCAFile));
  }
  fprintf(qcaFile, "%s\n", line);
}

void printDotArea(FILE* tempQCAFile,FILE* qcaFile, double* dxdy){
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 5);
}

void changeDesignObjectLabel(FILE* tempQCAFile, FILE* qcaFile, double* dxdy){
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 4);
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 3);
}


void printFixedDataDesignObject(double *dxdy, FILE* fixedGateFile, FILE* qcaFile, FILE* tempQCAFile){

  int counter;
  for(counter = 0; counter < 3; counter++){

    //the next 3 lines has important data related to fixed cells:
    //clr.red, clr.green e clr.blue
    printonFixedDataArea(fixedGateFile, qcaFile, tempQCAFile, '=');

  }
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 8);
  printonFixedDataArea(fixedGateFile, qcaFile, tempQCAFile, '=');

}


void printonFixedDataArea(FILE* fixedGateFile, FILE* qcaFile, FILE* tempQCAFile, char delim){

  char line;
  char value[50];

  line = fgetc(tempQCAFile);
  line = fgetc(fixedGateFile);

  fputc(line,qcaFile);
  while (line != delim){
    line = fgetc(tempQCAFile);
    line = fgetc(fixedGateFile);
    fputc(line,qcaFile);
  }
  fgets(value, sizeof value, tempQCAFile);
  fgets(value, sizeof value, fixedGateFile);
  //the value from the fixed file is the one to be printed in the qca file
  fprintf(qcaFile,"%s",value);


}

void printFixedDotArea(FILE* fixedGateFile, FILE* tempQCAFile,FILE* qcaFile, double* dxdy){
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 1);
  printonFixedDataArea(fixedGateFile, qcaFile, tempQCAFile, '=');
  fprintUnchanbleLines(tempQCAFile, qcaFile, 3);
}


void parseGateNormalCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy){

  char line[100];
  int dotCounter, totalofDots;

  //it's not a fixed cell we can run the file normally
   printQCADesignObject(tempQCAFile,qcaFile, dxdy);
   fprintUnchanbleLines(tempQCAFile, qcaFile, 6);
   totalofDots = getTotalofDots(tempQCAFile,qcaFile, '=');
   //with the total of dots in hand we work on printing the dots data
   for(dotCounter = 0; dotCounter < totalofDots; dotCounter ++){
     strcpy(line,  getFileLine(tempQCAFile));
     if(strcmp(line,changeableAreas[2]) == 0){
       fprintf(qcaFile, "%s\n", line);
       printDotArea(tempQCAFile, qcaFile,  dxdy);
     }

     else{
         perror("an error occured while reading the file 2");
         exit(0);
     }
   }
   strcpy(line,  getFileLine(tempQCAFile));
   if(strcmp(line, finishedAreas[5]) == 0){
     //cell was finished we can move on to the next cell or to close the file
     fprintf(qcaFile, "%s\n", line);
   }
   else if (strcmp(line, changeableAreas[3]) == 0){
     //this cell has a label which need to be inside the design
     fprintf(qcaFile, "%s\n", line);
     strcpy(line,  getFileLine(tempQCAFile));

     if(strcmp(line, changeableAreas[4]) == 0){
       //it is a stretchy object needs to be shown in file
       fprintf(qcaFile, "%s\n", line);
       strcpy(line,  getFileLine(tempQCAFile));

       if(strcmp(line, changeableAreas[1]) == 0){
         //we change the design object aspects and insert into file here
         fprintf(qcaFile, "%s\n", line);
         changeDesignObjectLabel(tempQCAFile, qcaFile, dxdy);
         //end printing the [#TYPE:QCADesignObject]
       }

       else{
         perror("an error occured while reading the file 5");
         exit(0);
       }

       strcpy(line,  getFileLine(tempQCAFile));
       while(strcmp(line, finishedAreas[5]) != 0){
         // until the cell is finished
         fprintf(qcaFile, "%s\n", line);
         strcpy(line,  getFileLine(tempQCAFile));
       }
       fprintf(qcaFile, "%s\n", line);

     }
     else {
       perror("an error occured while reading the file 4");
       exit(0);
     }
   }
   else {
     perror("an error occured while reading the file 3");
     exit(0);
   }
}
