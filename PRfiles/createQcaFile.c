#include "createQcaFile.h"
#define cellSize 20;
#define gridSize 5*cellSize;

const char* changeableAreas[5] = {"[TYPE:QCADCell]", "[TYPE:QCADDesignObject]", "[TYPE:CELL_DOT]", "[TYPE:QCADLabel]", "[TYPE:QCADStretchyObject]"};
const char* finishedAreas[7] = {"[#TYPE:QCADDesignObject]","[#TYPE:CELL_DOT]", "[#TYPE:QCADLabel]", "[#TYPE:QCADLayer]", "[#TYPE:DESIGN]", "[#TYPE:QCADCell]",
"[#TYPE:QCADStretchyObject]"};
const char* fixedCells[2] = {"positiveFixed.qca", "negativeFixed.qca"};

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

void createQCAFile(FILE* qcaFile, QCAData * data, int totalofGates){
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

    if(tempQCAFile == NULL){
      perror("error while opening the temporary file  \n");
      exit(EXIT_FAILURE);
    }

    if(data[counter].gateType >= 2){

       // dx and dy already know the use area now they need to know where in the
       //grid the fixed cell is
      dx +=    data[counter].fixedX * cellSize ;
      dy +=    data[counter].fixedY * cellSize ;
      fixeddxdy[0] = dx;
      fixeddxdy[1] = dy;
      parseGatewithFixedCell(tempQCAFile, qcaFile, dxdy, fixeddxdy, data[counter].gateType);
    }
    else {
      //in this case the file has a fixed cell we need to modify it accordingly
      parseGatewithoutFixedCell( tempQCAFile, qcaFile, dxdy);
    }
    fclose(tempQCAFile);
  }
}

void parseGatewithoutFixedCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy){
  char line[100];
  int dotCounter, totalofDots;

  while(!feof(tempQCAFile)){
    //reading the temporary file and adapting it to the new qca design
    strcpy(line,  getFileLine(tempQCAFile));

    if(strcmp(line,changeableAreas[0]) == 0){
      //we are dealing with a cell
      fprintf(qcaFile, "%s\n", line);
      strcpy(line,  getFileLine(tempQCAFile));
      if(strcmp(line,changeableAreas[1]) == 0){
        //we are on the area of a QCADesignObject of a cell should work accordingly
        //to its pattern
        fprintf(qcaFile, "%s\n", line);

        //printing the design object area inside the new file
        printQCADesignObject(tempQCAFile,qcaFile, dxdy);
        fprintUnchanbleLines(tempQCAFile, qcaFile, 6);
        totalofDots = getTotalofDots(tempQCAFile,qcaFile, '=');
      }
      else{
          //if it's not we have an error inside the file we should stop.
          perror("an error occured while reading the file 1");
          exit(0);
      }
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
      printf("%s\n", line);
      if(strcmp(line, finishedAreas[5]) == 0){
        //cell was finished we can move on to the next cell or to close the file
        fprintf(qcaFile, "%s\n", line);
        continue;
      }
      else if ( strcmp(line, changeableAreas[3]) == 0){
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

          else {
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
  }
}

void printQCADesignObject(FILE* tempQCAFile,FILE* qcaFile, double* dxdy){

  char line[100];
  changeXYData (dxdy, qcaFile, tempQCAFile, '=');
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


void parseGatewithFixedCell(FILE* tempQCAFile, FILE* qcaFile, double* dxdy, double* fixeddxdy, int gateType){
  char line[100];
  int dotCounter, totalofDots;
  FILE* fixedGateFile;
  int foundfixed = 0;
  printf("%lf %lf \n", fixeddxdy[0], fixeddxdy[1]);
  int fixedFile = getFixedFile(gateType);

  strcpy(line,  getFileLine(tempQCAFile));

  if(strcmp(line,changeableAreas[0]) == 0){
    getXY();
  }
  else {
    perror("an error occured while reading the file 1");
    exit(0);
  }


}
