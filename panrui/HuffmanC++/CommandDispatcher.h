#ifndef COMMAND_DISPATCHER
#define COMMAND_DISPATCHER
#include <string>
#include <cstdarg>

class CommandDispatcher
{
private:
	CommandDispatcher(CommandDispatcher &);
	const CommandDispatcher & operator = (const CommandDispatcher &);
protected:
	unsigned char	** cmd;
	unsigned int	num;
	virtual void paraAnalysis() = 0;
public:
	CommandDispatcher(unsigned int num);
	virtual ~CommandDispatcher();
	virtual bool Dispatch() = 0;
};
#endif