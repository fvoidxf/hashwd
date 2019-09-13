/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#include <QAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commands.h"
#include "config.h"
#include "strings.h"
#include "fieldscene.h"

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) 
	:QMainWindow(parent)
	,ui(new Ui::MainWindow)
	,m_exitAction(nullptr)
	,m_fileMenu(nullptr)
	,m_gameMenu(nullptr)
	,m_helpMenu(nullptr)
	,m_changeModeAction(nullptr)
	,m_aboutAction(nullptr)
	,m_newFileAction(nullptr)
	,m_saveFileAction(nullptr)
	,m_loadFileAction(nullptr)
	,m_stepForwardAction(nullptr)
	,m_stepBackwardAction(nullptr)
	,m_settingsAction(nullptr)
{
	Config::instance()->createGame(this);

    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize(Config::instance()->screenWidth(), Config::instance()->screenHeight());
	setCentralWidget(ui->graphicsView);

	ui->graphicsView->setScene(new FieldScene(this));

	if (Config::instance()->currentLanguage() == Config::Russian)
	{
		m_fileMenu = menuBar()->addMenu(QTLIFE_FILE_MENUNAME_RU);
		m_gameMenu = menuBar()->addMenu(QTLIFE_GAME_MENUNAME_RU);
		m_helpMenu = menuBar()->addMenu(QTLIFE_HELP_MENUNAME_RU);

		m_exitAction = new QAction(QTLIFE_ACTION_EXIT_RU, this);
		m_changeModeAction = new QAction(QTLIFE_ACTION_GAMEMODE_RU, this);
		m_aboutAction = new QAction(QTLIFE_ACTION_ABOUT_RU, this);
		m_newFileAction = new QAction(QTLIFE_ACTION_NEWFILE_RU, this);
		m_saveFileAction = new QAction(QTLIFE_ACTION_SAVEFILE_RU, this);
		m_loadFileAction = new QAction(QTLIFE_ACTION_LOADFILE_RU, this);

		m_stepForwardAction = new QAction(QTLIFE_ACTION_STEPFORWARD_RU, this);
		m_stepBackwardAction = new QAction(QTLIFE_ACTION_STEPBACKWARD_RU, this);

		m_settingsAction = new QAction(QTLIFE_ACTION_SETTINGS_RU, this);
	}
	else
	{
		m_fileMenu = menuBar()->addMenu(QTLIFE_FILE_MENUNAME_EN);
		m_gameMenu = menuBar()->addMenu(QTLIFE_GAME_MENUNAME_EN);
		m_helpMenu = menuBar()->addMenu(QTLIFE_HELP_MENUNAME_EN);

		m_exitAction = new QAction(QTLIFE_ACTION_EXIT_EN, this);
		m_changeModeAction = new QAction(QTLIFE_ACTION_GAMEMODE_EN, this);
		m_aboutAction = new QAction(QTLIFE_ACTION_ABOUT_EN, this);
		m_newFileAction = new QAction(QTLIFE_ACTION_NEWFILE_EN, this);
		m_saveFileAction = new QAction(QTLIFE_ACTION_SAVEFILE_EN, this);
		m_loadFileAction = new QAction(QTLIFE_ACTION_LOADFILE_EN, this);

		m_stepForwardAction = new QAction(QTLIFE_ACTION_STEPFORWARD_EN, this);
		m_stepBackwardAction = new QAction(QTLIFE_ACTION_STEPBACKWARD_EN, this);

		m_settingsAction = new QAction(QTLIFE_ACTION_SETTINGS_EN, this);
	}

	setWindowTitle(QTLIFE_APP_NAME);

	connect(m_stepForwardAction, SIGNAL(triggered()), this, SLOT(OnStepForward()));
	m_gameMenu->addAction(m_stepForwardAction);
	m_stepForwardAction->setEnabled(false);

	connect(m_stepBackwardAction, SIGNAL(triggered()), this, SLOT(OnStepBackward()));
	m_gameMenu->addAction(m_stepBackwardAction);
	m_stepBackwardAction->setEnabled(false);

	connect(m_changeModeAction, SIGNAL(triggered()), this, SLOT(OnChangeMode()));
	m_gameMenu->addAction(m_changeModeAction);

	connect(m_settingsAction, SIGNAL(triggered()), this, SLOT(OnSettings()));
	m_helpMenu->addAction(m_settingsAction);

	connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(OnAbout()));
	m_helpMenu->addAction(m_aboutAction);

	connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(OnNewFile()));
	m_fileMenu->addAction(m_newFileAction);

	connect(m_saveFileAction, SIGNAL(triggered()), this, SLOT(OnSaveFile()));
	m_fileMenu->addAction(m_saveFileAction);

	connect(m_loadFileAction, SIGNAL(triggered()), this, SLOT(OnLoadFile()));
	m_fileMenu->addAction(m_loadFileAction);

	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(OnExit()));
	m_fileMenu->addAction(m_exitAction);

	Config::instance()->setEditMode();

	if (Config::instance()->currentLanguage() == Config::Russian)
		OnUpdateStatusMsg(QTLIFE_INIT_MSG_RU);
	else
		OnUpdateStatusMsg(QTLIFE_INIT_MSG_EN);

	Config::instance()->writeSettings();
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnExit()
{
	std::auto_ptr<ICommand> pExit(ICommand::create(ICommand::Exit));
	pExit->exec();
	_update();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnChangeMode()
{
	std::auto_ptr<ICommand> pExit(ICommand::create(ICommand::ChangeMode));
	pExit->exec();
	_update();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::_update()
{
	if (Config::instance()->currentMode() == Config::EditMode)
	{
		m_stepForwardAction->setEnabled(false);
		m_stepBackwardAction->setEnabled(false);
		if (Config::instance()->currentLanguage() == Config::Russian)
		{
			m_changeModeAction->setText(QTLIFE_ACTION_GAMEMODE_RU);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_EDITMODE_RU);
		}
		else
		{
			m_changeModeAction->setText(QTLIFE_ACTION_GAMEMODE_EN);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_EDITMODE_EN);
		}
	}
	else
	{
		m_stepForwardAction->setEnabled(true);
		if(CompCont::globalIndex() < Config::instance()->sticker()->count())
			m_stepBackwardAction->setEnabled(true);
		if (Config::instance()->currentLanguage() == Config::Russian)
		{
			m_changeModeAction->setText(QTLIFE_ACTION_EDITMODE_RU);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_GAMEMODE_RU);
		}
		else
		{
			m_changeModeAction->setText(QTLIFE_ACTION_EDITMODE_EN);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_GAMEMODE_EN);
		}
	}
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnUpdateStatusMsg(const QString& msg)
{
	statusBar()->showMessage(msg, Config::instance()->statusBarTimeout());
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnAbout()
{
	std::auto_ptr<ICommand> pAbout(ICommand::create(ICommand::About));
	pAbout->exec();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnNewFile()
{
	std::auto_ptr<ICommand> pNewFile(ICommand::createFileCmd(ICommand::NewFile, Config::instance()->filename()));
	dynamic_cast<IFileCommand*>(pNewFile.get())->setScene(dynamic_cast<FieldScene*>( ui->graphicsView->scene() ) );
	pNewFile->exec();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnSaveFile()
{
	std::auto_ptr<ICommand> pSaveFile(ICommand::createFileCmd(ICommand::SaveFile, Config::instance()->filename()));
	dynamic_cast<IFileCommand*>(pSaveFile.get())->setScene(dynamic_cast<FieldScene*>(ui->graphicsView->scene()));
	pSaveFile->exec();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnLoadFile()
{
	std::auto_ptr<ICommand> pLoadFile(ICommand::createFileCmd(ICommand::LoadFile, Config::instance()->filename()));
	dynamic_cast<IFileCommand*>(pLoadFile.get())->setScene(dynamic_cast<FieldScene*>(ui->graphicsView->scene()));
	pLoadFile->exec();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnStepForward()
{

}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnStepBackward()
{

}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnSettings()
{
	std::auto_ptr<ICommand> pSettings(ICommand::create(ICommand::Settings));
	pSettings->exec();
}

//-------------------------------------------------------------------------------------------------

