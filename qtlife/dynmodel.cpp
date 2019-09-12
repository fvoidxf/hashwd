/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <stdexcept>
#include <QVector>
#include <QFile>
#include "dynmodel.h"
#include "config.h"

//-------------------------------------------------------------------------------------------------
DynModel::DynModel(int N, int M)
	:n(N)
	,m(M)
{

}

//-------------------------------------------------------------------------------------------------
DynModel::~DynModel()
{
	free();
}

//-------------------------------------------------------------------------------------------------
bool DynModel::allocate()
{
	data = (unsigned char **)(new unsigned char*[n]);
	for (auto i = 0; i < n; i++)
	{
		data[i] = new unsigned char[m];
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
unsigned char& DynModel::item(int i, int j)
{
	if ((i < 0) || (i >= n))
		throw std::range_error("invalid i index");
	if ((j < 0) || (j >= m))
		throw std::range_error("invalid j index");
	return data[i][j];
}

//-------------------------------------------------------------------------------------------------
unsigned char& DynModel::operator()(int i, int j)
{
	return item(i, j);
}

//-------------------------------------------------------------------------------------------------
void DynModel::free()
{
	for (auto i = 0; i < n; i++)
		delete[] data[i];
	delete data;
}

//-------------------------------------------------------------------------------------------------
void DynModel::clear()
{
	for (auto i = 0; i < n; i++)
		for (auto j = 0; j < m; j++)
			data[i][j] = 0;
}

//-------------------------------------------------------------------------------------------------
bool DataPacker::operator[](int index)const
{
	if (index < 0)
		throw std::range_error("invalid index");
	if (index > sizeof(TData) * 8)
		throw std::range_error("invalid index");

	TData t = 0x00000001 << index;
	return t & m_data;
}

//-------------------------------------------------------------------------------------------------
void DataPacker::setData(int index, bool bFlag)
{
	if (index < 0)
		throw std::range_error("invalid index");
	if (index > sizeof(TData) * 8)
		throw std::range_error("invalid index");

	if (bFlag)
	{
		TData t = 0x00000001 << index;
		m_data |= t;
	}
	else
	{
		if (operator[](index))
		{
			TData t = 0x00000001 << index;
			m_data ^= t;
		}
	}
}

//-------------------------------------------------------------------------------------------------
bool FileCtrlModel::save()
{
	unsigned int uiColumns = Config::instance()->columns();
	unsigned int uiRows = Config::instance()->rows();

	unsigned int cnt = (uiColumns * uiRows / (8 * sizeof(unsigned int))) + 1;
	QVector<DataPacker> vec(cnt);

	if (!cnt)
		return false;
	if (!uiColumns)
		return false;
	if (!uiRows)
		return false;
	QMutexLocker lock(m_model->mutex());
	for (auto i = 0; i < uiColumns; i++)
	{
		for (auto j = 0; j < uiRows; j++)
		{
			int index = Config::instance()->index(i, j);
			int compIndx = (int)(index / (8 * sizeof(unsigned int)));
			int irrIndx = (int)(index % (8 * sizeof(unsigned int)));
			vec[compIndx].setData(irrIndx, (bool)m_model->item(i, j));
		}
	}

	savePacker(vec);

	return true;
}

//-------------------------------------------------------------------------------------------------
void FileCtrlModel::savePacker(QVector<DataPacker>& vec)
{
	unsigned int uiColumns = Config::instance()->columns();
	unsigned int uiRows = Config::instance()->rows();

	QFile file(m_filename.c_str());
	if (file.open(QIODevice::WriteOnly))
	{
		file.write((char*)&uiColumns, sizeof(uiColumns));
		file.write((char*)&uiRows, sizeof(uiRows));

		for (DataPacker pk : vec)
		{
			DataPacker::TData td = pk.getData();
			file.write((char*)(&td), sizeof(DataPacker::TData));
		}
		file.close();
	}
}

//-------------------------------------------------------------------------------------------------
bool FileCtrlModel::load()
{
	unsigned int uiColumns = 0;
	unsigned int uiRows = 0;

	QVector<DataPacker> vec;

	QFile file(m_filename.c_str());
	if (file.open(QIODevice::ReadOnly))
	{
		file.read((char*)&uiColumns, sizeof(uiColumns));
		file.read((char*)&uiRows, sizeof(uiRows));

		if (uiColumns <= 0)
			return false;
		if (uiRows <= 0)
			return false;

		unsigned int cnt = (uiColumns * uiRows / (8 * sizeof(unsigned int))) + 1;
		
		vec.resize(cnt);

		for (auto i = 0; i < cnt; i++)
		{
			DataPacker::TData td;
			file.read((char*)&td, sizeof(td));
			vec[i] = td;
		}

		file.close();
	}

	if (!vec.size())
		return false;
	else
	{
		QMutexLocker lock(m_model->mutex());
		m_model->clear();
		for (auto i = 0; i < uiColumns; i++)
		{
			for (auto j = 0; j < uiRows; j++)
			{
				int index = Config::instance()->index(i, j);
				int compIndx = (int)(index / (8 * sizeof(unsigned int)));
				int irrIndx = (int)(index % (8 * sizeof(unsigned int)));
				bool bData = (bool)vec[compIndx][irrIndx];
				if (bData)
				{
					m_model->item(i, j) = 1;
					m_scene->addCell(i, j);
				}
			}
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
