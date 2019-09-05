#ifndef __COMMAND_H__
#define __COMMAND_H__

//=================================================================================================
class ICommand
{
public:
	enum Type
	{
		UnkCmd = 0,
		Exit,
		ChangeMode,
		About,
		AddCell,
		RemoveCell,
	};


	virtual ~ICommand(){}

	virtual void exec() = 0;

	static ICommand* create(Type cmdType);
	static ICommand* createCellCmd(Type cmdType, int i, int j);
};

//=================================================================================================s

#endif

