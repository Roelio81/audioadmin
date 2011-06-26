#include "presenter_briefmutualiteit.h"
#include "presenter_meetgegevens.h"
#include "../model/model_briefmutualiteit.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_mutualiteit.h"
#include "../model/model_universum.h"
#include "../view/view_letter.h"
#include "../view/view_meetgegevens.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefMutualiteit::BriefMutualiteit(View::Letter &view, Model::BriefMutualiteit &model)
    : m_view(view)
    , m_model(model)
{
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::setup()
{
    const Model::Dossier &dossier = m_model.getDossier();
    const Model::Klant &klant = dossier.getKlant();
    const Model::Instellingen &instellingen = dossier.getUniversum().getInstellingen();
    bool klantIsMan = (klant.getAanspreektitel() == "Dhr.");

    m_view.setGreeting("Geachte geneesheer-adviseur,");
    Q_ASSERT(dossier.getMutualiteit() >= 0);
    Model::Mutualiteit *mutualiteit = dossier.getUniversum().getMutualiteit(dossier.getMutualiteit());
    Q_ASSERT(mutualiteit);
    m_view.setAddresseeName(mutualiteit->getNaam());
    m_view.setAddresseeStreet(mutualiteit->getStraat());
    m_view.setAddresseeCity(QString::number(mutualiteit->getPostcode()) + " " + mutualiteit->getGemeente());
    m_view.setSenderName(instellingen.getNaam());
    m_view.setSenderStreet(instellingen.getStraat());
    m_view.setSenderCity(QString::number(instellingen.getPostcode()) + " " + instellingen.getGemeente());
    m_view.setSenderTelephone(instellingen.getTelefoon());
    m_view.setSenderMobilePhone(instellingen.getGsm());

    QString postDatum = m_model.getPostdatum();
    if (postDatum.isEmpty())
        postDatum = instellingen.getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_view.setPostalDate(postDatum);
    QString tekst = m_model.getTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u het proefrapport ter gehoorcorrectie van ";
        tekst += (klantIsMan ? "mijnheer " : "mevrouw ") + klant.getNaam() + " " + klant.getVoornaam();
        QDate geboorteDatum = klant.getGeboorteDatum();
        if (geboorteDatum != dossier.getUniversum().getInvalidDate())
        {
            tekst += " (" + QString(char(0xb0)) + " " + geboorteDatum.toString("dd-MM-yyyy") + "). ";
        }
        if (dossier.getAantalHoorapparaten() > 0)
        {
            tekst += (klantIsMan ? QString("Mijnheer ") : QString("Mevrouw ")) + "heeft geopteerd voor een ";
            if (dossier.getAantalHoorapparaten() == 1)
            {
                tekst += "monofonische aanpassing met ";
                if (!dossier.getLinkerHoorapparaatMerk().isEmpty() || !dossier.getLinkerHoorapparaatType().isEmpty())
                {
                    tekst += "het apparaat ";
                    tekst += dossier.getLinkerHoorapparaatMerk() + " " + dossier.getLinkerHoorapparaatType() + " (links). ";
                }
                else
                {
                    tekst += "het apparaat ";
                    tekst += dossier.getRechterHoorapparaatMerk() + " " + dossier.getRechterHoorapparaatType() + " (rechts). ";
                }
            }
            else
            {
                Q_ASSERT(dossier.getAantalHoorapparaten() == 2);
                tekst += "stereofonsiche aanpassing met ";
                if (dossier.getLinkerHoorapparaatMerk() == dossier.getRechterHoorapparaatMerk() &&
                    dossier.getLinkerHoorapparaatType() == dossier.getRechterHoorapparaatType())
                {
                    tekst += "het apparaat ";
                    tekst += dossier.getLinkerHoorapparaatMerk() + " " + dossier.getLinkerHoorapparaatType() + ". ";
                }
                else
                {
                    tekst += "de apparaten ";
                    tekst += dossier.getRechterHoorapparaatMerk() + " " + dossier.getRechterHoorapparaatType() + " (rechts) en ";
                    tekst += dossier.getLinkerHoorapparaatMerk() + " " + dossier.getLinkerHoorapparaatType() + " (links). ";
                }
            }
        }
        tekst += "Gelieve ten spoedigste een goedkeuring te laten geworden op bovenstaan adres.";
    }
    m_view.setText(tekst);
    QString besluit = m_model.getConclusie();
    if (besluit.isEmpty())
        besluit = "Indien u nog vragen hebt, kan u mij bereiken op bovenstaand nummer.";
    m_view.setConclusion(besluit);

    connect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefMutualiteit::teardown()
{
    m_model.setPostdatum(m_view.getPostalDate());
    m_model.setTekstblok(m_view.getText());
    m_model.setConclusie(m_view.getConclusion());

    disconnect(&m_view, SIGNAL(print()), this, SLOT(print()));
}

void BriefMutualiteit::print()
{
    const Model::Dossier &dossier = m_model.getDossier();
    const Model::Mutualiteit *mutualiteit = dossier.getUniversum().getMutualiteit(dossier.getMutualiteit());
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

        // Print the insurance company's address
        font.setPointSize(12);
        font.setItalic(false);
        painter.setFont(font);
        lineheight = painter.fontMetrics().height();
        painter.drawText(150*mmx, 62*mmy + (0*lineheight), mutualiteit->getNaam());
        painter.drawText(150*mmx, 62*mmy + (1*lineheight), mutualiteit->getStraat());
        painter.drawText(150*mmx, 62*mmy + (2*lineheight), QString::number(mutualiteit->getPostcode()) + " " + mutualiteit->getGemeente());

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
        const Model::Meetgegevens &meetgegevensModel = dossier.getMeetgegevens();
        View::Meetgegevens meetgegevensView(0);
        meetgegevensView.setVisible(false);
        Presenter::Meetgegevens meetgegevensPresenter(meetgegevensView, const_cast<Model::Meetgegevens &>(meetgegevensModel));
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
        if (dossier.getAantalHoorapparaten() == 2)
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
        tekst += instellingen.getNaam();
        tekstRect = QRect(QPoint(hmar, y),
                          QPoint(printer->paperRect().right() - hmar, printer->paperRect().bottom() - vmar));
        painter.drawText(tekstRect, tekst, Qt::AlignLeft|Qt::AlignTop);
    }
}
