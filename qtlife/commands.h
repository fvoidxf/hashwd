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

#endif
