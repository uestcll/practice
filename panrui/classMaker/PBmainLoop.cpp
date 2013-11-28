#include "PBmainLoop.h"
#include "CLClassContentTemplate.h"
#ifdef _LINUX_PROC_
const int PBmainLoop::add_new_var;
const int PBmainLoop::add_new_fun;
const int PBmainLoop::write_to_file;
const int PBmainLoop::show_now;
const int PBmainLoop::show_usage;
#endif

PBmainLoop::PBmainLoop()
{
	registed();
}

PBmainLoop::~PBmainLoop()
{
}
int PBmainLoop::analysisCMD()
{
	if(curCMD == "f") return add_new_fun; 
	if(curCMD == "v") return add_new_var;
	if(curCMD == "w") return write_to_file;
	
	return show_usage; 
}
void PBmainLoop::registed()
{
	f_map.insert(pair<int,void (*)()>(add_new_fun,PBtool::addFun));
	f_map.insert(pair<int,void (*)()>(add_new_var,PBtool::addVar));
	f_map.insert(pair<int,void (*)()>(write_to_file,PBtool::writeTofile));
	f_map.insert(pair<int,void (*)()>(show_usage,Usage));
}

void PBmainLoop::listenCMD()
{
	cin.sync();
	getline(cin,curCMD,'\n');
}

bool PBmainLoop::dispatchCMD(int actType)
{

	(f_map.find(actType))->second();
	if(actType == write_to_file)
			return false ;
	return true;
	
}

void PBmainLoop::mainloop()
{

	do
	{
		cout<<'#';
		curCMD.clear();
		listenCMD();
	
	}while(dispatchCMD(analysisCMD()));
}
void PBmainLoop::Usage()
{
	cout<<"v : add a var to class"<<endl;
	cout<<"f : add a function to class"<<endl;
	cout<<"w : write class to file"<<endl;
	cout<<"s : show current class"<<endl;
}

void PBtool::addFun()
{
	string access;
	string typeName;
	string functionName;
	string paraName;
	cout<<"access:";
	getline(cin,access,'\n');
	cout<<"typeName:";
	cin>>typeName;
	cout<<"functionName:";
	cin>>functionName;
	cout<<"paraName:";
	cin.sync();
	getline(cin,paraName,'\n');
	m_cla->addItem(access,typeName,functionName,paraName);


}

void PBtool::addVar()
{
	string access;
	string typeName;
	string VariableName;
	cout<<"access:";
	getline(cin,access,'\n');
	cout<<"typeName:";
	cin>>typeName;
	cout<<"VariableName:";
	cin>>VariableName;
	m_cla->addItem(access,typeName,VariableName);
}
bool PBtool::isSingle = 1;
CLClassTemplate * PBtool::m_cla = NULL;
CLClassContentTemplate * PBtool::m_cla_content = NULL;
void PBtool::init(string className,bool DefaultInit)
{
	if(PBtool::isSingle)
	PBtool::m_cla = new CLClassTemplate(className,DefaultInit);
	PBtool::m_cla_content = new CLClassContentTemplate(m_cla);
	isSingle = false;	
}
void PBtool::showNow()
{

}
void PBtool::writeTofile()
{
	m_cla->writeToFile();
	m_cla_content->writeCPPtoDisk();
	delete m_cla;
	delete m_cla_content;
}
