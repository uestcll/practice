#ifndef MAP_TREE
#define MAP_TREE

#include "TreeItem.h"
#include <map>

using namespace std;

class MapOfTree
{
private:
	const MapOfTree & operator =(const MapOfTree &);
	MapOfTree(const MapOfTree &);
	
	map<unsigned char,TreeItem *> map_tree;

protected:
public:
	MapOfTree();
	~MapOfTree();
	void addToMap(TreeItem *);
	TreeItem * fdTreeItem(unsigned char );

};


#endif
