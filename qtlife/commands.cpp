/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include "commands.h"
#include "config.h"
#include "strings.h"
#include "fieldscene.h"
#include "dynmodel.h"
#include "settings.h"

QMainWindow* SettingsCommand::m_wnd = nullptr;

//-------------------------------------------------------------------------------------------------
ICommand* ICommand::create(Type cmdType)
{
	switch (cmdType)
	{
	case Exit: return new ExitCommand;
	case ChangeMode: return new ChangeModeCommand;
	case About: return new AboutCommand;
	case Settings: return new SettingsCommand;
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
ICommand* ICommand::createFileCmd(Type cmdType, const std::string& filename)
{
	switch (cmdType)
	{
	case NewFile: return new NewFileCommand(filename);
	case SaveFile:return new SaveFileCommand(filename);
	case LoadFile:return new LoadFileCommand(filename);
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
	try
	{
		if (Config::instance()->currentMode() == Config::EditMode)
		{
			Config::instance()->setGameMode();
			Config::instance()->game()->start();
		}
		else
		{
			Config::instance()->setEditMode();
			Config::instance()->game()->setStopFlag();
		}
	}
	catch (...)
	{

	}
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
	QMutexLocker lock(m_model->mutex());
	m_model->item(m_i, m_j) = 1;
	m_scene->addCell(m_i, m_j);
}

//-------------------------------------------------------------------------------------------------
void RemoveCellCommand::exec()
{
	QMutexLocker lock(m_model->mutex());
	m_model->item(m_i, m_j) = 0;
	m_scene->removeCell(m_i, m_j);
}

//-------------------------------------------------------------------------------------------------
void NewFileCommand::exec()
{
	QMutexLocker lock(m_scene->model()->mutex());
	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			if (m_scene->model()->item(i, j) == 1)
			{
				m_scene->model()->item(i, j) = 0;
				m_scene->removeCell(i, j);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
void SaveFileCommand::exec()
{
	std::auto_ptr<FileCtrlModel> pCtrl(new FileCtrlModel(Config::instance()->filename(), m_scene));
	pCtrl->save();
}

//-------------------------------------------------------------------------------------------------
void LoadFileCommand::exec()
{
	std::auto_ptr<FileCtrlModel> pCtrl(new FileCtrlModel(Config::instance()->filename(), m_scene));
	pCtrl->load();
}

//-------------------------------------------------------------------------------------------------
void SettingsCommand::exec()
{
	if (m_wnd == nullptr)
		m_wnd = new SettingsWindow;
	m_wnd->show();
}

//-------------------------------------------------------------------------------------------------
