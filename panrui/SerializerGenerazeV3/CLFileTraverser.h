#ifndef CLFileTraverser_H
#define CLFileTraverser_H

#include <list>
#include <string>

using namespace std;

class CLFileTraverser
{
public:

	CLFileTraverser();
	~CLFileTraverser();

	list<string > * TraversingFile(string & v_path);

private:
	
	CLFileTraverser(const CLFileTraverser &);
	const CLFileTraverser & operator = (const CLFileTraverser &);

private:

	list<string > * m_fileList;

};


#endif