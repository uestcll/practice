#ifndef PB_MAIN_LOOP
#define PB_MAIN_LOOP

#include <iostream>
#include <vector>
#include "CLClassTemplate.h"


#include <map>

using namespace std;

class PBmainLoop
{
private:
	string			curCMD;
    map<int ,void (*)()> f_map;		

	int analysisCMD();
	void listenCMD();
	bool dispatchCMD(int );
	static void Usage();
	void registed();

	const static int add_new_var = 0;
	const static int add_new_fun = 1;
	const static int write_to_file = 2;
	const static int edit_fun = 3;
	const static int assign_value = 4;
	const static int show_now = 5;
	const static int show_usage = 6;
protected:

public:
	PBmainLoop();
	~PBmainLoop();
	void mainloop();
};
class CLClassContentTemplate;
class PBtool
{
private:
	static bool isSingle;
public:
	static CLClassTemplate * m_cla;
	static CLClassContentTemplate * m_cla_content;
	static void init(string className,bool defaultInit);
	static void addVar();
	static void addFun();
	static void writeTofile();
	static void showNow();
	static void editFun();
	static void assignVal();

};

#endif
