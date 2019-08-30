/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#ifndef __FIELDTHREAD_H__
#define __FIELDTHREAD_H__

#include <QThread>
#include <QSharedPointer>
#include <QMutex>
#include "dynmodel.h"
#include "config.h"

//=================================================================================================
class FieldThread : public QThread
{
    Q_OBJECT

public:
    FieldThread(QObject *parent = nullptr);
    virtual ~FieldThread();

    void setStopFlag();

    void modelStep();
    void randomModel(int start_i = Config::instance()->randomStartN(), int start_j = Config::instance()->randomStartM(), int i_cnt = Config::instance()->randomCountN(), int j_cnt = Config::instance()->randomCountM());
	void clearModel();

	void setStepCount(unsigned long long steps) { m_stepCount = steps; }
	unsigned long long stepCount()const { return m_stepCount; }
	static unsigned long long GetInfiniteSteps() { return 0xffffffffffffffff; }
	void setInfiniteSteps() { m_stepCount = GetInfiniteSteps(); }

    inline unsigned char randomBool();

	DynModel* getData() { return m_model; }

	void setMutex(QMutex* mutex) { m_mutex = mutex; }
	void setData(DynModel* data) { m_model = data; }

protected:
    virtual void run()override;
    DynModel *m_model;
    mutable bool m_isRunning;
	mutable unsigned long long m_stepCount;
	QMutex *m_mutex;

signals:
    void clearCells();
	void dataReady();
};

//=================================================================================================

#endif // __FIELDTHREAD_H__
