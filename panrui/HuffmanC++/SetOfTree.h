#ifndef SET_TREE
#define SET_TREE

#include "TreeItem.h"
#include "WordFrequency.h"
#include "MapOfTree.h"
#include <vector>
#include <list>

using namespace std;
class TreeItemSortCondition:less<TreeItem *>
{
public:
	bool operator()(TreeItem * ti1, TreeItem * ti2)
	{
		return ti1->getCount()<ti2->getCount();
	}
};


class SetOfTree
{
private:
	const SetOfTree & operator = (SetOfTree &);
	SetOfTree(const SetOfTree &);
	
	list<TreeItem *> set_tree;
	MapOfTree * map_tree;
	
	void reduceAndCreateNewElement();
	void writeToMap(list<TreeItem *>::iterator &);
protected:
public:
	SetOfTree(MapOfTree *);
	~SetOfTree();
	void AddToSet(WordFrequency &);
	MapOfTree * constructTree();
	TreeItem * getTreeHead();

	
};
#endif
