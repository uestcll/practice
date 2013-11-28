#include "PBmainLoop.h"
#include "CLClassContentTemplate.h"
#ifdef _LINUX_PROC_
const int PBmainLoop::add_new_var;
const int PBmainLoop::add_new_fun;
const int PBmainLoop::write_to_file;
const int PBmainLoop::edit_fun;
const int PBmainLoop::assign_value;
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
	if(curCMD == "e") return edit_fun;
	if(curCMD == "a") return assign_value;
	if(curCMD == "s") return show_now;
	
	return show_usage; 
}
void PBmainLoop::registed()
{
	f_map.insert(pair<int,void (*)()>(add_new_fun,PBtool::addFun));
	f_map.insert(pair<int,void (*)()>(add_new_var,PBtool::addVar));
	f_map.insert(pair<int,void (*)()>(write_to_file,PBtool::writeTofile));
	f_map.insert(pair<int,void (*)()>(show_usage,Usage));
	f_map.insert(pair<int,void (*)()>(edit_fun,PBtool::editFun));
	f_map.insert(pair<int,void (*)()>(assign_value,PBtool::assignVal));
	f_map.insert(pair<int,void (*)()>(show_now,PBtool::showNow));
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
	cout<<"e : edit function"<<endl;
	cout<<"a : assign value"<<endl;
}

void PBtool::addFun()
{
	string access;
	string typeName;
	string functionName;
	string paraName;
	cout<<"access:";
	cin.sync();
	getline(cin,access,'\n');
	cout<<"typeName:";
	cin.sync();
	getline(cin,typeName,'\n');
	cout<<"functionName:";
	cin.sync();
	getline(cin,functionName,'\n');
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
	cin.sync();
	getline(cin,access,'\n');
	cout<<"typeName:";
	cin.sync();
	getline(cin,typeName,'\n');
	cout<<"VariableName:";
	cin.sync();
	getline(cin,VariableName,'\n');
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
	cout<<*m_cla;
}
void PBtool::writeTofile()
{
	m_cla->writeToFile();
	m_cla_content->writeCPPtoDisk();
	delete m_cla;
	delete m_cla_content;
}

void PBtool::editFun()
{
	string functionName;
	cout<<"functionName:";
	cin>>functionName;
	memberFunctionContent * tmp = PBtool::m_cla_content->addNewFunction(functionName);
	
	if(tmp == NULL)
	{
		cout<<"No such function"<<endl;
		return ;
	}
		
	cout<<"content:(use 'end' to end edit)"<<endl;
	string content = "";
	do{
		cin.sync();
		getline(cin,content,'\n');	
		if(content != "end")
		tmp->insertSentence(content);
	}while(content != "end");

}
void PBtool::assignVal()
{
	string varName;
	cout<<"variableName:";
	cin>>varName;
	memberVarStatic * tmp = PBtool::m_cla_content->addNewVarStatic(varName);

	if(tmp == NULL)
	{
		cout<<"No such variable"<<endl;
		return ;
	}

	string value;
	cout<<"value:"<<endl;
	cin>>value;

	tmp->value = value;
}


