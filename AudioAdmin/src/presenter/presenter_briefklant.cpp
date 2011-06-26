#include "presenter_briefklant.h"
#include "../model/model_briefklant.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_klant.h"
#include "../model/model_universum.h"
#include "../view/view_letter.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefKlant::BriefKlant(View::Letter &view, Model::BriefKlant &model)
    : m_view(view)
    , m_model(model)
{
}

BriefKlant::~BriefKlant()
{
}

void BriefKlant::setup()
{
    const Model::Dossier &dossier = m_model.getDossier();
    const Model::Klant &klant = dossier.getKlant();
    const Model::Instellingen &instellingen = dossier.getUniversum().getInstellingen();
    bool klantIsMan = (klant.getAanspreektitel() == "Dhr.");

    m_view.setGreeting(klantIsMan ? "Geachte meneer," : "Geachte mevrouw,");
    m_view.setAddresseeName(klant.getNaam() + " " + klant.getVoornaam());
    m_view.setAddresseeStreet(klant.getStraat());
    m_view.setAddresseeCity(QString::number(klant.getPostcode()) + " " + klant.getGemeente());
    m_view.setSenderName(instellingen.getNaam());
    m_view.setSenderStreet(instellingen.getStraat());
    m_view.setSenderCity(QString::number(instellingen.getPostcode()) + " " + instellingen.getGemeente());
    m_view.setSenderTelephone(instellingen.getTelefoon());
    m_view.setSenderMobilePhone(instellingen.getGsm());

    QString postalDate = m_model.getPostdatum();
    if (postalDate.isEmpty())
        postalDate = instellingen.getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_view.setPostalDate(postalDate);
    QString tekst = m_model.getTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u een overschrijving voor de opleg van ";
        if (dossier.getAantalHoorapparaten() == 1)
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
    m_model.setPostdatum(m_view.getPostalDate());
    m_model.setTekstblok(m_view.getText());

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefKlant::print()
{
    const Model::Dossier &dossier = m_model.getDossier();
    const Model::Klant &klant = dossier.getKlant();
    const Model::Instellingen &instellingen = dossier.getUniversum().getInstellingen();

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
        painter.drawText(hmar, vmar, instellingen.getNaam());
        font.setPointSize(11);
        font.setBold(false);
        painter.setFont(font);
        int lineheight = painter.fontMetrics().height();
        painter.drawText(hmar, vmar + (3*lineheight)/2, instellingen.getOnderschrift());
        painter.drawText(hmar, vmar + (5*lineheight)/2, instellingen.getStraat());
        painter.drawText(hmar, vmar + (7*lineheight)/2, QString::number(instellingen.getPostcode()) + " " + instellingen.getGemeente());
        painter.drawText(hmar, vmar + (9*lineheight)/2, QString("Riziv: ") + instellingen.getRiziv());
        painter.drawText(150*mmx, vmar + (5*lineheight)/2, QString("tel: ") + instellingen.getTelefoon());
        painter.drawText(150*mmx, vmar + (7*lineheight)/2, QString("gsm: ") + instellingen.getGsm());
        painter.drawText(150*mmx, vmar + (9*lineheight)/2, QString("e-mail: ") + instellingen.getEmail());
        painter.drawLine(printer->paperRect().left(), 52*mmy, printer->paperRect().right(), 52*mmy);

        // Print the postal date
        painter.drawText(hmar, 62*mmy, m_view.getPostalDate());

        // Print the client's address
        font.setPointSize(12);
        font.setItalic(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(150*mmx, 62*mmy + (0*lineheight), klant.getAanspreektitel() + " " + klant.getNaam() + " " + klant.getVoornaam());
        painter.drawText(150*mmx, 62*mmy + (1*lineheight), klant.getStraat());
        painter.drawText(150*mmx, 62*mmy + (2*lineheight), QString::number(klant.getPostcode()) + " " + klant.getGemeente());

        // Print the actual text
        bool klantIsMan = (klant.getAanspreektitel() == "Dhr.");
        QString tekst = klantIsMan ? "Geachte meneer," : "Geachte mevrouw,";
        tekst += "\n\n";
        tekst += m_view.getText();
        tekst += "\n\n";
        tekst += "Vriendelijke groeten, \n\n";
        tekst += instellingen.getNaam();
        QRect tekstRect(QPoint(hmar, vmar + (17*lineheight)),
                        QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);
    }
}
