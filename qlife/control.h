/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <QObject>

class DynModel;
class FieldThread;
class QMutex;

//=================================================================================================
class Control : public QObject
{
	Q_OBJECT

public:
	Control(QObject *parent = nullptr);
	virtual ~Control();

protected:
	DynModel				*m_model;
	QMutex					*m_mutex;
	FieldThread				*m_thread;

public:
	bool init();

	void fillRandom();
	void startThread();
	void clearModel();
};

//=================================================================================================

#endif // __CONTROL_H__
