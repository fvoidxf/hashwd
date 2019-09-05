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
	void setScene(FieldScene* scene) { m_scene = scene; }
	void setStopFlag() { m_running = false;}

protected:
	virtual void run()override;

	TSModel			*m_model;
	FieldScene		*m_scene;
	bool			m_running;
};

//=================================================================================================

#endif
