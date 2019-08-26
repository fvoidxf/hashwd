/*
* created by fv01dxf@gmail.com
* FreeBSD License 2019
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
    FieldThread(QSharedPointer<Field> pField, QObject *parent = nullptr);
    virtual ~FieldThread();

    void modelStep();
    void modelInit();

protected:
    virtual void run()override;
    QSharedPointer<Field> field;
    QSharedPointer<DynModel> model;

signals:
    void clearCells();
    void addCell(int i, int j);
};

//=================================================================================================

#endif // __FIELDTHREAD_H__
