#ifndef GEN_HUFF_TREE
#define GEN_HUFF_TREE

#include "TreeItem.h"
#include "SetOfTree.h"
#include "MapOfTree.h"
#include "WordFrequency.h"


class GenerateHuffmanTree
{
private:
	GenerateHuffmanTree(GenerateHuffmanTree &);
	const GenerateHuffmanTree & operator = (GenerateHuffmanTree &);

	TreeItem * m_tree;
	SetOfTree * m_set;
	MapOfTree * m_map;
	WordFrequency * m_wf;
	string		str;	
	bool		constructionType;


	void genHFCode(TreeItem * p_tree,TreeItem * m_tree,unsigned char Next);
	void genSingalItemCode(TreeItem * p_tree,TreeItem * m_tree,unsigned char Next);
	void initByNewFile();
	void initByWordFrequency();
protected:

public:
	GenerateHuffmanTree(string str);

	~GenerateHuffmanTree();
	void GenerateStart(MapOfTree * &);
	void GenerateStart(TreeItem * &);
	void SaveWordFrequency(ofstream &);

};


#endif
