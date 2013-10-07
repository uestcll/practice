#include "Huffman.h"

hTree * initHTreeMap()
{
	hTree * h_map = (hTree *)calloc(256,sizeof(hTree));
	if(h_map == NULL)
		return NULL;

	for(int i = 0;i<256;i++)
	{
		h_map[i].value = i;
		if(i!=255)
		h_map[i].next = &h_map[i+1];
		else 
		h_map[i].next = NULL;
		if(i!=0)
		h_map[i].parent = &h_map[i-1];
		else
		h_map[i].parent = NULL;
	}
	
	return h_map;

}

hTree * loadFile(hTree * h_map,char * path)
{
	FILE * fd = fopen(path,"rb");
	if(fd == NULL)
		return NULL;

	unsigned char code[32]={0};
	unsigned char bit = 0;
	
	if(counter(h_map,fd) == false )
		return NULL;
	
	hTree * h_tree = genHTree(h_map);
	
	genHFCode(h_tree,code,bit);

	fclose(fd);
	return h_tree;
}

bool counter(hTree * h_map,FILE * fd)
{
	unsigned char in = 0;
	fseek(fd,0,SEEK_END);

	unsigned int len = ftell(fd);
	fseek(fd,0,SEEK_SET);

	for(unsigned int i=0;i<len;i++)
	{
		in=fgetc(fd);
		h_map[in].count++;
	}
	return true;
}

hTree * genHTree(hTree * h_map)
{
	while(h_map->next != NULL)
	{
		MINTWO min = minTwo(h_map);

		hTree * ntree = (hTree *)calloc(1,sizeof(hTree));
		ntree->left = min.sec;
		ntree->right = min.fir;
		ntree->count = ntree->left->count+ntree->right->count;

		if(min.fir->next==min.sec)
		{
			ntree->parent = ntree->right->parent;
			ntree->next = ntree->left->next;
			
			if(ntree->right->parent!=NULL)
				ntree->right->parent->next = ntree;
			else h_map = ntree;
			
			if(ntree->left->next!=NULL)
				ntree->left->next->parent = ntree;
			
			ntree->right->parent = ntree;
			ntree->left->parent = ntree;
			ntree->right->next = NULL;
			ntree->left->next = NULL;
		}
		else if(min.sec->next==min.fir)
		{
			ntree->next = ntree->right->next;
			ntree->parent = ntree->left->parent;
			
			if(ntree->left->parent!=NULL)
				ntree->left->parent->next = ntree;
			else h_map = ntree;
			
			if(ntree->right->next !=NULL)
				ntree->right->next->parent = ntree;
			
			ntree->left->parent = ntree;
			ntree->right->parent = ntree;
			ntree->left->next = NULL;
			ntree->right->next = NULL;
		}
		else
		{
			ntree->next = ntree->right->next;
			ntree->parent = ntree->right->parent;
			
			if(ntree->right->parent!=NULL)
				ntree->right->parent->next = ntree;
			else h_map = ntree;
			
			if(ntree->right->next!=NULL)
				ntree->right->next->parent = ntree;
			ntree->right->parent = ntree;
			ntree->right->next = NULL;

			if(ntree->left->parent!=NULL)
				ntree->left->parent->next = ntree->left->next;
			else h_map = ntree->left->next;
			
			if(ntree->left->next !=NULL)
				ntree->left->next->parent = ntree->left->parent;
			
			ntree->left->parent = ntree;
			ntree->left->next = NULL;
		}
	}
	return h_map;
}
MINTWO minTwo(hTree * h_map)
{
	MINTWO min;
	hTree * step = h_map;
	min.fir = step;
	min.sec = step;
	
	while(step!= NULL)
	{
		if(min.fir->count > step->count )
			min.fir = step;
		step = step->next ;
	}
	step = h_map;
	
	if(min.fir==h_map)
	min.sec = h_map->next;
	
	while(step!= NULL)
	{
		if((min.sec->count > step->count )&& (min.fir!=step))
			min.sec = step;
		step = step->next;
	}
	
	return min;
}

void genHFCode(hTree * h_map,unsigned char * code,char bit)
{
	memcpy(h_map->hfCode,code,32);
	h_map->bit = bit;
	
	unsigned char codeTMP0[32]={0};
	unsigned char codeTMP1[32]={0};
	memcpy(codeTMP0,code,32);
	memcpy(codeTMP1,code,32);
	
	if( h_map->left!=NULL )
		genHFCode(h_map->left,shl(codeTMP0,0,bit),bit+1);
	if( h_map->right != NULL)
		genHFCode(h_map->right,shl(codeTMP1,1,bit),bit+1);

}
unsigned char *shl(unsigned char * code,unsigned char value,unsigned char bit)
{
	int i = 0;
	unsigned char tmp_last =value;
	unsigned char tmp_next =0;
	int ext_bit = bit;
	
	while(ext_bit>=0)
	{	
		tmp_next = code[31-i]&0x80;
		tmp_next>>=7;
		code[31-i]<<=1;
		code[31-i]^=tmp_last;
		i++;
		ext_bit-=8;
		tmp_last = tmp_next;
	}
	
	return code;
}

void	destoryHTreeMap(hTree * h_map,hTree * h_tree)
{
	if(h_map!=NULL)
	{
		for(int i=0;i<256;i++)
		{
			if(h_map[i].parent->left == &h_map[i]) h_map[i].parent->left = NULL;
			else h_map[i].parent->right = NULL;
		}
		free(h_map);
	}
	if(h_tree->left !=NULL )
		destoryHTreeMap(NULL,h_tree->left);
	if(h_tree->right != NULL)
		destoryHTreeMap(NULL,h_tree->right);

	free(h_tree);
}

void	saveHuffmanToFile(hTree * h_tree,char leftBit)
{
	FILE * fd = fopen(HUFFMAN_TREE_PATH,"wb");
	
	fwrite(&leftBit,1,1,fd);
	saveRecurrence(h_tree,fd);

	fclose(fd);
}
void	saveRecurrence(hTree * h_tree,FILE * fd)
{
	hTreeFile tmp;
	
	tmp.bit = h_tree->bit;
	tmp.value = h_tree->value;
	memcpy(tmp.hfCode,h_tree->hfCode,32);
	if(h_tree->left == NULL||h_tree->right == NULL)
		tmp.isLeave = 1;
	else 
		tmp.isLeave = 0;

	fwrite(&tmp,sizeof(hTreeFile),1,fd);

	if(h_tree->left != NULL)
			saveRecurrence(h_tree->left,fd);
	if(h_tree->right != NULL)
			saveRecurrence(h_tree->right,fd);		
}

hTree *	loadHuffmanFromFile(char * leftBit)
{
	FILE * fd = fopen(HUFFMAN_TREE_PATH,"rb");
	
	fread(leftBit,1,1,fd);

	hTree * h_Head = (hTree *)calloc(1,sizeof(hTree));
	loadRecurrence(h_Head,fd);
	
	fclose(fd);
	return h_Head;
}
void	loadRecurrence(hTree * &h_tree,FILE *fd)
{
	hTreeFile tmp;
	fread(&tmp,sizeof(hTreeFile),1,fd);
	
	h_tree = (hTree *)calloc(1,sizeof(hTree));
	h_tree->value = tmp.value;
	h_tree->bit = tmp.bit;
	memcpy(h_tree->hfCode,tmp.hfCode,32);
	
	if(tmp.isLeave)
		return ;
	else
	{
		loadRecurrence(h_tree->left,fd);
		loadRecurrence(h_tree->right,fd);
	}
}
void	destoryLoadTree(hTree * h_tree)
{
	if(h_tree->left!=NULL)
		destoryLoadTree(h_tree->left);
	if(h_tree->right!=NULL)
		destoryLoadTree(h_tree->right);
	free(h_tree);
}


void	Usage()
{
	printf("Usage:\n");
	printf("\t-c [filename] [compressed filename]\n");
	printf("\t-u [compressed filename] [filename]\n");
}

