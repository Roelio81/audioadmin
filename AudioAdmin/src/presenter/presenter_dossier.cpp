#include "presenter_dossier.h"
#include "presenter_briefarts.h"
#include "presenter_briefklant.h"
#include "presenter_briefmutualiteit.h"
#include "presenter_meetgegevens.h"
#include "../model/model_arts.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_mutualiteit.h"
#include "../model/model_universum.h"
#include "../view/view_dossier.h"
#include "../view/view_letter.h"
#include "../view/view_factuur.h"
#include "../view/view_meetgegevens.h"

using namespace Presenter;

Dossier::Dossier(View::Dossier &view, Model::Dossier &model)
: m_view(view)
, m_model(model)
, m_universum(0)
, m_factuur(0)
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
    m_view.setRechterHoorapparaatPrijs(m_model.getRechterHoorapparaatPrijs());
    m_view.setRechterHoorapparaatSerienummer(m_model.getRechterHoorapparaatSerienummer());
    m_view.setLinkerHoorapparaatMerk(m_model.getLinkerHoorapparaatMerk());
    m_view.setLinkerHoorapparaatType(m_model.getLinkerHoorapparaatType());
    m_view.setLinkerHoorapparaatPrijs(m_model.getLinkerHoorapparaatPrijs());
    m_view.setLinkerHoorapparaatSerienummer(m_model.getLinkerHoorapparaatSerienummer());
    m_view.setOnderzoekDatum(m_model.getOnderzoekDatum());
    m_view.setProefDatum(m_model.getProefDatum());
    m_view.setNKORapportDatum(m_model.getNKORapportDatum());
    m_view.setDokterAdviesDatum(m_model.getDokterAdviesDatum());
    m_view.setAkkoordMutualiteitDatum(m_model.getAkkoordMutualiteitDatum());
    m_view.setBetalingDatum(m_model.getBetalingDatum());
    m_view.setAfleveringDatum(m_model.getAfleveringDatum());
    m_view.setWisselDatum(m_model.getWisselDatum());
    m_view.setOnderhoudsContractDatum(m_model.getOnderhoudsContractDatum());
}

void Dossier::teardown()
{
    bool gewijzigd = false;
    bool apparaatGewijzigd = false;
    Model::Klant &klantModel = m_model.getKlant();
    if (klantModel.getAanspreektitel() != m_view.getAanspreektitel())
    {
        klantModel.setAanspreektitel(m_view.getAanspreektitel());
        gewijzigd = true;
    }
    if (klantModel.getNaam() != m_view.getNaam())
    {
        klantModel.setNaam(m_view.getNaam());
        gewijzigd = true;
    }
    if (klantModel.getVoornaam() != m_view.getVoornaam())
    {
        klantModel.setVoornaam(m_view.getVoornaam());
        gewijzigd = true;
    }
    if (klantModel.getStraat() != m_view.getStraat())
    {
        klantModel.setStraat(m_view.getStraat());
        gewijzigd = true;
    }
    if (klantModel.getPostcode() != m_view.getPostcode())
    {
        klantModel.setPostcode(m_view.getPostcode());
        gewijzigd = true;
    }
    if (klantModel.getGemeente() != m_view.getGemeente())
    {
        klantModel.setGemeente(m_view.getGemeente());
        gewijzigd = true;
    }
    if (klantModel.getTelefoon() != m_view.getTelefoon())
    {
        klantModel.setTelefoon(m_view.getTelefoon());
        gewijzigd = true;
    }
    if (klantModel.getGeboorteDatum() != m_view.getGeboorteDatum())
    {
        klantModel.setGeboorteDatum(m_view.getGeboorteDatum());
        gewijzigd = true;
    }
    if (klantModel.getOpmerkingen() != m_view.getOpmerkingen())
    {
        klantModel.setOpmerkingen(m_view.getOpmerkingen());
        gewijzigd = true;
    }
    if (m_model.getMutualiteit() != m_view.getMutualiteit())
    {
        m_model.setMutualiteit(m_view.getMutualiteit());
        gewijzigd = true;
    }
    if (m_model.getAansluitingsnummer() != m_view.getAansluitingsnummer())
    {
        m_model.setAansluitingsnummer(m_view.getAansluitingsnummer());
        gewijzigd = true;
    }
    if (m_model.getPlaatsAanpassing() != m_view.getPlaatsAanpassing())
    {
        m_model.setPlaatsAanpassing(m_view.getPlaatsAanpassing());
        gewijzigd = true;
    }
    if (m_model.getArts() != m_view.getArts())
    {
        m_model.setArts(m_view.getArts());
        gewijzigd = true;
    }
    if (m_model.getRechterHoorapparaatMerk() != m_view.getRechterHoorapparaatMerk())
    {
        m_model.setRechterHoorapparaatMerk(m_view.getRechterHoorapparaatMerk());
        gewijzigd = true;
        apparaatGewijzigd = true;
    }
    if (m_model.getRechterHoorapparaatType() != m_view.getRechterHoorapparaatType())
    {
        m_model.setRechterHoorapparaatType(m_view.getRechterHoorapparaatType());
        gewijzigd = true;
        apparaatGewijzigd = true;
    }
    if (m_model.getRechterHoorapparaatPrijs() != m_view.getRechterHoorapparaatPrijs())
    {
        m_model.setRechterHoorapparaatPrijs(m_view.getRechterHoorapparaatPrijs());
        gewijzigd = true;
    }
    if (m_model.getRechterHoorapparaatSerienummer() != m_view.getRechterHoorapparaatSerienummer())
    {
        m_model.setRechterHoorapparaatSerienummer(m_view.getRechterHoorapparaatSerienummer());
        gewijzigd = true;
    }
    if (m_model.getLinkerHoorapparaatMerk() != m_view.getLinkerHoorapparaatMerk())
    {
        m_model.setLinkerHoorapparaatMerk(m_view.getLinkerHoorapparaatMerk());
        gewijzigd = true;
        apparaatGewijzigd = true;
    }
    if (m_model.getLinkerHoorapparaatType() != m_view.getLinkerHoorapparaatType())
    {
        m_model.setLinkerHoorapparaatType(m_view.getLinkerHoorapparaatType());
        gewijzigd = true;
        apparaatGewijzigd = true;
    }
    if (m_model.getLinkerHoorapparaatPrijs() != m_view.getLinkerHoorapparaatPrijs())
    {
        m_model.setLinkerHoorapparaatPrijs(m_view.getLinkerHoorapparaatPrijs());
        gewijzigd = true;
    }
    if (m_model.getLinkerHoorapparaatSerienummer() != m_view.getLinkerHoorapparaatSerienummer())
    {
        m_model.setLinkerHoorapparaatSerienummer(m_view.getLinkerHoorapparaatSerienummer());
        gewijzigd = true;
    }
    if (m_model.getOnderzoekDatum() != m_view.getOnderzoekDatum())
    {
        m_model.setOnderzoekDatum(m_view.getOnderzoekDatum());
        gewijzigd = true;
    }
    if (m_model.getProefDatum() != m_view.getProefDatum())
    {
        m_model.setProefDatum(m_view.getProefDatum());
        gewijzigd = true;
    }
    if (m_model.getNKORapportDatum() != m_view.getNKORapportDatum())
    {
        m_model.setNKORapportDatum(m_view.getNKORapportDatum());
        gewijzigd = true;
    }
    if (m_model.getDokterAdviesDatum() != m_view.getDokterAdviesDatum())
    {
        m_model.setDokterAdviesDatum(m_view.getDokterAdviesDatum());
        gewijzigd = true;
    }
    if (m_model.getAkkoordMutualiteitDatum() != m_view.getAkkoordMutualiteitDatum())
    {
        m_model.setAkkoordMutualiteitDatum(m_view.getAkkoordMutualiteitDatum());
        gewijzigd = true;
    }
    if (m_model.getBetalingDatum() != m_view.getBetalingDatum())
    {
        m_model.setBetalingDatum(m_view.getBetalingDatum());
        gewijzigd = true;
    }
    if (m_model.getAfleveringDatum() != m_view.getAfleveringDatum())
    {
        m_model.setAfleveringDatum(m_view.getAfleveringDatum());
        gewijzigd = true;
    }
    if (m_model.getWisselDatum() != m_view.getWisselDatum())
    {
        m_model.setWisselDatum(m_view.getWisselDatum());
        gewijzigd = true;
    }
    if (m_model.getOnderhoudsContractDatum() != m_view.getOnderhoudsContractDatum())
    {
        m_model.setOnderhoudsContractDatum(m_view.getOnderhoudsContractDatum());
        gewijzigd = true;
    }

    if (gewijzigd)
    {
        emit dossierGewijzigd(m_model.getId());
    }
    if (apparaatGewijzigd)
    {
        emit hoorapparaatGewijzigd();
    }
}

void Dossier::setupFactuur()
{
    teardown();
    setup();

    Q_ASSERT(m_factuur);
    m_factuur->setKlantNaam(m_model.getKlant().getAanspreektitel() + " " + m_model.getKlant().getNaam() + " " + m_model.getKlant().getVoornaam());
    m_factuur->setKlantStraat(m_model.getKlant().getStraat());
    m_factuur->setKlantGemeente(QString::number(m_model.getKlant().getPostcode()) + " " + m_model.getKlant().getGemeente());

    Q_ASSERT(m_universum);
    Model::Instellingen &instellingen = m_universum->getInstellingen();
    m_factuur->setAudioloogNaam(instellingen.getNaam());
    m_factuur->setAudioloogStraat(instellingen.getStraat());
    m_factuur->setAudioloogGemeente(QString::number(instellingen.getPostcode()) + " " + instellingen.getGemeente());
    m_factuur->setAudioloogTelefoon(instellingen.getTelefoon());
    m_factuur->setAudioloogGSM(instellingen.getGsm());

    m_factuur->setNummer(m_model.getFactuur().getNummer());
    m_factuur->setDatum(m_model.getFactuur().getDatum());
    m_factuur->setVervalDatum(m_model.getFactuur().getVervalDatum());
    m_factuur->setKortingPercentage(m_model.getFactuur().getKortingPercentage());
    m_factuur->setBtwPercentage(m_model.getFactuur().getBtwPercentage());
    m_factuur->setCondities(m_model.getFactuur().getCondities());
    m_factuur->setTekst(m_model.getFactuur().getTekst());

    connect(m_factuur, SIGNAL(factuurSluiten()), this, SLOT(factuurSluiten()));
    connect(m_factuur, SIGNAL(factuurBewaren()), this, SLOT(factuurBewaren()));
}

void Dossier::briefArtsTonen()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter briefArtsView(true, m_view.getParentWindow());
    BriefArts briefArts(briefArtsView, m_model.getBriefArts());
    briefArts.setup();
    if (briefArtsView.exec() == QDialog::Accepted)
    {
        briefArts.teardown();
        emit dossierGewijzigd(m_model.getId());
    }
}

void Dossier::briefKlantTonen()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter briefKlantView(false, m_view.getParentWindow());
    BriefKlant briefKlant(briefKlantView, m_model.getBriefKlant());
    briefKlant.setup();
    if (briefKlantView.exec() == QDialog::Accepted)
    {
        briefKlant.teardown();
        emit dossierGewijzigd(m_model.getId());
    }
}

void Dossier::briefMutualiteitTonen()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter briefMutualiteitView(true, m_view.getParentWindow());
    BriefMutualiteit briefMutualiteit(briefMutualiteitView, m_model.getBriefMutualiteit());
    briefMutualiteit.setup();
    if (briefMutualiteitView.exec() == QDialog::Accepted)
    {
        briefMutualiteit.teardown();
        emit dossierGewijzigd(m_model.getId());
    }
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

void Dossier::factuurBewaren()
{
    Q_ASSERT(m_factuur);
    m_model.getFactuur().setNummer(m_factuur->getNummer());
    m_model.getFactuur().setDatum(m_factuur->getDatum());
    m_model.getFactuur().setVervalDatum(m_factuur->getVervalDatum());
    m_model.getFactuur().setKortingPercentage(m_factuur->getKortingPercentage());
    m_model.getFactuur().setBtwPercentage(m_factuur->getBtwPercentage());
    m_model.getFactuur().setCondities(m_factuur->getCondities());
    m_model.getFactuur().setTekst(m_factuur->getTekst());
    emit dossierGewijzigd(m_model.getId());
}

void Dossier::meetgegevensTonen()
{
    // Create a presenter and open the view
    View::Meetgegevens meetgegevensView(m_view.getParentWindow());
    Meetgegevens meetgegevens(meetgegevensView, m_model.getMeetgegevens());
    meetgegevens.setup();
    if (meetgegevensView.exec() == QDialog::Accepted)
    {
        meetgegevens.teardown();
        emit dossierGewijzigd(m_model.getId());
    }
}
