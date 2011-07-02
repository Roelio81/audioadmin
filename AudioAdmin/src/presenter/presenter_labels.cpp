#include "presenter_labels.h"
#include "../model/model_universe.h"
#include "../model/model_file.h"
#include "../view/view_labels.h"

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

using namespace Presenter;

Labels::Labels(View::Labels &view, Model::Universe &model)
    : m_view(view)
    , m_model(model)
{
}

Labels::~Labels()
{
}

void Labels::print()
{
    // Ask for a printer
    QPrintDialog printDialog(&m_view);
    if (printDialog.exec() != QDialog::Accepted)
        return;

    // Start printing
    if (QPrinter *printer = printDialog.printer())
    {
        QPainter painter(printer);

    }
}

void Labels::setup()
{
    m_view.clearPlacesAdjustment();
    const QVector<Model::File *> &files = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator itFile = files.begin(); itFile != files.end(); ++itFile)
    {
        Model::File *file = *itFile;
        Q_ASSERT(file);
        m_view.addPlaceAdjustment(file->getPlaceAdjustment());
    }
    m_view.setTestDate(QDate::currentDate().addYears(-2));
}

void Labels::teardown()
{
    // The only thing to do when pressing the OK button is to print
    print();
}
