#include "mainwindowimpl.h"
#include "worldmodel.h"
#include "worldpresenter.h"

WorldPresenter::WorldPresenter(MainWindowImpl &mainWindow, WorldModel &worldModel)
: m_mainWindow(mainWindow)
, m_worldModel(worldModel)
{
	connect(&m_mainWindow, SIGNAL(backupSignal(const QString &)), &m_worldModel, SLOT(save(const QString &)));
	connect(&m_mainWindow, SIGNAL(restoreSignal(const QString &)), &m_worldModel, SLOT(load(const QString &)));
}

WorldPresenter::~WorldPresenter()
{
}
