/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/

#ifndef __DYNMODEL_H__
#define __DYNMODEL_H__

#ifdef _DEBUG
#include <vld.h>
#endif

#include <QMutex>
#include <QMutexLocker>

//=================================================================================================
class DynModel
{
protected:
	unsigned char **data;
	const int n;
	const int m;

public:
	DynModel(int N, int M);
	virtual ~DynModel();

	int N()const { return n; }
	int M()const { return m; }

	bool allocate();
	unsigned char& item(int i, int j);
	void free();
	void clear();
	unsigned char& operator()(int i, int j);
};

//=================================================================================================
class TSModel : public DynModel
{
protected:
	QMutex		m_mtx;

public:
	QMutex * mutex() { return &m_mtx; }
	~TSModel(){}
	TSModel(int N, int M):DynModel(N,M)
	{
		allocate();
		clear();
	}
};

//=================================================================================================

#endif // __DYNMODEL_H__
