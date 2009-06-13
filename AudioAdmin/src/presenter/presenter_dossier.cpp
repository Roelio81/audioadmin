#include "presenter_dossier.h"
#include "../model/model_arts.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_mutualiteit.h"
#include "../model/model_universum.h"
#include "../view/view_dossier.h"
#include "../view/view_briefarts.h"
#include "../view/view_briefklant.h"
#include "../view/view_briefmutualiteit.h"
#include "../view/view_factuur.h"
#include "../view/view_meetgegevens.h"

using namespace Presenter;

Dossier::Dossier(View::Dossier &view, Model::Dossier &model)
: m_view(view)
, m_model(model)
, m_universum(0)
, m_briefArts(0)
, m_briefKlant(0)
, m_briefMutualiteit(0)
, m_factuur(0)
, m_meetgegevens(0)
{
    connect(&m_view, SIGNAL(briefArtsTonen()), this, SLOT(briefArtsTonen()));
    connect(&m_view, SIGNAL(briefKlantTonen()), this, SLOT(briefKlantTonen()));
    connect(&m_view, SIGNAL(briefMutualiteitTonen()), this, SLOT(briefMutualiteitTonen()));
    connect(&m_view, SIGNAL(factuurTonen()), this, SLOT(factuurTonen()));
    connect(&m_view, SIGNAL(meetgegevensTonen()), this, SLOT(meetgegevensTonen()));
}

Dossier::~Dossier()
{
}

void Dossier::attachToUniversum(Model::Universum *universum)
{
    m_universum = universum;
}

void Dossier::detachFromUniversum()
{
    m_universum = 0;
}

void Dossier::setup()
{
    Model::Klant &klantModel = m_model.getKlant();
    m_view.leegAanspreektitels();
    m_view.toevoegenAanspreektitel("Dhr.");
    m_view.toevoegenAanspreektitel("Mevr.");
    m_view.setAanspreektitel(klantModel.getAanspreektitel());
    m_view.setNaam(klantModel.getNaam());
    m_view.setVoornaam(klantModel.getVoornaam());
    m_view.setStraat(klantModel.getStraat());
    m_view.setPostcode(klantModel.getPostcode());
    m_view.setGemeente(klantModel.getGemeente());
    m_view.setTelefoon(klantModel.getTelefoon());
    m_view.setGeboorteDatum(klantModel.getGeboorteDatum());
    m_view.setOpmerkingen(klantModel.getOpmerkingen());
    m_view.setMutualiteit(m_model.getMutualiteit());
    m_view.setAansluitingsnummer(m_model.getAansluitingsnummer());
    m_view.setPlaatsAanpassing(m_model.getPlaatsAanpassing());
    m_view.setArts(m_model.getArts());
    m_view.setRechterHoorapparaatMerk(m_model.getRechterHoorapparaatMerk());
    m_view.setRechterHoorapparaatType(m_model.getRechterHoorapparaatType());
    m_view.setLinkerHoorapparaatMerk(m_model.getLinkerHoorapparaatMerk());
    m_view.setLinkerHoorapparaatType(m_model.getLinkerHoorapparaatType());
    m_view.setOnderzoekDatum(m_model.getOnderzoekDatum());
    m_view.setProefDatum(m_model.getProefDatum());
    m_view.setNKORapportDatum(m_model.getNKORapportDatum());
    m_view.setDokterAdviesDatum(m_model.getDokterAdviesDatum());
    m_view.setAkkoordMutualiteitDatum(m_model.getAkkoordMutualiteitDatum());
    m_view.setBetalingDatum(m_model.getBetalingDatum());
    m_view.setAfleveringDatum(m_model.getAfleveringDatum());
    m_view.setWisselDatum(m_model.getWisselDatum());
    m_view.setOHKDatum(m_model.getOHKDatum());
}

void Dossier::setupBriefArts()
{
    bool klantIsMan = (m_model.getKlant().getAanspreektitel() == "Dhr.");

    Q_ASSERT(m_briefArts);
    Q_ASSERT(m_universum);
    Q_ASSERT(m_model.getArts() >= 0);
    Model::Arts *arts = m_universum->getArts(m_model.getArts());
    Q_ASSERT(arts);
    m_briefArts->setArtsNaam(arts->getNaam() + " " + arts->getVoornaam());
    m_briefArts->setArtsStraat(arts->getStraat());
    m_briefArts->setArtsGemeente(QString::number(arts->getPostcode()) + " " + arts->getGemeente());

    Model::Instellingen *instellingen = m_universum->getInstellingen();
    Q_ASSERT(instellingen);
    m_briefArts->setAudioloogNaam(instellingen->getNaam());
    m_briefArts->setAudioloogStraat(instellingen->getStraat());
    m_briefArts->setAudioloogGemeente(QString::number(instellingen->getPostcode()) + " " + instellingen->getGemeente());
    m_briefArts->setAudioloogTelefoon(instellingen->getTelefoon());
    m_briefArts->setAudioloogGSM(instellingen->getGsm());

    QString postDatum = m_model.getBriefArtsPostdatum();
    if (postDatum.isEmpty())
        postDatum = instellingen->getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_briefArts->setPostdatum(postDatum);
    QString tekst = m_model.getBriefArtsTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u het proefrapport ter gehoorcorrectie van ";
        tekst += (klantIsMan ? "mijnheer " : "mevrouw ") + m_model.getKlant().getNaam() + " " + m_model.getKlant().getVoornaam();
        tekst += " (geboortedatum: " + m_model.getKlant().getGeboorteDatum().toString("dd-MM-yyyy") + "). ";
        if (m_model.getAantalHoorapparaten() > 0)
        {
            tekst += (klantIsMan ? QString("Mijnheer ") : QString("Mevrouw ")) + "heeft geopteerd voor een ";
            if (m_model.getAantalHoorapparaten() == 1)
            {
                tekst += "mono aanpassing met ";
                if (!m_model.getLinkerHoorapparaatMerk().isEmpty() || !m_model.getLinkerHoorapparaatType().isEmpty())
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + " (links). ";
                }
                else
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getRechterHoorapparaatMerk() + " " + m_model.getRechterHoorapparaatType() + " (rechts). ";
                }
            }
            else
            {
                Q_ASSERT(m_model.getAantalHoorapparaten() == 2);
                tekst += "stereo aanpassing met ";
                if (m_model.getLinkerHoorapparaatMerk() == m_model.getRechterHoorapparaatMerk() &&
                    m_model.getLinkerHoorapparaatType() == m_model.getRechterHoorapparaatType())
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + ". ";
                }
                else
                {
                    tekst += "de apparaten ";
                    tekst += m_model.getRechterHoorapparaatMerk() + " " + m_model.getRechterHoorapparaatType() + " (rechts) en ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + " (links). ";
                }
            }
        }
    }
    m_briefArts->setTekst(tekst);
    QString besluit = m_model.getBriefArtsConclusie();
    if (besluit.isEmpty())
        besluit = "Indien u nog vragen hebt, kan u mij bereiken op bovenstaand nummer.";
    m_briefArts->setBesluit(besluit);

    connect(m_briefArts, SIGNAL(briefArtsSluiten()), this, SLOT(briefArtsSluiten()));
    connect(m_briefArts, SIGNAL(briefArtsBewaren()), this, SLOT(briefArtsBewaren()));
}

void Dossier::setupBriefKlant()
{
    bool klantIsMan = (m_model.getKlant().getAanspreektitel() == "Dhr.");

    Q_ASSERT(m_briefKlant);
    m_briefKlant->setAanspreking(klantIsMan ? "Geachte meneer," : "Geachte mevrouw,");
    m_briefKlant->setKlantNaam(m_model.getKlant().getNaam() + " " + m_model.getKlant().getVoornaam());
    m_briefKlant->setKlantStraat(m_model.getKlant().getStraat());
    m_briefKlant->setKlantGemeente(QString::number(m_model.getKlant().getPostcode()) + " " + m_model.getKlant().getGemeente());

    Q_ASSERT(m_universum);
    Model::Instellingen *instellingen = m_universum->getInstellingen();
    Q_ASSERT(instellingen);
    m_briefKlant->setAudioloogNaam(instellingen->getNaam());
    m_briefKlant->setAudioloogStraat(instellingen->getStraat());
    m_briefKlant->setAudioloogGemeente(QString::number(instellingen->getPostcode()) + " " + instellingen->getGemeente());
    m_briefKlant->setAudioloogTelefoon(instellingen->getTelefoon());
    m_briefKlant->setAudioloogGSM(instellingen->getGsm());

    QString postDatum = m_model.getBriefKlantPostdatum();
    if (postDatum.isEmpty())
        postDatum = instellingen->getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_briefKlant->setPostdatum(postDatum);
    QString tekst = m_model.getBriefKlantTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u de nodige documenten voor het ziekenfonds. Tevens vindt u 2 ";
        tekst += "overschrijvingsformulieren, waarvan 1 voor ";
        if (m_model.getAantalHoorapparaten() == 1)
            tekst += "het hoorapparaat";
        else
            tekst += "de hoorapparaten";
        tekst += ", incl. ... jaar garantie. Indien u 5 jaar garantie wenst, kan u het tweede ";
        tekst += "overschrijvingsformulier gebruiken.";
    }
    m_briefKlant->setTekst(tekst);

    connect(m_briefKlant, SIGNAL(briefKlantSluiten()), this, SLOT(briefKlantSluiten()));
    connect(m_briefKlant, SIGNAL(briefKlantBewaren()), this, SLOT(briefKlantBewaren()));
}

void Dossier::setupBriefMutualiteit()
{
    bool klantIsMan = (m_model.getKlant().getAanspreektitel() == "Dhr.");

    Q_ASSERT(m_briefMutualiteit);
    Q_ASSERT(m_universum);
    Q_ASSERT(m_model.getMutualiteit() >= 0);
    Model::Mutualiteit *mutualiteit = m_universum->getMutualiteit(m_model.getMutualiteit());
    Q_ASSERT(mutualiteit);
    m_briefMutualiteit->setMutualiteitNaam(mutualiteit->getNaam());
    m_briefMutualiteit->setMutualiteitStraat(mutualiteit->getStraat());
    m_briefMutualiteit->setMutualiteitGemeente(QString::number(mutualiteit->getPostcode()) + " " + mutualiteit->getGemeente());

    Model::Instellingen *instellingen = m_universum->getInstellingen();
    Q_ASSERT(instellingen);
    m_briefMutualiteit->setAudioloogNaam(instellingen->getNaam());
    m_briefMutualiteit->setAudioloogStraat(instellingen->getStraat());
    m_briefMutualiteit->setAudioloogGemeente(QString::number(instellingen->getPostcode()) + " " + instellingen->getGemeente());
    m_briefMutualiteit->setAudioloogTelefoon(instellingen->getTelefoon());
    m_briefMutualiteit->setAudioloogGSM(instellingen->getGsm());

    QString postDatum = m_model.getBriefMutualiteitPostdatum();
    if (postDatum.isEmpty())
        postDatum = instellingen->getGemeente() + ", " + QDate::currentDate().toString("dd-MM-yyyy");
    m_briefMutualiteit->setPostdatum(postDatum);
    QString tekst = m_model.getBriefMutualiteitTekstblok();
    if (tekst.isEmpty())
    {
        tekst = "Ingesloten vindt u het proefrapport ter gehoorcorrectie van ";
        tekst += (klantIsMan ? "mijnheer " : "mevrouw ") + m_model.getKlant().getNaam() + " " + m_model.getKlant().getVoornaam();
        tekst += " (geboortedatum: " + m_model.getKlant().getGeboorteDatum().toString("dd-MM-yyyy") + "). ";
        if (m_model.getAantalHoorapparaten() > 0)
        {
            tekst += (klantIsMan ? QString("Mijnheer ") : QString("Mevrouw ")) + "heeft geopteerd voor een ";
            if (m_model.getAantalHoorapparaten() == 1)
            {
                tekst += "mono aanpassing met ";
                if (!m_model.getLinkerHoorapparaatMerk().isEmpty() || !m_model.getLinkerHoorapparaatType().isEmpty())
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + " (links). ";
                }
                else
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getRechterHoorapparaatMerk() + " " + m_model.getRechterHoorapparaatType() + " (rechts). ";
                }
            }
            else
            {
                Q_ASSERT(m_model.getAantalHoorapparaten() == 2);
                tekst += "stereo aanpassing met ";
                if (m_model.getLinkerHoorapparaatMerk() == m_model.getRechterHoorapparaatMerk() &&
                    m_model.getLinkerHoorapparaatType() == m_model.getRechterHoorapparaatType())
                {
                    tekst += "het apparaat ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + ". ";
                }
                else
                {
                    tekst += "de apparaten ";
                    tekst += m_model.getRechterHoorapparaatMerk() + " " + m_model.getRechterHoorapparaatType() + " (rechts) en ";
                    tekst += m_model.getLinkerHoorapparaatMerk() + " " + m_model.getLinkerHoorapparaatType() + " (links). ";
                }
            }
        }
        tekst += "Gelieve ten spoedigste een goedkeuring te laten geworden op bovenstaan adres.";
    }
    m_briefMutualiteit->setTekst(tekst);
    QString besluit = m_model.getBriefMutualiteitConclusie();
    if (besluit.isEmpty())
        besluit = "Indien u nog vragen hebt, kan u mij bereiken op bovenstaand nummer.";
    m_briefMutualiteit->setBesluit(besluit);

    connect(m_briefMutualiteit, SIGNAL(briefMutualiteitSluiten()), this, SLOT(briefMutualiteitSluiten()));
    connect(m_briefMutualiteit, SIGNAL(briefMutualiteitBewaren()), this, SLOT(briefMutualiteitBewaren()));
}

void Dossier::setupFactuur()
{
    Q_ASSERT(m_factuur);
    connect(m_factuur, SIGNAL(factuurSluiten()), this, SLOT(factuurSluiten()));
}

void Dossier::setupMeetgegevens()
{
    Q_ASSERT(m_meetgegevens);
    Model::Meetgegevens &model = m_model.getMeetgegevens();
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        m_meetgegevens->setLGRechtsData(Hz[i], model.getLGRechtsData(Hz[i]));
        m_meetgegevens->setBGRechtsData(Hz[i], model.getBGRechtsData(Hz[i]));
        m_meetgegevens->setUCLRechtsData(Hz[i], model.getUCLRechtsData(Hz[i]));
        m_meetgegevens->setLGLinksData(Hz[i], model.getLGLinksData(Hz[i]));
        m_meetgegevens->setBGLinksData(Hz[i], model.getBGLinksData(Hz[i]));
        m_meetgegevens->setUCLLinksData(Hz[i], model.getUCLLinksData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        m_meetgegevens->setROZonderData(5*i, model.getROZonderData(5*i));
        m_meetgegevens->setLOZonderData(5*i, model.getLOZonderData(5*i));
        m_meetgegevens->setROLOZonderData(5*i, model.getROLOZonderData(5*i));
        m_meetgegevens->setROMetData(5*i, model.getROMetData(5*i));
        m_meetgegevens->setLOMetData(5*i, model.getLOMetData(5*i));
        m_meetgegevens->setROLOMetData(5*i, model.getROLOMetData(5*i));
    }
    m_meetgegevens->setLocalisatieZonder(model.getLocalisatieZonder());
    m_meetgegevens->setLocalisatieRechts(model.getLocalisatieRechts());
    m_meetgegevens->setLocalisatieLinks(model.getLocalisatieLinks());
    m_meetgegevens->setLocalisatieBeide(model.getLocalisatieBeide());
    connect(m_meetgegevens, SIGNAL(meetgegevensSluiten()), this, SLOT(meetgegevensSluiten()));
    connect(m_meetgegevens, SIGNAL(meetgegevensBewaren()), this, SLOT(meetgegevensBewaren()));
}

void Dossier::briefArtsTonen()
{
    if (!m_briefArts)
    {
        m_briefArts = new View::BriefArts(m_view.getParentWindow());
    }

    setupBriefArts();
    m_briefArts->show();
}

void Dossier::briefArtsSluiten()
{
    Q_ASSERT(m_briefArts);
    m_briefArts->close();
    m_briefArts = 0;
}

void Dossier::briefArtsBewaren()
{
    Q_ASSERT(m_briefArts);
    m_model.setBriefArtsPostdatum(m_briefArts->getPostdatum());
    m_model.setBriefArtsTekstblok(m_briefArts->getTekst());
    m_model.setBriefArtsConclusie(m_briefArts->getBesluit());
}

void Dossier::briefKlantTonen()
{
    if (!m_briefKlant)
    {
        m_briefKlant = new View::BriefKlant(m_view.getParentWindow());
    }

    setupBriefKlant();
    m_briefKlant->show();
}

void Dossier::briefKlantSluiten()
{
    Q_ASSERT(m_briefKlant);
    m_briefKlant->close();
    m_briefKlant = 0;
}

void Dossier::briefKlantBewaren()
{
    Q_ASSERT(m_briefKlant);
    m_model.setBriefKlantPostdatum(m_briefKlant->getPostdatum());
    m_model.setBriefKlantTekstblok(m_briefKlant->getTekst());
}

void Dossier::briefMutualiteitTonen()
{
    if (!m_briefMutualiteit)
    {
        m_briefMutualiteit = new View::BriefMutualiteit(m_view.getParentWindow());
    }

    setupBriefMutualiteit();
    m_briefMutualiteit->show();
}

void Dossier::briefMutualiteitSluiten()
{
    Q_ASSERT(m_briefMutualiteit);
    m_briefMutualiteit->close();
    m_briefMutualiteit = 0;
}

void Dossier::briefMutualiteitBewaren()
{
    Q_ASSERT(m_briefMutualiteit);
    m_model.setBriefMutualiteitPostdatum(m_briefMutualiteit->getPostdatum());
    m_model.setBriefMutualiteitTekstblok(m_briefMutualiteit->getTekst());
    m_model.setBriefMutualiteitConclusie(m_briefMutualiteit->getBesluit());
}

void Dossier::factuurTonen()
{
    if (!m_factuur)
    {
        m_factuur = new View::Factuur(m_view.getParentWindow());
    }

    setupFactuur();
    m_factuur->show();
}

void Dossier::factuurSluiten()
{
    Q_ASSERT(m_factuur);
    m_factuur->close();
    m_factuur = 0;
}

void Dossier::meetgegevensTonen()
{
    if (!m_meetgegevens)
    {
        m_meetgegevens = new View::Meetgegevens(m_view.getParentWindow());
    }

    setupMeetgegevens();
    m_meetgegevens->show();
}

void Dossier::meetgegevensSluiten()
{
    Q_ASSERT(m_meetgegevens);
    m_meetgegevens->close();
    m_meetgegevens = 0;
}

void Dossier::meetgegevensBewaren()
{
    Q_ASSERT(m_meetgegevens);
    Model::Meetgegevens &model = m_model.getMeetgegevens();
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        model.setLGRechtsData(Hz[i], m_meetgegevens->getLGRechtsData(Hz[i]));
        model.setBGRechtsData(Hz[i], m_meetgegevens->getBGRechtsData(Hz[i]));
        model.setUCLRechtsData(Hz[i], m_meetgegevens->getUCLRechtsData(Hz[i]));
        model.setLGLinksData(Hz[i], m_meetgegevens->getLGLinksData(Hz[i]));
        model.setBGLinksData(Hz[i], m_meetgegevens->getBGLinksData(Hz[i]));
        model.setUCLLinksData(Hz[i], m_meetgegevens->getUCLLinksData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        model.setROZonderData(5*i, m_meetgegevens->getROZonderData(5*i));
        model.setLOZonderData(5*i, m_meetgegevens->getLOZonderData(5*i));
        model.setROLOZonderData(5*i, m_meetgegevens->getROLOZonderData(5*i));
        model.setROMetData(5*i, m_meetgegevens->getROMetData(5*i));
        model.setLOMetData(5*i, m_meetgegevens->getLOMetData(5*i));
        model.setROLOMetData(5*i, m_meetgegevens->getROLOMetData(5*i));
    }
    model.setLocalisatieZonder(m_meetgegevens->getLocalisatieZonder());
    model.setLocalisatieRechts(m_meetgegevens->getLocalisatieRechts());
    model.setLocalisatieLinks(m_meetgegevens->getLocalisatieLinks());
    model.setLocalisatieBeide(m_meetgegevens->getLocalisatieBeide());
}
