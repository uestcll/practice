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

hTree * initHTreeMap();//生成256个对象的数组，然后将其链表依次链接为下一个,使用calloc;
hTree *	loadFile(hTree * h_map,char * path);//读入文件,调用counter,genXXX
bool	counter(hTree * h_map,FILE * fd);//统计出现频率
hTree *	genHTree(hTree * h_map);//调用minTwo
MINTWO	minTwo(hTree * h_map);
void	genHFCode(hTree * h_map,unsigned char * code ,char bit);
unsigned char *shl(unsigned char * code,unsigned char value,unsigned char bit);
void	destoryHTreeMap(hTree * h_map,hTree * h_tree);




#endif 