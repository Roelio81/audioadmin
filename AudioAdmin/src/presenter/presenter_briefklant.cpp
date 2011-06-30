#include "presenter_briefklant.h"
#include "../model/model_letter.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_customer.h"
#include "../model/model_universe.h"
#include "../view/view_letter.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefKlant::BriefKlant(View::Letter &view, Model::Letter &model)
    : m_view(view)
    , m_model(model)
{
}

BriefKlant::~BriefKlant()
{
}

void BriefKlant::setup()
{
    const Model::File &file = m_model.getFile();
    const Model::Customer &klant = file.getCustomer();
    const Model::Settings &instellingen = file.getUniverse().getSettings();
    bool sex = (klant.getTitle() == "Dhr.");

    m_view.setGreeting(sex ? "Geachte meneer," : "Geachte mevrouw,");
    m_view.setAddresseeName(klant.getName() + " " + klant.getFirstName());
    m_view.setAddresseeStreet(klant.getStreet());
    m_view.setAddresseeCity(QString::number(klant.getPostalCode()) + " " + klant.getCity());
    m_view.setSenderName(instellingen.getName());
    m_view.setSenderStreet(instellingen.getStreet());
    m_view.setSenderCity(QString::number(instellingen.getPostalCode()) + " " + instellingen.getCity());
    m_view.setSenderTelephone(instellingen.getTelephone());
    m_view.setSenderMobilePhone(instellingen.getMobilePhone());

    QString postalDate = m_model.getPostalDate();
    if (postalDate.isEmpty())
        postalDate = instellingen.getCity() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_view.setPostalDate(postalDate);
    QString tekst = m_model.getText();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u een overschrijving voor de opleg van ";
        if (file.getNofHearingAids() == 1)
            tekst += "het hoorapparaat.";
        else
            tekst += "de hoorapparaten.";
        tekst += "Tevens vindt u een tweede overschrijving die u kan gebruiken indien u 5 jaar garantie wenst i.p.v. ... jaar.";
    }
    m_view.setText(tekst);

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefKlant::teardown()
{
    m_model.setPostalDate(m_view.getPostalDate());
    m_model.setText(m_view.getText());

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefKlant::print()
{
    const Model::File &file = m_model.getFile();
    const Model::Customer &klant = file.getCustomer();
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

        // Print the client's address
        font.setPointSize(12);
        font.setItalic(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(150*mmx, 62*mmy + (0*lineheight), klant.getTitle() + " " + klant.getName() + " " + klant.getFirstName());
        painter.drawText(150*mmx, 62*mmy + (1*lineheight), klant.getStreet());
        painter.drawText(150*mmx, 62*mmy + (2*lineheight), QString::number(klant.getPostalCode()) + " " + klant.getCity());

        // Print the actual text
        bool klantIsMan = (klant.getTitle() == "Dhr.");
        QString tekst = klantIsMan ? "Geachte meneer," : "Geachte mevrouw,";
        tekst += "\n\n";
        tekst += m_view.getText();
        tekst += "\n\n";
        tekst += "Vriendelijke groeten, \n\n";
        tekst += settings.getName();
        QRect tekstRect(QPoint(hmar, vmar + (17*lineheight)),
                        QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);
    }
}
