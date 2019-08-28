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
#define TIMEOUT_MS			200

//-------------------------------------------------------------------------------------------------
Config* Config::m_self = nullptr;

//-------------------------------------------------------------------------------------------------
Config::Config()
	:m_columns(COLUMNS)
	,m_rows(ROWS)
	,m_screenWidth(SCREEN_WIDTH)
	,m_screenHeight(SCREEN_HEIGHT)
	,m_fieldWidth(FIELD_WIDTH)
	,m_fieldHeight(FIELD_HEIGHT)
	,m_thread_timeout_ms(TIMEOUT_MS)
	,m_bgAreaColor(QColor(150,240,0))
	,m_brdColor(Qt::cyan)
	,m_cellColor(Qt::blue)
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
