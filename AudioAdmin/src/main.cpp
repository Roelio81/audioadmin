#include <QApplication>
#include "model/model_universum.h"
#include "presenter/presenter_universum.h"
#include "view/view_universum.h"

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
