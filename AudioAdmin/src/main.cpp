#include "model/model_universe.h"
#include "presenter/presenter_universe.h"
#include "view/view_universe.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char ** argv)
{
    QApplication app( argc, argv );

    QTranslator translator;
    bool translationFound = translator.load("audioadmin_nl");
    Q_ASSERT(translationFound);
    app.installTranslator(&translator);

    View::Universe view;
    Model::Universe model(QString("audio.xml"));
    Presenter::Universum presenter(view, model);
    view.show();
    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
    return app.exec();
}
