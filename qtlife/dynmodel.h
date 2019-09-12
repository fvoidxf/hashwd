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

#include <stdexcept>
#include <QVector>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include "fieldscene.h"


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
class DataPacker
{
public:
	typedef unsigned int TData;

protected:
	TData m_data;

public:
	virtual ~DataPacker(){}
	explicit DataPacker(TData data = 0):m_data(data){}

	virtual bool operator[](int index)const;

	TData getData()const { return m_data; }
	virtual void setData(int index, bool bFlag = true);

	DataPacker& operator=(const TData& td)
	{
		m_data = td;
		return *this;
	}
};

//=================================================================================================
class RefDataPacker
{
protected:
	DataPacker::TData& m_refData;

public:
	RefDataPacker(DataPacker::TData& RefData) :m_refData(RefData) {}

	virtual bool operator[](int index)const;
	virtual void setData(int index, bool bFlag = true);
};

//=================================================================================================
class FileCtrlModel
{
protected:
	const std::string	m_filename;
	TSModel				*m_model;
	FieldScene			*m_scene;

	void savePacker(QVector<DataPacker>& vec);

public:
	FileCtrlModel(const std::string& filename, FieldScene* pScene)
		:m_filename(filename)
		, m_scene(pScene)
		, m_model(pScene->model())
	{

	}

	virtual ~FileCtrlModel(){}

	virtual bool save();
	virtual bool load();
};

//=================================================================================================


#endif // __DYNMODEL_H__
