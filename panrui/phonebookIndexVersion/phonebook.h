#ifndef 	_PHONE_BOOK_
#define 	_PHONE_BOOK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PHONE_NAME_LENGTH 10
#define PHONE_NUM_LENGTH 12
#define PHONE_STRUCT_LENGTH ((PHONE_NAME_LENGTH)+(PHONE_NUM_LENGTH))

#define COMMAND_LEN_MAX 200
#define PATH_LEN_MAX 100
#define DEFAULT_PATH ".\\phonebook.txt"
#define BUFF_SIZE  ((PHONE_STRUCT_LENGTH)*4)

#define	LETTER_NUM 26

#define LOAD 	0
#define SAVE 	1
#define SAVETO	2
#define ADDNEW	3
#define QUIT 	4
#define SHOW    5
//addition
#define FIND	6



struct	Index
{
	int	 cur_p;
	bool IsIndirect[LETTER_NUM];
	long offset[LETTER_NUM];
};
struct phoneNum
{
	char name[PHONE_NAME_LENGTH];
	char num[PHONE_NUM_LENGTH];
};
struct Tools
{

	Index	 *	index;
	FILE	 *  fd;
	int			pn_size;
	phoneNum *	pn;
};

void InitIndex(Index * index,FILE * fd);
void InitIndexByRecurrence(Index * index,FILE * fd,int depth,long limit);
void destoryIndex(Index * index);
void UpdateIndex(Index * index,int c_offset);
Index * InitBuffer(Tools * tool,char *sign);
void ClearBuffer(Tools * tool);

void initTool(Tools * tool);
void addPhoneNum(Tools * tool,char * name,char *num);
void InsertToFile(Tools * tool,char * pn,long offset);

void destoryTool(Tools * tool);

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
