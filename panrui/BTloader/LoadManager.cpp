#include "LoadManager.h"

void mainLogic(char * path)
{
	FILE *fd =fopen(path,"rb");
	if(fd == NULL)
	{
		printf("error happens while opening file");
		return ;
	}
	dictionary * info = NULL;

	loadFile(fd,info);

	fclose(fd);
	query(info);
}

void loadFile(FILE *fd,dictionary * info)
{
	fgetc(fd);
	initDictionary(fd,info);
}

void query(dictionary * &info)
{
	
}