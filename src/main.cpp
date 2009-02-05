#include <QApplication>
#include "mainwindowimpl.h"
#include "worldmodel.h"
#include "worldpresenter.h"

int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	MainWindowImpl win;
	WorldModel model("audio.xml");
	WorldPresenter presenter(win, model);
	win.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
