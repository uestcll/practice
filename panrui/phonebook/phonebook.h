#ifndef 	_PHONE_BOOK_
#define 	_PHONE_BOOK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHONE_NAME_LENGTH 10
#define PHONE_NUM_LENGTH 12

#define COMMAND_LEN_MAX 200
#define PATH_LEN_MAX 100
#define DEFAULT_PATH ".\\phonebook.txt"

#define LOAD 	0
#define SAVE 	1
#define SAVETO	2
#define ADDNEW	3
#define QUIT 	4
#define SHOW    5
//addition
#define FIND	6

struct phoneNum
{
	char name[PHONE_NAME_LENGTH];
	char num[PHONE_NUM_LENGTH];
	phoneNum *NextP;
};
struct Tools
{
	phoneNum * head;
	phoneNum * last;
};

void initHead(phoneNum * p_num,Tools * tool);
void initPhoneNum(phoneNum * p_num);
void addPhoneNumToNext(Tools * tool,char * name,char *num);
void destoryPhoneNum(Tools * tool);

bool load(const char * path,Tools * tool);
bool save(char * path,Tools * tool);

void show(Tools * tool);
void formatPN(phoneNum * p_num);
char * PN2str(phoneNum * p_num,char * output);

void mainLoop(Tools * tool);
int  commandAnalysis(char * command);
bool dispatchCMD(char * command,Tools * tool);
char * find(char * in,char aim,bool statu);
void Usage();
char * getStr(char * sentence,char * buf,int length);

//addition
void doFind(char * command,Tools * tool);
		
#endif
