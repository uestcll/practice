#ifndef LOAD_MANAGER 
#define LOAD_MANAGER
#include "BencodingStructDef.h"
#include "FunctionLib.h"

void mainLogic(char * path);
void loadFile(FILE * fd,dictionary *& info);
void query(dictionary * &info);
void deleteBTfile(dictionary * info);

#endif