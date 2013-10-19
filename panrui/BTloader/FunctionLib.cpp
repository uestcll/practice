#include "FunctionLib.h"
#include <stdlib.h>


void initDictionary(FILE * &fd,dictionary *& info)
{
	info = (dictionary *)calloc(1,sizeof(dictionary));
	initData(fd,info->fir,info->firl,info->fird,&(info->firType));
	initData(fd,info->sec,info->secl,info->secd,&(info->secType));
	
	char tmp = fgetc(fd);

	if(tmp == 'e')
		return ;
	else
	{
		fseek(fd,-1,SEEK_CUR);
		initDictionary(fd,info->next);
	}
}

void initData(FILE * &fd,item *& pi,list *& pl,dictionary *& pd,char * type)
{
	char tmp_type = fgetc(fd);
	switch(tmp_type)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		*type = ITEM;
		fseek(fd,-1,SEEK_CUR);
		initString(fd,pi);
		break;
	case 'i':
		*type = ITEM;
		initInt(fd,pi);
		break;
	case 'l':
		*type = LIST;
		initList(fd,pl);
		break;
	case 'd':
		*type = DICTIONARY;
		initDictionary(fd,pd);
		break;
	default:
		printf("error happens\n");
		break;
	}
	return ;
}

void initInt(FILE *&fd,item *& pi)
{
	pi = (item *)calloc(1,sizeof(item ));
	pi->itemType = INTERGER;
	pi->data = (char *)calloc(1,sizeof(unsigned long ));
	*(unsigned long *)(pi->data) = getInterger(fd);

}

void initString(FILE *&fd,item *& pi)
{
	pi = (item *)calloc(1,sizeof(item ));
	pi->itemType = STRING;
	pi->len = getInterger(fd);
	pi->data = (char *)calloc(pi->len+1,sizeof(char ));

	fread(pi->data,1,pi->len,fd);
}

void initList(FILE *& fd,list *& pl)
{
	pl = (list *)calloc(1,sizeof(list ));
	initData(fd,pl->pitem,pl->plist,pl->pdic,&(pl->dataType));

	char tmp = fgetc(fd);
	if(tmp == 'e')
		return ;
	else
	{
		fseek(fd,-1,SEEK_CUR);
		initList(fd,pl->next);
	}
}

void deleteInfo(dictionary * info)
{
	switch(info->firType)
	{
	case ITEM:
		deleteItem(info->fir);
		break;
	case LIST:
		deleteList(info->firl);
		break;
	case DICTIONARY:
		deleteInfo(info->fird);
		break;
	default:
		printf("deleting error\n");
	}
	switch(info->secType)
	{
	case ITEM:
		deleteItem(info->sec);
		break;
	case LIST:
		deleteList(info->secl);
		break;
	case DICTIONARY:
		deleteInfo(info->secd);
		break;
	default:
		printf("deleting error\n");
	}
	if(info->next!=NULL)
		deleteInfo(info->next);
	delete info;
}

void deleteList(list * pl)
{
	switch(pl->dataType)
	{
	case ITEM:
		deleteItem(pl->pitem);
		break;
	case LIST:
		deleteList(pl->plist);
		break;
	case DICTIONARY:
		deleteInfo(pl->pdic);
		break;
	default:
		printf("deleting error\n");
	}
	if(pl->next!=NULL)
		deleteList(pl->next);
	delete pl;
}

void deleteItem(item * pi)
{
	delete pi->data;
	delete pi;
}

unsigned long getInterger(FILE *&fd)
{
	unsigned long retValue = 0;
	unsigned long weight = 100000000;
	char CurNum = 0;
	int  step = 9;
	while(true)
	{
		CurNum = fgetc(fd);
		if(CurNum >'9'||CurNum<'0')
			break;
		retValue += weight * (CurNum - '0');
		weight /= 10;
		step --;
		if(step == -1)
		{
			retValue *= 10;
			retValue += CurNum - '0';
			step = 0;

		}
	}

	while(step--)
	{
		retValue /=10;
	}
	
	return retValue;
}