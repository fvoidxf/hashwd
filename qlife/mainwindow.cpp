/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#include <QThread>
#include "fieldthread.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dynmodel.h"
#include "fieldscene.h"
#include "fieldview.h"
#include "config.h"
#include "workarea.h"

//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,m_ui(new Ui::MainWindow)
    ,m_scene(nullptr)
	,m_area(nullptr)
{
    m_ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	setFixedSize( Config::instance()->screenWidth(), Config::instance()->screenHeight() );
    setCentralWidget(m_ui->graphicsView);

	m_mainMenu = new QMenu("File", this);
	menuBar()->addMenu(m_mainMenu);

	m_changeModeAction = new QAction("Edit mode", this);
	m_changeModeAction->setCheckable(true);
	connect(m_changeModeAction, SIGNAL(triggered()), this, SLOT(OnChangeMode()));

	m_controlMenu = new QMenu("Control", this);
	menuBar()->addMenu(m_controlMenu);

	m_exitAction = new QAction("Exit", this);
	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(OnExit()));

	m_fillRandom = new QAction("Fill random cells", this);
	connect(m_fillRandom, SIGNAL(triggered()), this, SLOT(OnFillRandom()));

	m_startAction = new QAction("Start", this);
	connect(m_startAction, SIGNAL(triggered()), this, SLOT(OnStart()));

	m_stopAction = new QAction("Stop", this);
	connect(m_stopAction, SIGNAL(triggered()), this, SLOT(OnStop()));

	m_clearFieldAction = new QAction("Clear field", this);
	connect(m_clearFieldAction, SIGNAL(triggered()), this, SLOT(OnClearField()));

	m_mainMenu->addAction(m_changeModeAction);
	m_mainMenu->addAction(m_exitAction);

	m_controlMenu->addAction(m_fillRandom);
	m_controlMenu->addAction(m_startAction);
	m_controlMenu->addAction(m_stopAction);
	m_controlMenu->addAction(m_clearFieldAction);

	Config::instance()->setGameMode();
	statusBar()->showMessage("Game mode");
}

//-------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	if (m_thread) {
		m_thread->setStopFlag();
		m_thread->wait();
	}
    delete m_ui;
}

//-------------------------------------------------------------------------------------------------
bool MainWindow::init()
{
	m_thread = new FieldThread(this);

	connect(m_thread, SIGNAL(clearCells()), this, SLOT(OnClearCells()));
	connect(m_thread, SIGNAL(dataReady()), this, SLOT(OnDataReady()));

    m_scene = new FieldScene(this);
	m_scene->init();

    m_ui->graphicsView->setScene(m_scene);
	m_ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
	m_ui->graphicsView->setUpdatesEnabled(true);

	QRectF areasz(0, 0, Config::instance()->fieldWidth(), Config::instance()->fieldHeight());

	m_area = new Workarea(areasz, Config::instance()->columns(), Config::instance()->rows());
	m_area->setBackgroundColor( Config::instance()->areaBackgroundColor() );
	m_area->setBorderColor( Config::instance()->borderColor() );
	m_scene->addArea(m_area);

    m_ui->graphicsView->setWorkarea(m_area);

	m_scene->update();

    return true;
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnClearCells()
{
	if (m_scene)
	{
		m_scene->clearCells();
		m_scene->update();
	}
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnDataReady()
{
	if (!m_scene)
		return;

	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			if (m_thread->getData()->item(i, j) == 1)
			{
				QMutexLocker lock(m_thread->getMutex());
				m_scene->addCell(i, j);
				lock.unlock();
				m_scene->update();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnExit()
{
	qApp->closeAllWindows();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnStart()
{
	if(Config::instance()->currentMode() == Config::GameMode)
		m_thread->start();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnStop()
{
	m_thread->terminate();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::OnChangeMode()
{
	if (Config::instance()->currentMode() == Config::GameMode)
	{
		Config::instance()->setEditMode();
		statusBar()->showMessage("Edit mode");
		if(m_thread->isRunning())
			m_thread->terminate();
	}
	else if (Config::instance()->currentMode() == Config::EditMode)
	{
		Config::instance()->setGameMode();
		statusBar()->showMessage("Game mode");
	}
}

//------------------------------------------------------------------------------------------------
void MainWindow::OnClearField()
{
	if (m_scene)
	{
		m_scene->clearCells();
		m_thread->clearModel();
		m_scene->update();
	}
}

//------------------------------------------------------------------------------------------------
void MainWindow::OnFillRandom()
{
	if (m_scene)
	{
		m_scene->clearCells();
		m_thread->randomModel();
		m_thread->setStepCount(1);
		m_thread->start();
		m_scene->update();
		m_thread->setInfiniteSteps();
	}
}

//------------------------------------------------------------------------------------------------
