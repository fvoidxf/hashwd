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
		NewFile,
		LoadFile,
		SaveFile,
	};


	virtual ~ICommand(){}

	virtual void exec() = 0;

	static ICommand* create(Type cmdType);
	static ICommand* createCellCmd(Type cmdType, int i, int j);
	static ICommand* createFileCmd(Type cmdType, const std::string & filename);
};

//=================================================================================================s

#endif

