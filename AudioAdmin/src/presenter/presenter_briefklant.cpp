#include "presenter_briefklant.h"
#include "../model/model_briefklant.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_klant.h"
#include "../model/model_universum.h"
#include "../view/view_briefklant.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefKlant::BriefKlant(View::BriefKlant &view, Model::BriefKlant &model)
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

    m_view.setAanspreking(klantIsMan ? "Geachte meneer," : "Geachte mevrouw,");
    m_view.setKlantNaam(klant.getNaam() + " " + klant.getVoornaam());
    m_view.setKlantStraat(klant.getStraat());
    m_view.setKlantGemeente(QString::number(klant.getPostcode()) + " " + klant.getGemeente());
    m_view.setAudioloogNaam(instellingen.getNaam());
    m_view.setAudioloogStraat(instellingen.getStraat());
    m_view.setAudioloogGemeente(QString::number(instellingen.getPostcode()) + " " + instellingen.getGemeente());
    m_view.setAudioloogTelefoon(instellingen.getTelefoon());
    m_view.setAudioloogGSM(instellingen.getGsm());

    QString postDatum = m_model.getPostdatum();
    if (postDatum.isEmpty())
        postDatum = instellingen.getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_view.setPostdatum(postDatum);
    QString tekst = m_model.getTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u de nodige documenten voor het ziekenfonds. Tevens vindt u 2 ";
        tekst += "overschrijvingsformulieren, waarvan 1 voor ";
        if (dossier.getAantalHoorapparaten() == 1)
            tekst += "het hoorapparaat";
        else
            tekst += "de hoorapparaten";
        tekst += ", incl. ... jaar garantie. Indien u 5 jaar garantie wenst, kan u het tweede ";
        tekst += "overschrijvingsformulier gebruiken.";
    }
    m_view.setTekst(tekst);

    connect(m_view.b_afdrukken, SIGNAL(clicked()), this, SLOT(print()));
    connect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    connect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
}

void BriefKlant::teardown()
{
    m_model.setPostdatum(m_view.getPostdatum());
    m_model.setTekstblok(m_view.getTekst());

    disconnect(m_view.b_afdrukken, SIGNAL(clicked()), this, SLOT(print()));
    disconnect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    disconnect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
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
        const int hmar = 25*mmx;
        const int vmar = 20*mmy;

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
        painter.drawText(hmar, 62*mmy, m_view.getPostdatum());

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
        tekst += m_view.getTekst();
        tekst += "\n\n";
        tekst += "Vriendelijke groeten, \n\n";
        tekst += instellingen.getNaam();
        QRect tekstRect(QPoint(hmar, vmar + (17*lineheight)),
                        QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);
    }
}
