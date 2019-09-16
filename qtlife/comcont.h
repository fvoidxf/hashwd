/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __COMCONT_H__
#define __COMCONT_H__

#include "dynmodel.h"

//=================================================================================================
struct SAVEFRAME
{
	unsigned long long CurrentFrame;
	int Columns;
	int Rows;
	unsigned int *data;
};

//=================================================================================================
struct ADDITIONALHEADER
{
	unsigned int reserved;
};

//=================================================================================================
struct SAVEGAME
{
	unsigned int majVer;
	unsigned int midVer;
	unsigned int minVer;

	ADDITIONALHEADER header;
	unsigned int FramesCount;
	SAVEFRAME *FRAMES;
};

//=================================================================================================
class CompCont
{
protected:
	QVector<DataPacker::TData*> m_mem;				//������, � ���. ����� �������� ��� ������������ ���� ����
	mutable unsigned int		m_memSize;			//������ �������� ���� ������ ���� ����
	static unsigned long long	m_gameStepIndex;	//���������� ������� ������ ����

public:
	CompCont();
	virtual ~CompCont();

	unsigned int memCellSize()const;
	unsigned int count()const { return m_mem.size(); }

	static unsigned long long globalIndex();
	static void setGlobalIndex(unsigned long long index);
	static unsigned long long incIndex();
	static unsigned long long decIndex();

	virtual bool add(TSModel* pModel);
	virtual DataPacker::TData* operator[](int index);
};

//=================================================================================================

#endif
