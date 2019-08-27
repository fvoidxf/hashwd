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

	QRectF areasz(0, 0, Config::instance()->fieldWidth(), Config::instance()->fieldHeight());

	//m_area = new Workarea(areasz, Config::instance()->columns(), Config::instance()->rows());
	//m_scene->addArea(m_area);

    //m_ui->graphicsView->setWorkarea(m_area);

	m_scene->update();

    m_thread->start();

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
/*void MainWindow::OnAddCell(int i, int j)
{
#ifdef _DEBUG
    _CrtMemState _memState;
    _CrtMemCheckpoint(&_memState);
    //_CrtDumpMemoryLeaks();
#endif
    //Дичайшие утечки, которые дают оба метода
    field->addCell(i,j);
    field->update();
#ifdef _DEBUG
    _CrtMemDumpAllObjectsSince(&_memState);

#endif
}*/

//-------------------------------------------------------------------------------------------------
void MainWindow::OnDataReady()
{
	if (!m_scene)
		return;

	QMutexLocker lock(m_thread->getMutex());
	for (auto i = 0; i < Config::instance()->columns(); i++)
	{
		for (auto j = 0; j < Config::instance()->rows(); j++)
		{
			if (m_thread->getData()->item(i, j) == 1)
			{
				m_scene->addCell(i, j);
				m_scene->update();
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
