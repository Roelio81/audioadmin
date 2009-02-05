#ifndef __WORLDPRESENTER_H__
#define __WORLDPRESENTER_H__

#include <QObject>

class MainWindowImpl;
class WorldModel;

class WorldPresenter : public QObject
{
	public:
		WorldPresenter(MainWindowImpl &mainWindow, WorldModel &worldModel);
		virtual ~WorldPresenter();

	private:
		MainWindowImpl &m_mainWindow;
		WorldModel &m_worldModel;
};

#endif // __WORLDPRESENTER_H__
