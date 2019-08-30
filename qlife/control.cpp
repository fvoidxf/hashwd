/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include "config.h"
#include "dynmodel.h"
#include "control.h"
#include "fieldthread.h"

//-------------------------------------------------------------------------------------------------
Control::Control(QObject *parent)
	:m_model( new DynModel( Config::instance()->columns(), Config::instance()->rows() ) )
	,m_thread( new FieldThread )
	,m_mutex(new QMutex)
{
	m_model->allocate();
	m_model->clear();

	time_t t;
	time(&t);
	srand(t);

	m_thread->setMutex(m_mutex);
	m_thread->setData(m_model);
}

//-------------------------------------------------------------------------------------------------
Control::~Control()
{
	if (m_model)
		delete m_model;
	if (m_thread)
	{
		if (m_thread->isRunning())
		{
			m_thread->setStopFlag();
			m_thread->wait(Config::instance()->threadTerminateTimeoutMs());
			m_thread->terminate();
			delete m_thread;
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool Control::init()
{
	return true;
}

//-------------------------------------------------------------------------------------------------
void Control::fillRandom()
{
	m_thread->randomModel();
}

//-------------------------------------------------------------------------------------------------
void Control::startThread()
{
	m_thread->start();
}

//-------------------------------------------------------------------------------------------------
void Control::clearModel()
{
	m_thread->clearModel();
}

//-------------------------------------------------------------------------------------------------
