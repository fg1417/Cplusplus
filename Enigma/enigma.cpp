#include <iostream>
#include <fstream>
#include <vector>
#include "errors.h"
#include "class.h"

using namespace std;

int main(int argc, char* argv[]){
  if(argc < 3){
    for(int i = 0; i < argc; i++)
    cerr<<"usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?"<<endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  int error = NO_ERROR;
  Enigma enigma(argc-1);
  error = enigma.startOn(&(argv[1]));
  if(error != NO_ERROR)
    return error;
  error = enigma.encryptOrDecrypt();
  return error;
}
