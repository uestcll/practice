#ifndef COMMAND_DISPATCHER
#define COMMAND_DISPATCHER
#include <string>
#include <cstdarg>

class CmdExecute;
class CmdAnalysis;
class CommandDispatcher
{
private:
	CommandDispatcher(CommandDispatcher &);
	const CommandDispatcher & operator = (const CommandDispatcher &);
	unsigned char	** cmd;
	unsigned int	paraNum;
	unsigned int 	analysisResult;
	CmdExecute  *	doExecute;
	CmdAnalysis *   doAnalysis;
public:
	CommandDispatcher(unsigned int paraNum,...);
	~CommandDispatcher();

	void startDispatch();
	
};
#endif
