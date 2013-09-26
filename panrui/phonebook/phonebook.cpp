#include "phonebook.h"
void initHead(phoneNum * p_num,Tools * tool)
{
	initPhoneNum(p_num);
	tool->head = p_num;
	tool->last = p_num;
}

void initPhoneNum(phoneNum * p_num)
{
	if(p_num == NULL )
	{
		printf("struct phone hasn't allocated spaces before init\n");
		return ;
	}

	memset(p_num->name,0,PHONE_NAME_LENGTH);
	memset(p_num->num,0,PHONE_NUM_LENGTH);

	p_num->NextP = NULL;
}

void addPhoneNumToNext(Tools * tool,char * name,char *num)
{
	if(name == NULL || num == NULL || tool->last == NULL)
	{
		printf("infomation is not completed\n");
		return;
	}

	tool->last->NextP = (phoneNum *)malloc(sizeof( phoneNum));

	initPhoneNum(tool->last->NextP);
	memcpy(tool->last->NextP->name,name,PHONE_NAME_LENGTH);
	memcpy(tool->last->NextP->num,num,PHONE_NUM_LENGTH);

	tool->last = tool->last->NextP;
}

void destoryPhoneNum(Tools * tool)
{
	phoneNum * p_num = tool->head->NextP;

	while(p_num!=NULL)
	{
		free( tool->head);
		tool->head = p_num;
		p_num=p_num->NextP;
	}

	free(tool->head);
	free(tool);
}

bool load(const char * path,Tools * tool)
{
	FILE * file = fopen(path,"r");

	if(file == NULL)
	{
		printf("file is not exist or wrong path\n");
		return false;
	}

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	while(fread(pn,1,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,file)==22)
	{
		addPhoneNumToNext(tool,&pn[0],&pn[PHONE_NAME_LENGTH]);
		formatPN(tool->last);
	}

	fclose(file);
	return true;
}

bool save(char * path,Tools * tool)
{
	phoneNum * p_num = tool->head->NextP;
	FILE * file = fopen(path,"w+");

	if(file == NULL )
	{
		printf("save file error\n");
		return false ;
	}

	while(p_num != NULL)
	{
		char TMP[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH+1] = {0};
		fwrite(PN2str(p_num,TMP),1,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,file);
		p_num = p_num->NextP;
	}

	fclose(file );
	return true;
}

void show(Tools * tool )
{
	phoneNum * p_num = tool->head->NextP;

	while(p_num != NULL )
	{
		char TMP[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH+1] = {0};
		printf("%s\n",PN2str(p_num,TMP));
		p_num = p_num->NextP;
	}
}

void formatPN(phoneNum * p_num)
{
	bool flag = false;

	for(int i = 0;i<PHONE_NAME_LENGTH;i++)
	{
		if((p_num->name[i]<'A')||(p_num->name[i]>'Z'&&p_num->name[i]<'a')||(p_num->name[i]>'z'))
			flag = true;
		if(flag) p_num->name[i] = 0;
	}

	flag = false ;
	for(int i = 0 ;i<PHONE_NUM_LENGTH;i++)
	{
		if(p_num->num[i]<'0'||p_num->num[i]>'9')
			flag = true;
		if(flag) p_num->num[i] = 0;
	}

}

char * PN2str(phoneNum * p_num,char * output)
{
	memset(output,' ',PHONE_NAME_LENGTH+PHONE_NUM_LENGTH+1);
	output[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH] = 0;

	memcpy(output,p_num->name,strlen(p_num->name));
	memcpy(&output[PHONE_NAME_LENGTH],p_num->num,strlen(p_num->num));

	return output;
}

void mainLoop(Tools * tool)
{
	load(DEFAULT_PATH,tool);

	while(true)
	{
		printf("#");
		char command[COMMAND_LEN_MAX] = {0};

		if(scanf("%[^\n]", command) == 0)
		{
			fflush(stdin);
			continue;
		}

		fflush(stdin);

		if(!dispatchCMD(command,tool))
		{
			break;
		}
	}
}

bool dispatchCMD(char * command,Tools * tool)
{
	char path[PATH_LEN_MAX] = {0};
	char name[PHONE_NAME_LENGTH] = {0};
	char num[PHONE_NUM_LENGTH] = {0};

		switch(commandAnalysis(command))
		{
		case LOAD:
			getStr(&command[3],path,PATH_LEN_MAX);
			load(path,tool);
			return true;
		case SAVE:
			strcpy(path,DEFAULT_PATH);
			save(path,tool);
			return true;
		case SAVETO:
			getStr(&command[3],path,PATH_LEN_MAX);
			save(path,tool);
			return true;
		case ADDNEW:
			getStr(getStr(&command[3],name,PHONE_NAME_LENGTH),num,PHONE_NUM_LENGTH);
			if(strlen(name)>0&&strlen(num))
				addPhoneNumToNext(tool,name,num);
			return true;
		case SHOW:
			show(tool);
			return true;
		case QUIT:
			destoryPhoneNum(tool);
			return false;
		case FIND:
			doFind(command,tool);
			return true;
		default:
			return true;
		}	
}

int  commandAnalysis(char * command)
{
	if(memcmp(command,"-ld",3)==0)		return LOAD;
	if(memcmp(command,"-sa",3)==0)		return SAVETO;
	if(memcmp(command,"-se",3)==0)		return SAVE;
	if(memcmp(command,"-ad",3)==0)		return ADDNEW;
	if(memcmp(command,"-qt",3)==0) 		return QUIT;
	if(memcmp(command,"-ls",3)==0)		return SHOW;
	if(memcmp(command,"-fd",3)==0)		return FIND;
	Usage();
	return -1;
}
void Usage()
{
	printf("invalid command:\n");
	printf("Usage:\t-ld [path]\n");
	printf("\t-se \n");
	printf("\t-sa [path]\n");
	printf("\t-ad [username] [phonenumber]\n");
	printf("\t-ls\n");
}

char * getStr(char * sentence,char * buf,int length)
{
	char * pstart = find(sentence,' ',true);

	char * pend = find(pstart,' ',false);

	if(pend-pstart<length)
	{
		memcpy(buf,pstart,pend-pstart);
		buf[pend-pstart]=0;
	}
	else printf("too long to write in buf\n");
	return pend;
}
char * find(char * in,char aim,bool statu)
{
	char * tmp = in;
	if(statu)
	{
		while(*in==aim&&*in!=0)
		{
			in++;
		}
		return in;
	}
	else
	{
		while(*in!=aim&&*in!=0)
		{
			in++;
		}
		return in;	
	}
}

void doFind(char * command,Tools * tool)
{
	int len = PHONE_NAME_LENGTH>PHONE_NUM_LENGTH?PHONE_NAME_LENGTH:PHONE_NUM_LENGTH;
	char * searchBuf = (char *)calloc(len,sizeof(char));
	getStr(&command[3],searchBuf,len);

	phoneNum * p_num = tool->head->NextP;

	while(p_num!=NULL)
	{
		char TMP[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH+1] = {0};
		if((!strcmp(p_num->name,searchBuf))||(!strcmp(p_num->num,searchBuf)))
		{
			printf("%s\n",PN2str(p_num,TMP));	
		}

		p_num = p_num->NextP;
	}

	free(searchBuf);
}