#ifndef	CLSetOffset_H
#define CLSetOffset_H

struct offset
{

	unsigned long from_start;
	unsigned long max_unit;

	const offset & operator += (const offset & another);

};

class CLClassDescribe;
class CLSerializerAndDeserializerCreater;

class CLSetOffset
{
public:

	CLSetOffset();
	~CLSetOffset();

	virtual offset startWork(CLClassDescribe * ,CLSerializerAndDeserializerCreater *);

private:

	CLSetOffset(const CLSetOffset &);
	const CLSetOffset & operator = (const CLSetOffset &);

};


#endif