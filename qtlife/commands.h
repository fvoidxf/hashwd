#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "icommand.h"

class FieldScene;
class TSModel;

//=================================================================================================
class ExitCommand : public ICommand
{
public:
	ExitCommand(){}
	~ExitCommand(){}

	virtual void exec()override;
};

//=================================================================================================
class ChangeModeCommand : public ICommand
{
public:
	ChangeModeCommand(){}
	~ChangeModeCommand(){}

	virtual void exec()override;
};

//=================================================================================================
class AboutCommand : public ICommand
{
public:
	AboutCommand(){}
	~AboutCommand(){}

	virtual void exec()override;
};

//=================================================================================================
class AddCellCommand : public ICommand
{
public:
	AddCellCommand(int i, int j):m_i(i),m_j(j){}
	~AddCellCommand(){}

	virtual void exec()override;

	void setScene(FieldScene *scene) { m_scene = scene; }
	void setModel(TSModel* model) { m_model = model; }

private:
	int m_i;
	int m_j;

	FieldScene	*m_scene;
	TSModel		*m_model;
};

//=================================================================================================
class RemoveCellCommand : public ICommand
{
public:
	RemoveCellCommand(int i, int j) :m_i(i), m_j(j) {}
	~RemoveCellCommand() {}

	virtual void exec()override;

	void setScene(FieldScene *scene) { m_scene = scene; }
	void setModel(TSModel* model) { m_model = model; }

private:
	int m_i;
	int m_j;

	FieldScene	*m_scene;
	TSModel		*m_model;
};

//=================================================================================================
class IFileCommand : public ICommand
{
protected:
	const std::string	m_filename;
	FieldScene			*m_scene;

public:
	IFileCommand(const std::string& file):m_filename(file){}
	virtual ~IFileCommand(){}

	void setScene(FieldScene* scene) { m_scene = scene; }
};

//=================================================================================================
class NewFileCommand : public IFileCommand
{
public:
	NewFileCommand(const std::string file) :IFileCommand(file){}
	virtual ~NewFileCommand(){}


	virtual void exec();
};

//=================================================================================================
class SaveFileCommand : public IFileCommand
{
public:
	SaveFileCommand(const std::string file) :IFileCommand(file) {}
	virtual ~SaveFileCommand() {}


	virtual void exec();
};

//=================================================================================================
class LoadFileCommand : public IFileCommand
{
public:
	LoadFileCommand(const std::string file) :IFileCommand(file) {}
	virtual ~LoadFileCommand() {}


	virtual void exec();
};

//=================================================================================================

#endif
