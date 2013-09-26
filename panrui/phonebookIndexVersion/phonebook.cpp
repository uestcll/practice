#include "phonebook.h"
void initTool(Tools * tool)
{
	tool->index = (Index *)calloc(1,sizeof(Index));
	tool->cur_index = -1;
	
	tool->deffd = NULL;
	
	tool->pn_size = 0;
	tool->pn = NULL;
	InitIndex(tool);
}

void InitIndex(Tools * tool)
{
	tool->deffd = fopen(DEFAULT_PATH,"r");
	
	if(tool->deffd == NULL)
	{
		printf("No default file\n");
		return ;
	}	

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	while(fread(pn,1,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,tool->deffd)==22)
	{
		if(tool->index->offset[pn[0]-'a'] == 0)
			tool->index->offset[pn[0]-'a'] == ftell(tool->deffd)-PHONE_NAME_LENGTH-PHONE_NUM_LENGTH;
	}


	fclose(tool->deffd);
	tool->deffd = NULL;
}
void UpdateIndex(Tools * tool,int c_offset)
{
	for(int i = tool->cur_index;i<LETTER_NUM;i++)
	{
		tool->index->offset[i]+=c_offset;
	}
}
void InitBuffer(Tools * tool,char sign)
{
	tool->deffd = fopen(DEFAULT_PATH,"r");

	if(sign == 'z')
	{
		fseek(tool->deffd,0,SEEK_END);
		tool->pn_size = ftell(tool->deffd)-tool->index->offset[sign-'a'];
		fseek(tool->deffd,0,SEEK_SET);
	}
	else
	{
		tool->pn_size = tool->index->offset[sign-'a']-tool->index->offset[sign-'a'+1];
	}

	if(tool->pn_size == 0)
		{
			fclose(tool->deffd);
			return ;
		}
	tool->pn = (phoneNum *)calloc(tool->pn_size/(PHONE_NAME_LENGTH+PHONE_NUM_LENGTH),sizeof(phoneNum));

	fseek(tool->deffd,tool->index->offset[sign-'a'],SEEK_SET);
	for(int i = 0 ; i< tool->pn_size/(PHONE_NAME_LENGTH+PHONE_NUM_LENGTH);i++)
	{
		fread((char *)&(tool->pn[i]),sizeof(phoneNum),1,tool->deffd);
	}

	tool->cur_index = sign-'a';

	fclose(tool->deffd);
	tool->deffd = NULL;

}
void ClearBuffer(Tools * tool)
{
	free(tool->pn);
	tool->pn = NULL;
	tool->pn_size = 0;
	tool->cur_index =-1;
}

void addPhoneNum(Tools * tool,char * name,char *num)
{
	if(name == NULL || num == NULL )
	{
		printf("infomation is not completed\n");
		return;
	}
	InitBuffer(tool,name[0]);

	int i = 0;
	for(;i<tool->pn_size/(PHONE_NAME_LENGTH+PHONE_NUM_LENGTH;i++)
	{
		if(strcmp((char *)&(tool->pn[i]),name)<0)
			break;
	}
	
	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	memcpy(pn,name,PHONE_NAME_LENGTH);
	memcpy(&pn[PHONE_NAME_LENGTH],num,PHONE_NUM_LENGTH);
	InsertToFile(tool,pn,(i+1)*PHONE_NAME_LENGTH+PHONE_NUM_LENGTH);
	ClearBuffer(tool);

	UpdateIndex(tool,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH);
}
void InsertToFile(Tools * tool,char * pn,int offset)
{
	tool->deffd = fopen(DEFAULT_PATH_CP,"w");
	FILE * file = fopen(DEFAULT_PATH,"r");
	long long int len = offset+tool->index->offset[tool->cur_index];

	char buffer[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH];
	long long int readLen = 0;
	


	fclose(file);
	fclose(tool->deffd);
	
}

void destoryTool(Tools * tool)
{
	if(tool->pn!=NULL)
	ClearBuffer(tool);
	free(tool->index);
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
		addPhoneNum(tool,&pn[0],&pn[PHONE_NAME_LENGTH]);
	}

	fclose(file);
	return true;
}

bool save(char * path,Tools * tool)
{
	FILE * file = fopen(path,"w+");

	if(file == NULL )
	{
		printf("save file error\n");
		return false ;
	}
	
	tool->deffd = fopen(DEFAULT_PATH,"r");

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	while(fread(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,tool->deffd)==22)
	{
		fwrite(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,file);
	}

	fclose(tool->deffd);
	fclose(file );
	return true;
}

void show(Tools * tool )
{
	tool->deffd = fopen(DEFAULT_PATH,"r");

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	while(fread(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,tool->deffd)==22)
	{
		printf("%s\n",pn);
	}

	fclose(tool->deffd);
}
/*
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
*/
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
				addPhoneNum(tool,name,num);
			return true;
		case SHOW:
			show(tool);
			return true;
		case QUIT:
			destoryTool(tool);
			return false;
		//case FIND:
		//	doFind(command,tool);
		//	return true;
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
//	if(memcmp(command,"-fd",3)==0)		return FIND;
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
/*
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
*/