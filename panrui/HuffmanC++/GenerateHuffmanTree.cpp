#include "GenerateHuffmanTree.h"

GenerateHuffmanTree::GenerateHuffmanTree(string str):str(str),m_tree(NULL),m_set(NULL),m_map(NULL),m_wf(NULL)
{

}

GenerateHuffmanTree::~GenerateHuffmanTree()
{
	if(m_tree != NULL)
		delete m_tree;
	if(m_set != NULL)
		delete m_set;
	if(m_map != NULL)
		delete m_map;
	if(m_wf != NULL)
		delete m_wf;
}

void GenerateHuffmanTree::GenerateStart(MapOfTree * &map)
{
	initByNewFile();

	m_wf->startCounting();

	m_set->AddToSet(*m_wf);
	m_set->constructTree();
	m_tree = m_set->getTreeHead();

	if(m_tree->getLT()!=NULL)
		genHFCode(m_tree,m_tree->getLT(),0);
	if(m_tree->getRT()!=NULL)
		genHFCode(m_tree,m_tree->getRT(),1);

	map = m_map;
}

void GenerateHuffmanTree::genHFCode(TreeItem * p_tree,TreeItem * m_tree,unsigned char Next)
{
	genSingalItemCode(p_tree,m_tree,Next);
	if(m_tree->getLT()!=NULL)
		genHFCode(m_tree,m_tree->getLT(),0);
	if(m_tree->getRT()!=NULL)
		genHFCode(m_tree,m_tree->getRT(),1);
}

void GenerateHuffmanTree::initByNewFile()
{
	m_wf = new WordFrequency(str);
	m_map = new MapOfTree;
	m_set = new SetOfTree(m_map);;

}

void GenerateHuffmanTree::genSingalItemCode(TreeItem * p_tree,TreeItem * m_tree,unsigned char Next)
{
	vector<unsigned char>::iterator begin,end;
	p_tree->returnHFCode(begin,end);
	m_tree->copyHFCode(begin,end);
	m_tree->setNextBit(Next);	
}

void GenerateHuffmanTree::SaveWordFrequency(ofstream & str)
{
	m_wf->saveFrequencyToFile(str);
}