/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include "config.h"

#define SCREEN_WIDTH		650
#define SCREEN_HEIGHT		540
#define COLUMNS				64
#define ROWS				48
#define FIELD_WIDTH			640
#define FIELD_HEIGHT		480
#define TIMEOUT_MS			80

#define RANDOM_START_N		20
#define RANDOM_START_M		15
#define RANDOM_COUNT_N		5
#define RANDOM_COUNT_M		4

#define CELL_SCALE_FACTOR	0.5
#define CELL_SCALE_STEP		0.2

#define VERSION_MAJOR		0
#define VERSION_MIDLE		5
#define VERSION_MINOR		0

#define TERMINATE_THREAD_TIMEOUT 1500

//-------------------------------------------------------------------------------------------------
Config* Config::m_self = nullptr;

//-------------------------------------------------------------------------------------------------
Config::Config()
	:m_cellScale(CELL_SCALE_FACTOR)
	,m_columns(COLUMNS)
	,m_rows(ROWS)
	,m_screenWidth(SCREEN_WIDTH)
	,m_screenHeight(SCREEN_HEIGHT)
	,m_fieldWidth(FIELD_WIDTH)
	,m_fieldHeight(FIELD_HEIGHT)
	,m_thread_timeout_ms(TIMEOUT_MS)
	,m_bgAreaColor(QColor(150,240,0))
	,m_brdColor(Qt::cyan)
	,m_cellColor(Qt::blue)
	,m_randomN_POS(RANDOM_START_N)
	,m_randomM_POS(RANDOM_START_M)
	,m_randomN_CNT(RANDOM_COUNT_N)
	,m_randomM_CNT(RANDOM_COUNT_M)
	,m_workMode(UndefinedMode)
	,m_minVer(VERSION_MINOR)
	,m_midVer(VERSION_MIDLE)
	,m_majVer(VERSION_MAJOR)
	,m_threadTerminateMsTimeout(TERMINATE_THREAD_TIMEOUT)
{
	static_assert(COLUMNS > 2, "columns must be greater 2");
	static_assert(ROWS > 2, "rows must be greater 2");
}

//-------------------------------------------------------------------------------------------------
Config* Config::instance()
{
	if (!m_self)
		m_self = new Config;
	return m_self;
}

//-------------------------------------------------------------------------------------------------
void Config::scenePosToIndex(QPointF pos, int& i, int& j)
{
	i = (int)(pos.x() / cellWidth());
	j = (int)(pos.y() / cellHeight());
}

//-------------------------------------------------------------------------------------------------
QString Config::version()const
{
	QString sVer = QString("%1.%2.%3").arg(majVer()).arg(midVer()).arg(minVer());
	return sVer;
}

//-------------------------------------------------------------------------------------------------
