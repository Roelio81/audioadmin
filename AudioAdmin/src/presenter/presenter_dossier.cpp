#include "presenter_dossier.h"
#include "../model/model_dossier.h"
#include "../view/view_dossier.h"
#include "../view/view_briefarts.h"
#include "../view/view_briefklant.h"
#include "../view/view_briefmutualiteit.h"
#include "../view/view_factuur.h"
#include "../view/view_meetgegevens.h"

using namespace Presenter;

Dossier::Dossier(View::Dossier &view, Model::Dossier &model)
: QObject()
, m_view(view)
, m_model(model)
, m_briefArts(0)
, m_briefKlant(0)
, m_briefMutualiteit(0)
, m_factuur(0)
, m_meetgegevens(0)
{
    connect(&m_view, SIGNAL(briefArtsSignal()), this, SLOT(briefArtsTonen()));
    connect(&m_view, SIGNAL(briefKlantSignal()), this, SLOT(briefKlantTonen()));
    connect(&m_view, SIGNAL(briefMutualiteitSignal()), this, SLOT(briefMutualiteitTonen()));
    connect(&m_view, SIGNAL(factuurSignal()), this, SLOT(factuurTonen()));
    connect(&m_view, SIGNAL(meetgegevensSignal()), this, SLOT(meetgegevensTonen()));
}

Dossier::~Dossier()
{
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
}

void Dossier::setupBriefKlant()
{
}

void Dossier::setupBriefMutualiteit()
{
}

void Dossier::setupFactuur()
{
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
