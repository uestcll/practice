#include "phonebook.h"

void initTool(Tools * tool)
{
	tool->index = NULL;
	tool->fd = NULL;
	tool->pn = NULL;
	tool->pn_size = 0;

	tool->fd = fopen(DEFAULT_PATH,"r");
	InitIndex(tool->index,tool->fd);
	fclose(tool->fd);
}
void destoryTool(Tools * tool)
{
	if(tool->pn!=NULL)
		ClearBuffer(tool);
	if(tool->index !=NULL)
		destoryIndex(tool->index);

}

void InitIndex(Index * index , FILE * fd)
{
	fseek(fd,0,SEEK_END);
	long flen = ftell(fd);
	fseek(fd,0,SEEK_SET);
	InitIndexByRecurrence(index,fd,0,flen);
}
void destoryIndex(Index * index)
{
	for(int i = 0;i<25;i++)
	{
		if(index->IsIndirect[i])
			destoryIndex((Index *)(index->offset[i]));
	}
	free(index);
}
void InitIndexByRecurrence(Index * index,FILE * fd,int depth,long limit)
{
	index = (Index *)calloc(1,sizeof(Index));
	char pn[PHONE_STRUCT_LENGTH]= {0};
	char current = 'a';
	for(int i = 0;i<LETTER_NUM;i++)
	{
		long lenSingal = 0;
		index->offset[i] = ftell(fd);
		while(PHONE_STRUCT_LENGTH==fread(pn,PHONE_STRUCT_LENGTH,1,fd))
		{
			lenSingal += PHONE_STRUCT_LENGTH;
			
			if(limit == ftell(fd))
			{
				//处理后面的
				for(int j = i;j<LETTER_NUM;j++)
				{
					index->offset[j] = limit;		
				}
				return ;
			}
			
			if(pn[depth - 'a']!=current)
			{
				fseek(fd,-PHONE_STRUCT_LENGTH,SEEK_CUR);
				break;
			}
		}
		if(lenSingal>BUFF_SIZE)
		{
			long limit = ftell(fd);
			fseek(fd,index->offset[i],SEEK_SET);
			index->IsIndirect[i] = 1;
			InitIndexByRecurrence((Index *)(index->offset[i]),fd,depth+1,limit);
		}
		current++;
	}

}

void UpdateIndex(Index * index,int c_offset)
{
	Index * p = index;
	for(int i = p->cur_p+1;i<LETTER_NUM;i++)
	{
		if(p->IsIndirect[i] == false)
		{
			p->offset[i]+=c_offset;
		}
		else
		{
			Index * q = (Index *)(p->offset[i]);
			q->cur_p = 0;
			UpdateIndex(q,c_offset);
		}
	}
}
Index * InitBuffer(Tools * tool,char *sign)
{
	tool->fd = fopen(DEFAULT_PATH,"r");
	Index * p = tool->index;
	long next_off = LONG_MAX;
	if(p = NULL)
	{
		printf("init buffer before init Index");
		return NULL;
	}
	p->cur_p = (int )(sign - 'a');

	if(p->cur_p!=25)
		next_off = p->offset[p->cur_p+1];

	while(p->IsIndirect[p->cur_p]==1)
	{
		p = (Index *)p->offset[p->cur_p];
		p->cur_p = *(++sign)-'a';
		if(p->cur_p!=25)
			next_off = p->offset[p->cur_p+1];
	}

	if(next_off == LONG_MAX)
	{
		fseek(tool->fd,0,SEEK_END);
		next_off = ftell(tool->fd);
		fseek(tool->fd,0,SEEK_SET);
	}

	fseek(tool->fd,p->offset[p->cur_p],SEEK_SET);

	tool->pn_size = next_off - p->cur_p;
	tool->pn = (phoneNum *)malloc(tool->pn_size);

	fread(tool->fd,tool->pn_size,1,tool->fd);


	fclose(tool->fd);

	return p;

}
void ClearBuffer(Tools * tool)
{
	free(tool->pn);
	tool->pn_size = 0;
}

void addPhoneNum(Tools * tool,char * name , char * num)
{
	if((name == NULL) || (num == NULL))
	{
		printf("cannot add without name or num");
		return;
	}
	Index * p = InitBuffer(tool,name);

	int insertPlace = 0;
	for(;insertPlace < tool->pn_size/PHONE_STRUCT_LENGTH;insertPlace++)
	{
		if(memcmp(name,&(tool->pn[insertPlace]),PHONE_NAME_LENGTH)<0)
			break;
	}

	long insertOff = insertPlace*PHONE_STRUCT_LENGTH + p->offset[p->cur_p];
	phoneNum insertStruct;
	memcpy(insertStruct.name,name,PHONE_NAME_LENGTH);
	memcpy(insertStruct.num,num,PHONE_NUM_LENGTH);

	ClearBuffer(tool);
	
	InsertToFile(tool,(char *)&insertStruct,insertOff);
}
void InsertToFile(Tools * tool,char * pn,long offset)
{
	tool->fd = fopen(DEFAULT_PATH,"rw");

	phoneNum readBuf;
	phoneNum writeBuf;
	memcpy((char *)&writeBuf,pn,PHONE_STRUCT_LENGTH);

	fseek(tool->fd,0,SEEK_END);
	long fileEnd = ftell(tool->fd);

	fseek(tool->fd,offset,SEEK_SET);

	for(long curOff = offset;curOff<fileEnd+PHONE_STRUCT_LENGTH;curOff+=PHONE_STRUCT_LENGTH)
	{
		fread((char *)&readBuf,PHONE_STRUCT_LENGTH,1,tool->fd);
		fseek(tool->fd,-PHONE_STRUCT_LENGTH,SEEK_CUR);
		fwrite((char *)&writeBuf,PHONE_STRUCT_LENGTH,1,tool->fd);
	}

	fclose(tool->fd);
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
	
	tool->fd = fopen(DEFAULT_PATH,"r");

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH]={0};
	while(fread(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,tool->fd)==22)
	{
		fwrite(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,file);
	}

	fclose(tool->fd);
	fclose(file );
	return true;
}

void show(Tools * tool )
{
	tool->fd = fopen(DEFAULT_PATH,"r");

	char pn[PHONE_NAME_LENGTH+PHONE_NUM_LENGTH+1]={0};
	while(fread(pn,PHONE_NAME_LENGTH+PHONE_NUM_LENGTH,1,tool->fd)==22)
	{
		printf("%s\n",pn);
	}

	fclose(tool->fd);
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
	initTool(&tool);
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
	destoryTool(&tool);
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