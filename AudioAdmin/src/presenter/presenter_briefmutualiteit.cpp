#include "presenter_briefmutualiteit.h"
#include "presenter_measurements.h"
#include "../model/model_letter.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_insurancecompany.h"
#include "../model/model_universe.h"
#include "../view/view_letter.h"
#include "../view/view_measurements.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefMutualiteit::BriefMutualiteit(View::Letter &view, Model::Letter &model)
    : m_view(view)
    , m_model(model)
{
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::setup()
{
    const Model::File &file = m_model.getFile();
    const Model::Customer &customer = file.getCustomer();
    const Model::Settings &settings = file.getUniverse().getSettings();
    bool sex = (customer.getTitle() == "Dhr.");

    m_view.setGreeting("Geachte geneesheer-adviseur,");
    Q_ASSERT(file.getInsuranceCompany() >= 0);
    Model::InsuranceCompany *insuranceCompany = file.getUniverse().getInsuranceCompany(file.getInsuranceCompany());
    Q_ASSERT(insuranceCompany);
    m_view.setAddresseeName(insuranceCompany->getName());
    m_view.setAddresseeStreet(insuranceCompany->getStreet());
    m_view.setAddresseeCity(QString::number(insuranceCompany->getPostalCode()) + " " + insuranceCompany->getCity());
    m_view.setSenderName(settings.getName());
    m_view.setSenderStreet(settings.getStreet());
    m_view.setSenderCity(QString::number(settings.getPostalCode()) + " " + settings.getCity());
    m_view.setSenderTelephone(settings.getTelephone());
    m_view.setSenderMobilePhone(settings.getMobilePhone());

    QString postalDate = m_model.getPostalDate();
    if (postalDate.isEmpty())
        postalDate = settings.getCity() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_view.setPostalDate(postalDate);
    QString text = m_model.getText();
    if (text.isEmpty())
    {
        text = "Ingesloten vindt u het proefrapport ter gehoorcorrectie van ";
        text += (sex ? "mijnheer " : "mevrouw ") + customer.getName() + " " + customer.getFirstName();
        QDate dateOfBirth = customer.getDateOfBirth();
        if (dateOfBirth != file.getUniverse().getInvalidDate())
        {
            text += " (" + QString(char(0xb0)) + " " + dateOfBirth.toString("dd-MM-yyyy") + "). ";
        }
        if (file.getAantalHoorapparaten() > 0)
        {
            text += (sex ? QString("Mijnheer ") : QString("Mevrouw ")) + "heeft geopteerd voor een ";
            if (file.getAantalHoorapparaten() == 1)
            {
                text += "monofonische aanpassing met ";
                if (!file.getLinkerHoorapparaatMerk().isEmpty() || !file.getLinkerHoorapparaatType().isEmpty())
                {
                    text += "het apparaat ";
                    text += file.getLinkerHoorapparaatMerk() + " " + file.getLinkerHoorapparaatType() + " (links). ";
                }
                else
                {
                    text += "het apparaat ";
                    text += file.getRechterHoorapparaatMerk() + " " + file.getRechterHoorapparaatType() + " (rechts). ";
                }
            }
            else
            {
                Q_ASSERT(file.getAantalHoorapparaten() == 2);
                text += "stereofonsiche aanpassing met ";
                if (file.getLinkerHoorapparaatMerk() == file.getRechterHoorapparaatMerk() &&
                    file.getLinkerHoorapparaatType() == file.getRechterHoorapparaatType())
                {
                    text += "het apparaat ";
                    text += file.getLinkerHoorapparaatMerk() + " " + file.getLinkerHoorapparaatType() + ". ";
                }
                else
                {
                    text += "de apparaten ";
                    text += file.getRechterHoorapparaatMerk() + " " + file.getRechterHoorapparaatType() + " (rechts) en ";
                    text += file.getLinkerHoorapparaatMerk() + " " + file.getLinkerHoorapparaatType() + " (links). ";
                }
            }
        }
        text += "Gelieve ten spoedigste een goedkeuring te laten geworden op bovenstaan adres.";
    }
    m_view.setText(text);
    QString conclusion = m_model.getConclusion();
    if (conclusion.isEmpty())
        conclusion = "Indien u nog vragen hebt, kan u mij bereiken op bovenstaand nummer.";
    m_view.setConclusion(conclusion);

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefMutualiteit::teardown()
{
    m_model.setPostalDate(m_view.getPostalDate());
    m_model.setText(m_view.getText());
    m_model.setConclusion(m_view.getConclusion());

    disconnect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefMutualiteit::print()
{
    const Model::File &file = m_model.getFile();
    const Model::InsuranceCompany *mutualiteit = file.getUniverse().getInsuranceCompany(file.getInsuranceCompany());
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
        painter.drawText(hmar, vmar + (9*lineheight)/2, QString("Riziv: ") + settings.getNationalId());
        painter.drawText(150*mmx, vmar + (5*lineheight)/2, QString("tel: ") + settings.getTelephone());
        painter.drawText(150*mmx, vmar + (7*lineheight)/2, QString("gsm: ") + settings.getMobilePhone());
        painter.drawText(150*mmx, vmar + (9*lineheight)/2, QString("e-mail: ") + settings.getEmail());
        painter.drawLine(printer->paperRect().left(), 52*mmy, printer->paperRect().right(), 52*mmy);

        // Print the postal date
        painter.drawText(hmar, 62*mmy, m_view.getPostalDate());

        // Print the insurance company's address
        font.setPointSize(12);
        font.setItalic(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(150*mmx, 62*mmy + (0*lineheight), mutualiteit->getName());
        painter.drawText(150*mmx, 62*mmy + (1*lineheight), mutualiteit->getStreet());
        painter.drawText(150*mmx, 62*mmy + (2*lineheight), QString::number(mutualiteit->getPostalCode()) + " " + mutualiteit->getCity());

        // Print the actual text
        QString tekst = "Geachte geneesheer-adviseur,";
        tekst += "\n\n";
        tekst += m_view.getText();
        int y = vmar + 80*mmy;
        QRect tekstRect(QPoint(hmar, y),
                        QPoint(printer->paperRect().right() - hmar, vmar + 125*mmy));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);

        // Print test results
        font.setPointSize(13);
        font.setBold(true);
        font.setUnderline(true);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        y = vmar + 135*mmy;
        painter.drawText(hmar, y, "Testresultaten:");
        y += 2*lineheight;
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(true);
        font.setUnderline(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(hmar, y, "Tonale audiometrie rechts");
        painter.drawText(hmar + 120*mmx, y, "Tonale audiometrie links");
        y += lineheight;

        // Print tonale audiometrie
        const Model::Measurements &meetgegevensModel = file.getMeasurements();
        View::Measurements meetgegevensView(0);
        meetgegevensView.setVisible(false);
        Presenter::Measurements meetgegevensPresenter(meetgegevensView, const_cast<Model::Measurements &>(meetgegevensModel));
        meetgegevensPresenter.setup();
        painter.drawPixmap(hmar, y, 90*mmx, 90*mmy, meetgegevensView.getTonaleRechts());
        painter.drawPixmap(hmar + 120*mmx, y, 90*mmx, 90*mmy, meetgegevensView.getTonaleLinks());

        // Print vocale audiometrie
        y += 100*mmy;
        painter.drawText(hmar, y, "Vocale audiometrie zonder hoorapparaat");
        y += lineheight;
        painter.drawPixmap(hmar, y,  150*mmx, 60*mmy, meetgegevensView.getVocaleZonderApparaat());
        printer->newPage();
        y = vmar;
        painter.drawText(hmar, y, "Vocale audiometrie met hoorapparaat");
        y += lineheight;
        painter.drawPixmap(hmar, y, 150*mmx, 60*mmy, meetgegevensView.getVocaleMetApparaat());

        // Print table with the results
        y += 75*mmy;
        painter.drawText(hmar, y, "Prothetische winst");
        y += lineheight;
        painter.drawLine(hmar, y+lineheight+2*mmy, hmar, y+4*lineheight+8*mmy);
        painter.drawLine(hmar+45*mmx, y, hmar+45*mmx, y+4*lineheight+8*mmy);
        painter.drawLine(hmar+70*mmx, y, hmar+70*mmx, y+4*lineheight+8*mmy);
        painter.drawLine(hmar+95*mmx, y, hmar+95*mmx, y+4*lineheight+8*mmy);
        painter.drawLine(hmar+120*mmx, y, hmar+120*mmx, y+4*lineheight+8*mmy);
        painter.drawLine(hmar+45*mmx, y, hmar+120*mmx, y);
        y += lineheight;
        painter.drawText(hmar+52*mmx, y, "- H.A.");
        painter.drawText(hmar+72*mmx, y, "+ H.A.");
        painter.drawText(hmar+102*mmx, y, "winst");
        y += 2*mmy;
        painter.drawLine(hmar, y, hmar+120*mmx, y);
        y += lineheight;
        painter.drawText(hmar+2*mmx, y, "rechts");
        painter.drawText(hmar+52*mmx, y, meetgegevensView.getROZonder());
        painter.drawText(hmar+77*mmx, y, meetgegevensView.getROMet());
        painter.drawText(hmar+102*mmx, y, meetgegevensView.getROWinst());
        y += 2*mmy;
        painter.drawLine(hmar, y, hmar+120*mmx, y);
        y += lineheight;
        painter.drawText(hmar+2*mmx, y, "links");
        painter.drawText(hmar+52*mmx, y, meetgegevensView.getLOZonder());
        painter.drawText(hmar+77*mmx, y, meetgegevensView.getLOMet());
        painter.drawText(hmar+102*mmx, y, meetgegevensView.getLOWinst());
        y += 2*mmy;
        painter.drawLine(hmar, y, hmar+120*mmx, y);
        y += lineheight;
        painter.drawText(hmar+2*mmx, y, "bilateraal");
        painter.drawText(hmar+52*mmx, y, meetgegevensView.getROLOZonder());
        painter.drawText(hmar+77*mmx, y, meetgegevensView.getROLOMet());
        painter.drawText(hmar+102*mmx, y, meetgegevensView.getROLOWinst());
        y += 2*mmy;
        painter.drawLine(hmar, y, hmar+120*mmx, y);

        // Print localization tests for stereophonic adjustments
        if (file.getAantalHoorapparaten() == 2)
        {
            y += 2*lineheight;
            painter.drawText(hmar, y, "Localisatie testen");
            y += lineheight;
            painter.drawLine(hmar, y, hmar, y+4*lineheight + 8*mmy);
            painter.drawLine(hmar+70*mmx, y, hmar+70*mmx, y+4*lineheight + 8*mmy);
            painter.drawLine(hmar+100*mmx, y, hmar+100*mmx, y+4*lineheight + 8*mmy);
            painter.drawLine(hmar, y, hmar+100*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, "Zonder apparaten");
            painter.drawText(hmar+75*mmx, y, QString::number(meetgegevensView.getLocalisatieZonder()) + " %");
            y += 2*mmx;
            painter.drawLine(hmar, y, hmar+100*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, "Met 1 apparaat (rechts)");
            painter.drawText(hmar+75*mmx, y, QString::number(meetgegevensView.getLocalisatieRechts()) + " %");
            y += 2*mmx;
            painter.drawLine(hmar, y, hmar+100*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, "Met 1 apparaat (links)");
            painter.drawText(hmar+75*mmx, y, QString::number(meetgegevensView.getLocalisatieLinks()) + " %");
            y += 2*mmx;
            painter.drawLine(hmar, y, hmar+100*mmx, y);
            y += lineheight;
            painter.drawText(hmar+2*mmx, y, "Met 2 apparaten");
            painter.drawText(hmar+75*mmx, y, QString::number(meetgegevensView.getLocalisatieBeide()) + " %");
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
        painter.drawText(hmar, y, "Besluit:");
        y += lineheight;
        font.setPointSize(12);
        font.setBold(false);
        font.setUnderline(false);
        painter.setFont(font);
        tekst = m_view.getConclusion() + "\n\n";
        tekst += "\n\n";
        tekst += "Vriendelijke groeten, \n\n";
        tekst += settings.getName();
        tekstRect = QRect(QPoint(hmar, y),
                          QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);
    }
}
