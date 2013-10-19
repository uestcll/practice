#ifndef FUNCTION_LIB
#define FUNCTION_LIB
#include <stdio.h>
#include "BencodingStructDef.h"

void initDictionary(FILE *& fd,dictionary *& info);
void initData(FILE *& fd,item *& pi,list *& pl,dictionary *& pd,char * type);
void initInt(FILE *& fd,item *& pi);
void initString(FILE *& fd,item *& pi);
void initList(FILE *& fd,list *& pl);

void deleteInfo(dictionary * info);
void deleteList(list * pl);
void deleteItem(item * pi);

void find(char * aim,dictionary * info);
unsigned long getInterger(FILE *& fd);

#endif