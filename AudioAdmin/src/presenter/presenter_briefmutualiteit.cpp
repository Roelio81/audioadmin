#include "presenter_briefmutualiteit.h"
#include "../model/model_briefmutualiteit.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_mutualiteit.h"
#include "../model/model_universum.h"
#include "../view/view_briefmutualiteit.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

BriefMutualiteit::BriefMutualiteit(View::BriefMutualiteit &view, Model::BriefMutualiteit &model)
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

    Q_ASSERT(dossier.getMutualiteit() >= 0);
    Model::Mutualiteit *mutualiteit = dossier.getUniversum().getMutualiteit(dossier.getMutualiteit());
    Q_ASSERT(mutualiteit);
    m_view.setMutualiteitNaam(mutualiteit->getNaam());
    m_view.setMutualiteitStraat(mutualiteit->getStraat());
    m_view.setMutualiteitGemeente(QString::number(mutualiteit->getPostcode()) + " " + mutualiteit->getGemeente());

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
    m_view.setTekst(tekst);
    QString besluit = m_model.getConclusie();
    if (besluit.isEmpty())
        besluit = "Indien u nog vragen hebt, kan u mij bereiken op bovenstaand nummer.";
    m_view.setBesluit(besluit);

    connect(m_view.b_afdrukken, SIGNAL(clicked()), this, SLOT(print()));
    connect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    connect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
}

void BriefMutualiteit::teardown()
{
    m_model.setPostdatum(m_view.getPostdatum());
    m_model.setTekstblok(m_view.getTekst());
    m_model.setConclusie(m_view.getBesluit());

    disconnect(m_view.b_afdrukken, SIGNAL(clicked()), this, SLOT(print()));
    disconnect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    disconnect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
}

void BriefMutualiteit::print()
{
}
