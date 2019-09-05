#include <QAction>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commands.h"
#include "config.h"
#include "strings.h"
#include "fieldscene.h"
#include "workarea.h"

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
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize(Config::instance()->screenWidth(), Config::instance()->screenHeight());
	setCentralWidget(ui->graphicsView);

	ui->graphicsView->setScene(new FieldScene(this));

	QRectF areasz(0, 0, Config::instance()->fieldWidth(), Config::instance()->fieldHeight());

	Workarea *area = new Workarea(areasz, Config::instance()->columns(), Config::instance()->rows());
	area->setBackgroundColor(Config::instance()->areaBackgroundColor());
	area->setBorderColor(Config::instance()->borderColor());

	dynamic_cast<FieldScene*>(ui->graphicsView->scene())->addArea(area);

	if (Config::instance()->currentLanguage() == Config::Russian)
	{
		m_fileMenu = menuBar()->addMenu(QTLIFE_FILE_MENUNAME_RU);
		m_gameMenu = menuBar()->addMenu(QTLIFE_GAME_MENUNAME_RU);
		m_helpMenu = menuBar()->addMenu(QTLIFE_HELP_MENUNAME_RU);
		m_exitAction = new QAction(QTLIFE_ACTION_EXIT_RU, this);
		m_changeModeAction = new QAction(QTLIFE_ACTION_GAMEMODE_RU, this);
		m_aboutAction = new QAction(QTLIFE_ACTION_ABOUT_RU, this);
	}
	else
	{
		m_fileMenu = menuBar()->addMenu(QTLIFE_FILE_MENUNAME_EN);
		m_gameMenu = menuBar()->addMenu(QTLIFE_GAME_MENUNAME_EN);
		m_helpMenu = menuBar()->addMenu(QTLIFE_HELP_MENUNAME_EN);
		m_exitAction = new QAction(QTLIFE_ACTION_EXIT_EN, this);
		m_changeModeAction = new QAction(QTLIFE_ACTION_GAMEMODE_EN, this);
		m_aboutAction = new QAction(QTLIFE_ACTION_ABOUT_EN, this);
	}

	setWindowTitle(QTLIFE_APP_NAME);

	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(OnExit()));
	m_fileMenu->addAction(m_exitAction);

	connect(m_changeModeAction, SIGNAL(triggered()), this, SLOT(OnChangeMode()));
	m_gameMenu->addAction(m_changeModeAction);

	connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(OnAbout()));
	m_helpMenu->addAction(m_aboutAction);

	Config::instance()->setEditMode();

	if (Config::instance()->currentLanguage() == Config::Russian)
		OnUpdateStatusMsg(QTLIFE_INIT_MSG_RU);
	else
		OnUpdateStatusMsg(QTLIFE_INIT_MSG_EN);
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
		if (Config::instance()->currentLanguage() == Config::Russian)
		{
			m_changeModeAction->setText(QTLIFE_ACTION_GAMEMODE_RU);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_GAMEMODE_RU);
		}
		else
		{
			m_changeModeAction->setText(QTLIFE_ACTION_GAMEMODE_EN);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_GAMEMODE_EN);
		}
	}
	else
	{
		if (Config::instance()->currentLanguage() == Config::Russian)
		{
			m_changeModeAction->setText(QTLIFE_ACTION_EDITMODE_RU);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_EDITMODE_RU);
		}
		else
		{
			m_changeModeAction->setText(QTLIFE_ACTION_EDITMODE_EN);
			OnUpdateStatusMsg(QTLIFE_STATUSMSG_EDITMODE_EN);
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
