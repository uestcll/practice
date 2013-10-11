#include "MapOfTree.h"

MapOfTree::MapOfTree()
{

}

MapOfTree::~MapOfTree()
{

}

void MapOfTree::addToMap(TreeItem * h_tree)
{
	map_tree.insert(pair<unsigned char,TreeItem *>(h_tree->getValue(),h_tree));
}

TreeItem * MapOfTree::fdTreeItem(unsigned char value)
{
	map<unsigned char,TreeItem *>::iterator it = map_tree.find(value);
	if(it != map_tree.end())
		return it->second;
	else
		return NULL;
}