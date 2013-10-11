#include "SetOfTree.h"


SetOfTree::SetOfTree(MapOfTree * map_tree):map_tree(map_tree)
{

}

SetOfTree::~SetOfTree()
{

}

void SetOfTree::AddToSet(WordFrequency &wf)
{
	wf.reset();
	for(unsigned int i = 0;i<wf.getSize();i++)
	{
		pair<unsigned char, unsigned long long > t_pair = wf.getPair();
		set_tree.push_back(new TreeItem(t_pair.first,t_pair.second));
	}

}

MapOfTree * SetOfTree::constructTree()
{
	while(set_tree.size() != 1)
		reduceAndCreateNewElement();
	return map_tree;
}

TreeItem  * SetOfTree::getTreeHead()
{
	return *set_tree.begin();
}

void SetOfTree::reduceAndCreateNewElement()
{
	set_tree.sort(TreeItemSortCondition());
	list<TreeItem *>::iterator ifir = set_tree.begin();
	list<TreeItem *>::iterator isec = ifir;
	isec++;

	set_tree.push_back(new TreeItem(*ifir,*isec,(*ifir)->getCount()+(*isec)->getCount()));

	writeToMap(ifir);
	writeToMap(isec);

	set_tree.erase(ifir);
	set_tree.erase(isec);
}

void SetOfTree::writeToMap(list<TreeItem *>::iterator & it)
{
	if(map_tree == NULL)
		return ;
	else
		if((*it)->getLT() == NULL)
			map_tree->addToMap(*it);
	
	return ;
}



