/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QColor>
#include <QPointF>
#include <QObject>

#include "game.h"


//=================================================================================================
class Config
{
public:
	enum WorkMode
	{
		UndefinedMode = 0,			//Неопределенный
		GameMode,					//Режим игры
		EditMode,					//Режим редактирования
	};

	enum Linguas
	{
		UndefLanguage = 0,
		English,
		Russian,
	};

protected:
	int m_screenWidth;
	int m_screenHeight;

	int m_fieldWidth;
	int m_fieldHeight;

	int m_columns;
	int m_rows;

	int m_thread_timeout_ms;

	QColor m_bgAreaColor;
	QColor m_brdColor;
	QColor m_cellColor;

	int m_randomN_CNT;
	int m_randomM_CNT;
	int m_randomN_POS;
	int m_randomM_POS;

	int m_majVer;
	int m_midVer;
	int m_minVer;

	WorkMode m_workMode;
	Linguas  m_language;

	unsigned long m_threadTerminateMsTimeout;
	unsigned long m_statusBarMsgTimeout;

	Game	*m_game;


	std::string			m_defaultFilename;

public:
	virtual ~Config() {}

	static Config* instance();

private:
	Config();
	static Config* m_self;

public:
	int screenWidth()const { return m_screenWidth; }
	int screenHeight()const { return m_screenHeight; }

	const int columns()const { return m_columns; }
	const int rows()const { return m_rows; }

	int fieldWidth()const { return m_fieldWidth; }
	int fieldHeight()const { return m_fieldHeight; }

	int cellWidth()const { return m_fieldWidth / columns(); }
	int cellHeight()const { return m_fieldHeight / rows(); }

	int threadTimeoutMs()const { return m_thread_timeout_ms; }

	QColor areaBackgroundColor()const { return m_bgAreaColor; }
	QColor borderColor()const { return m_brdColor; }
	QColor cellColor()const { return m_cellColor; }

	int randomStartN()const { return m_randomN_POS; }
	int randomStartM()const { return m_randomM_POS; }
	int randomCountN()const { return m_randomN_CNT; }
	int randomCountM()const { return m_randomM_CNT; }

	WorkMode currentMode()const { return m_workMode; }
	Linguas  currentLanguage()const { return m_language; }

	void setGameMode() { m_workMode = GameMode; }
	void setEditMode() { m_workMode = EditMode; }

	void setRussian() { m_language = Russian; }
	void setEnglish() { m_language = English; }

	void scenePosToIndex(QPointF pos, int& i, int& j);

	int minVer()const { return m_minVer; }
	int midVer()const { return m_midVer; }
	int majVer()const { return m_majVer; }

	QString version()const;

	unsigned long threadTerminateTimeoutMs()const { return m_threadTerminateMsTimeout; }
	unsigned long statusBarTimeout()const { return m_statusBarMsgTimeout; }

	Game* game() { return m_game; }
	void createGame(QObject* parent = nullptr) { m_game = new Game(parent); }

	int index(int i, int j);

	std::string filename()const { return m_defaultFilename; }
};

//=================================================================================================

#endif // __CONFIG_H__
