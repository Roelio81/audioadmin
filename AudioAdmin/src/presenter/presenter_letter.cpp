#include "presenter_letter.h"
#include "presenter_measurements.h"
#include "../model/model_letter.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_universe.h"
#include "../view/view_letter.h"
#include "../view/view_measurements.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

Letter::Letter(View::Letter &view, Model::Letter &model)
    : m_view(view)
    , m_model(model)
{
}

Letter::~Letter()
{
}

void Letter::setup()
{
    const Model::File &file = m_model.getFile();
    const Model::Settings &settings = file.getUniverse().getSettings();

    m_view.setGreeting(getGreeting());
    m_view.setAddresseeName(getAddresseeName());
    m_view.setAddresseeStreet(getAddresseeStreet());
    m_view.setAddresseeCity(getAddresseeCity());
    m_view.setSenderName(settings.getName());
    m_view.setSenderStreet(settings.getStreet());
    m_view.setSenderCity(QString::number(settings.getPostalCode()) + " " + settings.getCity());
    m_view.setSenderTelephone(settings.getTelephone());
    m_view.setSenderMobilePhone(settings.getMobilePhone());

    QString postalDate = m_model.getPostalDate();
    if (postalDate.isEmpty())
        postalDate = settings.getCity() + ", " + QDate::currentDate().toString(tr("yyyy-MM-dd"));
    m_view.setPostalDate(postalDate);
    QString text = m_model.getText();
    if (text.isEmpty())
        text = getDefaultText();
    m_view.setText(text);
    if (m_model.hasConclusion())
    {
        QString conclusion = m_model.getConclusion();
        if (conclusion.isEmpty())
            conclusion = tr("In case you still have questions, you can reach me at the number at the header.");
        m_view.setConclusion(conclusion);
    }

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void Letter::teardown()
{
    m_model.setPostalDate(m_view.getPostalDate());
    m_model.setText(m_view.getText());
    if (m_model.hasConclusion())
        m_model.setConclusion(m_view.getConclusion());

    disconnect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void Letter::print()
{
    const Model::File &file = m_model.getFile();
    const Model::Settings &settings = file.getUniverse().getSettings();

    QPrintDialog printDialog(&m_view);
    printDialog.setEnabledOptions(QAbstractPrintDialog::None);
    if (printDialog.exec() != QDialog::Accepted)
        return;

    if (QPrinter *printer = printDialog.printer())
    {
        // Determine some margins and printer settings
        const int mmx = printer->width() / printer->widthMM();
        const int mmy = printer->height() / printer->heightMM();
        const int hmar = 25*mmx - printer->pageRect().left();
        const int vmar = 20*mmy - printer->pageRect().top();

        // Make a painter and configure with a default font
        QPainter painter(printer);
        QFont font("Arial");

        // Print the header of the letter
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(true);
        painter.setFont(font);
        painter.drawText(hmar, vmar, settings.getName());
        font.setPointSize(11);
        font.setBold(false);
        painter.setFont(font);
        int lineheight = painter.fontMetrics().height();
        painter.drawText(hmar, vmar + (3*lineheight)/2, settings.getCaption());
        painter.drawText(hmar, vmar + (5*lineheight)/2, settings.getStreet());
        painter.drawText(hmar, vmar + (7*lineheight)/2, QString::number(settings.getPostalCode()) + " " + settings.getCity());
        painter.drawText(hmar, vmar + (9*lineheight)/2, QString(tr("Nat.ID: ")) + settings.getNationalId());
        painter.drawText(150*mmx, vmar + (5*lineheight)/2, QString(tr("tel.: ")) + settings.getTelephone());
        painter.drawText(150*mmx, vmar + (7*lineheight)/2, QString(tr("mobile: ")) + settings.getMobilePhone());
        painter.drawText(150*mmx, vmar + (9*lineheight)/2, QString(tr("email: ")) + settings.getEmail());
        painter.drawLine(printer->paperRect().left(), 52*mmy, printer->paperRect().right(), 52*mmy);

        // Print the postal date
        painter.drawText(hmar, 62*mmy, m_view.getPostalDate());

        // Print the addressee's address
        font.setPointSize(12);
        font.setItalic(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(150*mmx, 62*mmy + (0*lineheight), getAddresseeName());
        painter.drawText(150*mmx, 62*mmy + (1*lineheight), getAddresseeStreet());
        painter.drawText(150*mmx, 62*mmy + (2*lineheight), getAddresseeCity());

        // Print the actual text
        QString text = getGreeting();
        text += "\n\n";
        text += m_view.getText();
        int y = vmar + 80*mmy;
        if (m_model.hasConclusion())
        {
            QRect textRect(QPoint(hmar, y),
                           QPoint(printer->paperRect().right() - hmar, vmar + 125*mmy));
            painter.drawText(textRect, text, Qt::AlignLeft|Qt::AlignTop);

            // Print test results
            font.setPointSize(13);
            font.setBold(true);
            font.setUnderline(true);
            painter.setFont(font);
            lineheight = painter.fontMetrics().height();
            y = vmar + 135*mmy;
            painter.drawText(hmar, y, tr("Test results:"));
            y += 2*lineheight;
            const Model::Measurements &measurementsModel = file.getMeasurements();
            View::Measurements measurementsView(0);
            measurementsView.setVisible(false);
            Presenter::Measurements measurementsPresenter(measurementsView, const_cast<Model::Measurements &>(measurementsModel));
            measurementsPresenter.setup();

            // Print pure tone audiometry
            font.setPointSize(12);
            font.setBold(false);
            font.setItalic(true);
            font.setUnderline(false);
            painter.setFont(font);
            lineheight = painter.fontMetrics().height();
            painter.drawText(hmar, y, tr("Pure tone audiometry: right"));
            painter.drawText(hmar + 120*mmx, y, tr("Pure tone audiometry: left"));
            y += lineheight;
            painter.drawPixmap(hmar, y, 90*mmx, 90*mmy, measurementsView.getPureToneAudiometryRight());
            painter.drawPixmap(hmar + 120*mmx, y, 90*mmx, 90*mmy, measurementsView.getPureToneAudiometryLeft());

            // Print average loss
            y += 95*mmy;
            font.setPointSize(10);
            font.setItalic(false);
            painter.setFont(font);
            lineheight = painter.fontMetrics().height();
            painter.drawText(hmar + 15*mmx, y, tr("Average loss") + "   " + measurementsView.getAverageLossRight());
            painter.drawText(hmar + 135*mmx, y, tr("Average loss") + "   " + measurementsView.getAverageLossLeft());

            // Print speech audiometry
            font.setPointSize(12);
            font.setItalic(true);
            painter.setFont(font);
            lineheight = painter.fontMetrics().height();
            y += 2*lineheight;
            painter.drawText(hmar, y, tr("Speech audiometry without hearing aid"));
            y += lineheight;
            painter.drawPixmap(hmar, y,  150*mmx, 60*mmy, measurementsView.getSpeechAudiometryWithoutAid());
            printer->newPage();
            y = vmar;
            painter.drawText(hmar, y, tr("Speech audiometry with hearing aid"));
            y += lineheight;
            painter.drawPixmap(hmar, y, 150*mmx, 60*mmy, measurementsView.getSpeechAudiometryWithAid());

            // Print table with the results
            y += 75*mmy;
            painter.drawText(hmar, y, tr("Prosthetic gain"));
            y += lineheight;
            painter.drawLine(hmar, y+lineheight+2*mmy, hmar, y+4*lineheight+8*mmy);
            painter.drawLine(hmar+45*mmx, y, hmar+45*mmx, y+4*lineheight+8*mmy);
            painter.drawLine(hmar+70*mmx, y, hmar+70*mmx, y+4*lineheight+8*mmy);
            painter.drawLine(hmar+95*mmx, y, hmar+95*mmx, y+4*lineheight+8*mmy);
            painter.drawLine(hmar+120*mmx, y, hmar+120*mmx, y+4*lineheight+8*mmy);
            painter.drawLine(hmar+45*mmx, y, hmar+120*mmx, y);
            y += lineheight;
            painter.drawText(hmar+52*mmx, y, tr("- H.A."));
            painter.drawText(hmar+72*mmx, y, tr("+ H.A."));
            painter.drawText(hmar+102*mmx, y, tr("gain"));
            y += 2*mmy;
            painter.drawLine(hmar, y, hmar+120*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, tr("right"));
            painter.drawText(hmar+52*mmx, y, measurementsView.getREWithout());
            painter.drawText(hmar+77*mmx, y, measurementsView.getREWith());
            painter.drawText(hmar+102*mmx, y, measurementsView.getREGain());
            y += 2*mmy;
            painter.drawLine(hmar, y, hmar+120*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, tr("left"));
            painter.drawText(hmar+52*mmx, y, measurementsView.getLEWithout());
            painter.drawText(hmar+77*mmx, y, measurementsView.getLEWith());
            painter.drawText(hmar+102*mmx, y, measurementsView.getLEGain());
            y += 2*mmy;
            painter.drawLine(hmar, y, hmar+120*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, tr("bilateral"));
            painter.drawText(hmar+52*mmx, y, measurementsView.getRELEWithout());
            painter.drawText(hmar+77*mmx, y, measurementsView.getRELEWith());
            painter.drawText(hmar+102*mmx, y, measurementsView.getRELEGain());
            y += 2*mmy;
            painter.drawLine(hmar, y, hmar+120*mmx, y);

            // Print localization tests for stereophonic adjustments
            if (file.getNofHearingAids() == 2)
            {
                y += 2*lineheight;
                painter.drawText(hmar, y, tr("Localization tests"));
                y += lineheight;
                painter.drawLine(hmar, y, hmar, y+4*lineheight + 8*mmy);
                painter.drawLine(hmar+70*mmx, y, hmar+70*mmx, y+4*lineheight + 8*mmy);
                painter.drawLine(hmar+100*mmx, y, hmar+100*mmx, y+4*lineheight + 8*mmy);
                painter.drawLine(hmar, y, hmar+100*mmx, y);
                y += lineheight;
                painter.drawText(hmar+2*mmx, y, tr("Without hearing aids"));
                painter.drawText(hmar+75*mmx, y, QString::number(measurementsView.getLocalizationWithout()) + " %");
                y += 2*mmx;
                painter.drawLine(hmar, y, hmar+100*mmx, y);
                y += lineheight;
                painter.drawText(hmar+2*mmx, y, tr("With 1 hearing aid (right)"));
                painter.drawText(hmar+75*mmx, y, QString::number(measurementsView.getLocalizationRight()) + " %");
                y += 2*mmx;
                painter.drawLine(hmar, y, hmar+100*mmx, y);
                y += lineheight;
                painter.drawText(hmar+2*mmx, y, tr("With 1 hearing aid (left)"));
                painter.drawText(hmar+75*mmx, y, QString::number(measurementsView.getLocalizationLeft()) + " %");
                y += 2*mmx;
                painter.drawLine(hmar, y, hmar+100*mmx, y);
                y += lineheight;
                painter.drawText(hmar+2*mmx, y, tr("With 2 hearing aids"));
                painter.drawText(hmar+75*mmx, y, QString::number(measurementsView.getLocalizationBoth()) + " %");
                y += 2*mmx;
                painter.drawLine(hmar, y, hmar+100*mmx, y);
            }

            // Print the conclusion
            y += 3*lineheight;
            font.setPointSize(13);
            font.setBold(true);
            font.setItalic(false);
            font.setUnderline(true);
            painter.setFont(font);
            lineheight = painter.fontMetrics().height();
            painter.drawText(hmar, y, tr("Conclusion:"));
            y += lineheight;
            font.setPointSize(12);
            font.setBold(false);
            font.setUnderline(false);
            painter.setFont(font);
            text = m_view.getConclusion() + "\n\n";
        }

        text += "\n\n";
        text += tr("Kind regards,") + "\n\n";
        text += settings.getName();
        QRect textRect = QRect(QPoint(hmar, y),
                               QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(textRect, text, Qt::AlignLeft|Qt::AlignTop);
    }
}
