#ifndef		_HUFFMAN_
#define		_HUFFMAN_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct hTree
{
	hTree * parent;
	hTree * next;
	hTree * left;
	hTree * right;
	
	unsigned char	value;
	unsigned char	bit;
	int				count;
	unsigned char	hfCode[32];

};

struct MINTWO
{
	hTree * fir;
	hTree * sec;
};

hTree * initHTreeMap();//����256����������飬Ȼ����������������Ϊ��һ��,ʹ��calloc;
hTree *	loadFile(hTree * h_map,char * path);//�����ļ�,����counter,genXXX
bool	counter(hTree * h_map,FILE * fd);//ͳ�Ƴ���Ƶ��
hTree *	genHTree(hTree * h_map);//����minTwo
MINTWO	minTwo(hTree * h_map);
void	genHFCode(hTree * h_map,unsigned char * code ,char bit);
unsigned char *shl(unsigned char * code,unsigned char value,unsigned char bit);
void	destoryHTreeMap(hTree * h_map,hTree * h_tree);




#endif 