/*
* created by fv01dxf@gmail.com
* General Public License v3
*         2019
*/
#ifndef __GAME_H__
#define __GAME_H__

#include <QThread>

class TSModel;
class FieldScene;

//=================================================================================================
class Game : public QThread
{
	Q_OBJECT

public:
	Game(QObject *parent = nullptr);
	~Game();

	bool step(TSModel *model);

	void setModel(TSModel* model) { m_model = model; }
	void setStopFlag() { m_running = false;}

protected:
	virtual void run()override;

	TSModel			*m_model;
	bool			m_running;

signals:
	void ModelUpdated();
};

//=================================================================================================

#endif
