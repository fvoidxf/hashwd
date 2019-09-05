#include <QApplication>
#include <QMessageBox>
#include "commands.h"
#include "config.h"
#include "strings.h"
#include "fieldscene.h"
#include "dynmodel.h"

//-------------------------------------------------------------------------------------------------
ICommand* ICommand::create(Type cmdType)
{
	switch (cmdType)
	{
	case Exit: return new ExitCommand;
	case ChangeMode: return new ChangeModeCommand;
	case About: return new AboutCommand;
	}

	return nullptr;
}

//-------------------------------------------------------------------------------------------------
ICommand* ICommand::createCellCmd(Type cmdType, int i, int j)
{
	switch (cmdType)
	{
	case AddCell: return new AddCellCommand(i, j);
	case RemoveCell: return new RemoveCellCommand(i, j);
	}

	return nullptr;
}

//-------------------------------------------------------------------------------------------------
void ExitCommand::exec()
{
	qApp->exit();
}

//-------------------------------------------------------------------------------------------------
void ChangeModeCommand::exec()
{
	if (Config::instance()->currentMode() == Config::EditMode)
		Config::instance()->setGameMode();
	else
		Config::instance()->setEditMode();
}

//-------------------------------------------------------------------------------------------------
void AboutCommand::exec()
{
	QMessageBox msgBox;

	if (Config::instance()->currentLanguage() == Config::Russian)
	{
		msgBox.setText(QTLIFE_ACTION_ABOUT_RU);
		msgBox.setInformativeText(QTLIFE_APP_NAME);
	}
	else
	{
		msgBox.setText(QTLIFE_ACTION_ABOUT_EN);
		msgBox.setInformativeText(QTLIFE_APP_NAME);
	}
	
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);

	int iRes = msgBox.exec();
}

//-------------------------------------------------------------------------------------------------
void AddCellCommand::exec()
{
	m_scene->addCell(m_i, m_j);
	QMutexLocker lock(m_model->mutex());
	m_model->item(m_i, m_i) = 1;
}

//-------------------------------------------------------------------------------------------------
void RemoveCellCommand::exec()
{
	m_scene->removeCell(m_i, m_j);
	QMutexLocker lock(m_model->mutex());
	m_model->item(m_i, m_j);
}

//-------------------------------------------------------------------------------------------------