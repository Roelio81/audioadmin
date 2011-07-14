#include "presenter_labels.h"
#include "../model/model_customer.h"
#include "../model/model_file.h"
#include "../model/model_labels.h"
#include "../model/model_universe.h"
#include "../view/view_labels.h"

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

using namespace Presenter;

Labels::Labels(View::Labels &view, Model::Labels &model)
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
        // Determine some margins and printer settings
        const double mmx = static_cast<double>(printer->pageRect().width()) / static_cast<double>(printer->widthMM());
        const double mmy = static_cast<double>(printer->pageRect().height()) / static_cast<double>(printer->heightMM());
        const int hmar = 9*mmx - printer->pageRect().left();
        const int vmar = 25*mmy - printer->pageRect().top();

        // Make a painter and configure with a default font
        QPainter painter(printer);
        QFont font("Times New Roman", 10);
        painter.setFont(font);
        int lineheight = painter.fontMetrics().height();

        // Print all labels that (based on what we selected in the dialog)
        const QVector<Model::File *> &files = m_model.getUniverse().getFiles();
        int labelNr = 0;
        for (QVector<Model::File *>::const_iterator itFile = files.begin(); itFile != files.end(); ++itFile)
        {
            Model::File *file = *itFile;
            Q_ASSERT(file);
            bool passesTestDateCheck = (!m_view.isTestDateChecked()) || (file->getTestDate() >= m_view.getTestDate());
            bool passesAdjustmentPlaceChecked = (!m_view.isAdjustmentPlaceChecked()) || (file->getPlaceAdjustment() == m_view.getPlaceAdjustment());
            if (passesTestDateCheck && passesAdjustmentPlaceChecked)
            {
                // This label passes both checks and should be printed

                // We print 21 labels per page, so every 21 labels we have to get a new page in the printer
                if ((labelNr > 0) && (labelNr % 21 == 0))
                    printer->newPage();

                // Print the name, address and city (each label is 66mm x 38.1mm)
                Model::Customer &customer = file->getCustomer();
                int x = (labelNr % 3)*70*mmx + hmar;
                int y = ((labelNr / 3)%7)*38.1*mmy + (lineheight) + vmar;
                painter.drawText(x, y, customer.getFirstName() + " " + customer.getName());
                y += lineheight;
                painter.drawText(x, y, customer.getStreet());
                y += lineheight;
                painter.drawText(x, y, QString::number(customer.getPostalCode()) + " " + customer.getCity());

                // Increment the label counter
                labelNr++;
            }
        }
    }
}

void Labels::setup()
{
    m_view.clearPlacesAdjustment();
    const QVector<Model::File *> &files = m_model.getUniverse().getFiles();
    for (QVector<Model::File *>::const_iterator itFile = files.begin(); itFile != files.end(); ++itFile)
    {
        Model::File *file = *itFile;
        Q_ASSERT(file);
        m_view.addPlaceAdjustment(file->getPlaceAdjustment());
    }
    m_view.setPlaceAdjustment(m_model.getPlaceAdjustment());
    m_view.setTestDate(m_model.getTestDate());
}

void Labels::teardown()
{
    // Save the last used value of test date and place adjustment
    m_model.setPlaceAdjustment(m_view.getPlaceAdjustment());
    m_model.setTestDate(m_view.getTestDate());

    // Now print the labels
    print();
}
