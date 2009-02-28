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
    m_view.setMutualiteit(klantModel.getMutualiteit());
    m_view.setAansluitingsnummer(klantModel.getAansluitingsnummer());
    m_view.setPlaatsAanpassing(klantModel.getPlaatsAanpassing());
    m_view.setOpmerkingen(klantModel.getOpmerkingen());
    m_view.setArts(m_model.getArts());
}

void Dossier::setupBriefArts()
{
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

    connect(m_briefArts, SIGNAL(briefArtsSluiten()), this, SLOT(briefArtsSluiten()));
}

void Dossier::setupBriefKlant()
{
    Q_ASSERT(m_briefKlant);
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

    connect(m_briefKlant, SIGNAL(briefKlantSluiten()), this, SLOT(briefKlantSluiten()));
}

void Dossier::setupBriefMutualiteit()
{
    Q_ASSERT(m_briefMutualiteit);
    Q_ASSERT(m_universum);
    Q_ASSERT(m_model.getKlant().getMutualiteit() >= 0);
    Model::Mutualiteit *mutualiteit = m_universum->getMutualiteit(m_model.getKlant().getMutualiteit());
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

    connect(m_briefMutualiteit, SIGNAL(briefMutualiteitSluiten()), this, SLOT(briefMutualiteitSluiten()));
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
    connect(m_meetgegevens, SIGNAL(meetgegevensSluiten()), this, SLOT(meetgegevensSluiten()));
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
