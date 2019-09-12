/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include "comcont.h"
#include "config.h"

unsigned long long CompCont::m_gameStepIndex = 0;

//-------------------------------------------------------------------------------------------------
CompCont::CompCont()
	:m_memSize(0)
{

}

//-------------------------------------------------------------------------------------------------
CompCont::~CompCont()
{

}

//-------------------------------------------------------------------------------------------------
unsigned int CompCont::memCellSize()const
{
	if(!m_memSize)
	{
		unsigned int uiColumns = Config::instance()->columns();
		unsigned int uiRows = Config::instance()->rows();
		m_memSize = (uiColumns * uiRows / (8 * sizeof(unsigned int))) + 1;
	}
	return m_memSize;
}

//-------------------------------------------------------------------------------------------------
unsigned long long CompCont::globalIndex()
{
	return m_gameStepIndex;
}

//-------------------------------------------------------------------------------------------------
void CompCont::setGlobalIndex(unsigned long long index)
{
	m_gameStepIndex = index;
}

//-------------------------------------------------------------------------------------------------
unsigned long long CompCont::incIndex()
{
	return ++m_gameStepIndex;
}

//-------------------------------------------------------------------------------------------------
unsigned long long CompCont::decIndex()
{
	return --m_gameStepIndex;
}

//-------------------------------------------------------------------------------------------------
bool CompCont::add(TSModel* pModel)
{
	unsigned int uiColumns = Config::instance()->columns();
	unsigned int uiRows = Config::instance()->rows();

	if (!pModel)
		return false;
	if (!uiColumns)
		return false;
	if (!uiRows)
		return false;

	DataPacker::TData* pDatArr = new DataPacker::TData[memCellSize()];

	for (auto i = 0; i < uiColumns; i++)
	{
		for (auto j = 0; j < uiRows; j++)
		{
			int index = Config::instance()->index(i, j);
			int compIndx = (int)(index / (8 * sizeof(unsigned int)));
			int irrIndx = (int)(index % (8 * sizeof(unsigned int)));
			RefDataPacker pkr(pDatArr[compIndx]);
			pkr.setData(irrIndx, (bool)pModel->item(i, j));
		}
	}

	m_mem.push_back(pDatArr);

	return true;
}

//-------------------------------------------------------------------------------------------------
DataPacker::TData* CompCont::operator[](int index)
{
	if (index >= count())
		throw std::range_error("invalid index");
	return m_mem[index];
}

//-------------------------------------------------------------------------------------------------
