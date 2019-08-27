/*
* created by fv01dxf@gmail.com
* General Public License v3 
*         2019
*/
#ifndef __FIELDTHREAD_H__
#define __FIELDTHREAD_H__

#include <QThread>
#include <QSharedPointer>
#include "dynmodel.h"
#include "field.h"

//=================================================================================================
class FieldThread : public QThread
{
    Q_OBJECT

public:
    FieldThread(QObject *parent = nullptr);
    virtual ~FieldThread();

    void setStopFlag();

    void modelStep();
    void modelInit();
    void randomModel(int N, int M);

    inline unsigned char randomBool();

protected:
    virtual void run()override;
    QSharedPointer<DynModel> model;
    mutable bool isRunning;

signals:
    void clearCells();
    void addCell(int i, int j);
};

//=================================================================================================

#endif // __FIELDTHREAD_H__
