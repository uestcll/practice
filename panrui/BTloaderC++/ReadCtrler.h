#ifndef _READ_CONTROLER_
#define _READ_CONTROLER_
#include <string>
#include <fstream>

using namespace std;
class ReadCtrler
{
private:
	ReadCtrler(const ReadCtrler &);
	const ReadCtrler & operator = (const ReadCtrler &);

	static bool has_a;
	static ReadCtrler * reader;
	ifstream istr;
	static string path;

	ReadCtrler();
	~ReadCtrler();
public:
	static void SetPath(string &filepath);
	static ReadCtrler *GetInstence();
	
	int GetNextType();
	string GetString(unsigned long len);
	unsigned long GetNumber();
	bool tryEnd();

	
};
#endif