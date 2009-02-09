#include <QApplication>
#include "model/universum.h"
#include "presenter/universum.h"
#include "view/universum.h"

int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	View::Universum view;
	Model::Universum model("audio.xml");
	Presenter::Universum presenter(view, model);
	view.show(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	return app.exec();
}
