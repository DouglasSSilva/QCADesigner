#include "usedata.h"
#include "createQcaFile.h"


int main(int argc, char* argv[]){

    convertFile(argv[1], argv[2]);
    createQFile(argv[2], argv[3]);

  return 0;
}
