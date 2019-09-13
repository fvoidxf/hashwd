/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#include <QSettings>
#include "config.h"

#define SCREEN_WIDTH		650
#define SCREEN_HEIGHT		540

#define COLUMNS				32
#define ROWS				24

#define FIELD_WIDTH			640
#define FIELD_HEIGHT		480
#define TIMEOUT_MS			80

#define RANDOM_START_N		20
#define RANDOM_START_M		15
#define RANDOM_COUNT_N		5
#define RANDOM_COUNT_M		4


#define VERSION_MAJOR		0
#define VERSION_MIDLE		3
#define VERSION_MINOR		0

#define TERMINATE_THREAD_TIMEOUT	1500
#define STATUSBAR_MSG_TIMEOUT		5000

#define DEFAULT_FILENAME	"qtlife.sav"
#define DEFAULT_SETTINGS	"qtlife.ini"

//-------------------------------------------------------------------------------------------------
Config* Config::m_self = nullptr;

//-------------------------------------------------------------------------------------------------
Config::Config()
	: m_columns(COLUMNS)
	, m_rows(ROWS)
	, m_screenWidth(SCREEN_WIDTH)
	, m_screenHeight(SCREEN_HEIGHT)
	, m_fieldWidth(FIELD_WIDTH)
	, m_fieldHeight(FIELD_HEIGHT)
	, m_thread_timeout_ms(TIMEOUT_MS)
	, m_bgAreaColor(QColor(150, 240, 0))
	, m_brdColor(Qt::cyan)
	, m_cellColor(Qt::blue)
	, m_randomN_POS(RANDOM_START_N)
	, m_randomM_POS(RANDOM_START_M)
	, m_randomN_CNT(RANDOM_COUNT_N)
	, m_randomM_CNT(RANDOM_COUNT_M)
	, m_workMode(UndefinedMode)
	, m_minVer(VERSION_MINOR)
	, m_midVer(VERSION_MIDLE)
	, m_majVer(VERSION_MAJOR)
	, m_threadTerminateMsTimeout(TERMINATE_THREAD_TIMEOUT)
	, m_statusBarMsgTimeout(STATUSBAR_MSG_TIMEOUT)
	, m_language(Russian)
	, m_game(nullptr)
	, m_defaultFilename(DEFAULT_FILENAME)
	, m_sticker(nullptr)
	, m_settingsFilename(DEFAULT_SETTINGS)
{
	static_assert(COLUMNS > 2, "columns must be greater 2");
	static_assert(ROWS > 2, "rows must be greater 2");
	m_sticker = new CompCont;
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
int Config::index(int i, int j)
{
	return i * m_rows + j;
}

//-------------------------------------------------------------------------------------------------
bool Config::readSettings()
{
	QSettings sttg(settingsFilename().c_str(), QSettings::IniFormat);

	//Читаем версию
	int Maj = 0, Mid = 0, Min = 0;
	Maj = sttg.value("VersionMajor", -1).toInt();
	if (Maj == -1)return false;
	Mid = sttg.value("VersionMiddle", -1).toInt();
	if (Mid == -1)return false;
	Min = sttg.value("VersionMinor", -1).toInt();
	if (Min == -1)return false;

	if (VERSION_MAJOR > Maj)
		throw std::runtime_error("ini file to much old!");

	if (VERSION_MAJOR == Maj)
	{
		if (VERSION_MIDLE > Mid)
			throw std::runtime_error("ini file bad back cap!");
	}

	m_majVer = Maj, m_midVer = Mid, m_minVer = Min;

	m_columns = sttg.value("FieldColumns", 0).toInt();
	m_rows = sttg.value("FieldRows", 0).toInt();

	m_fieldWidth = sttg.value("FieldWidth", 0).toInt();
	m_fieldHeight = sttg.value("FieldHeight", 0).toInt();

	m_screenWidth = sttg.value("ScreenWidth", 0).toInt();
	m_screenHeight = sttg.value("screenHeight", 0).toInt();

	m_language = (Linguas)sttg.value("Language", 0).toInt();

	m_thread_timeout_ms = sttg.value("ThreadTimeout", 0).toInt();

	m_bgAreaColor = sttg.value("AreaBackgroundColor").value<QColor>();
	m_brdColor = sttg.value("BorderLineColor").value<QColor>();
	m_cellColor = sttg.value("CellColor").value<QColor>();
}

//-------------------------------------------------------------------------------------------------
void Config::writeSettings()
{
	QSettings sttg(settingsFilename().c_str(), QSettings::IniFormat);

	//Записываем версию
	sttg.setValue("VersionMajor", m_majVer);
	sttg.setValue("VersionMiddle", m_midVer);
	sttg.setValue("VersionMinor", m_minVer);

	sttg.setValue("FieldColumns", m_columns);
	sttg.setValue("FieldRows", m_rows);

	sttg.setValue("FieldWidth", m_fieldWidth);
	sttg.setValue("FieldHeight", m_fieldHeight);

	sttg.setValue("ScreenWidth", m_screenWidth);
	sttg.setValue("ScreenHeight", m_screenHeight);

	sttg.setValue("Language", m_language);

	sttg.setValue("ThreadTimeout", m_thread_timeout_ms);

	sttg.setValue("AreaBackgroundColor", m_bgAreaColor);
	sttg.setValue("BorderLineColor", m_brdColor);
	sttg.setValue("CellColor", m_cellColor);
}

//-------------------------------------------------------------------------------------------------
