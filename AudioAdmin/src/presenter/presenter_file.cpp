#include "presenter_file.h"
#include "presenter_briefarts.h"
#include "presenter_briefklant.h"
#include "presenter_briefmutualiteit.h"
#include "presenter_invoice.h"
#include "presenter_measurements.h"
#include "../model/model_file.h"
#include "../view/view_file.h"
#include "../view/view_letter.h"
#include "../view/view_invoice.h"
#include "../view/view_measurements.h"

using namespace Presenter;

File::File(View::File &view, Model::File &model)
: m_view(view)
, m_model(model)
{
    connect(&m_view, SIGNAL(briefArtsTonen()), this, SLOT(briefArtsTonen()));
    connect(&m_view, SIGNAL(briefKlantTonen()), this, SLOT(briefKlantTonen()));
    connect(&m_view, SIGNAL(briefMutualiteitTonen()), this, SLOT(briefMutualiteitTonen()));
    connect(&m_view, SIGNAL(showInvoice()), this, SLOT(showInvoice()));
    connect(&m_view, SIGNAL(showMeasurements()), this, SLOT(showMeasurements()));
}

File::~File()
{
}

void File::setup()
{
    Model::Customer &klantModel = m_model.getCustomer();
    m_view.leegAanspreektitels();
    m_view.toevoegenAanspreektitel("Dhr.");
    m_view.toevoegenAanspreektitel("Mevr.");
    m_view.setAanspreektitel(klantModel.getTitle());
    m_view.setNaam(klantModel.getName());
    m_view.setVoornaam(klantModel.getFirstName());
    m_view.setStraat(klantModel.getStreet());
    m_view.setPostcode(klantModel.getPostalCode());
    m_view.setGemeente(klantModel.getCity());
    m_view.setTelefoon(klantModel.getTelephone());
    m_view.setGeboorteDatum(klantModel.getDateOfBirth());
    m_view.setOpmerkingen(klantModel.getComments());
    m_view.setInsuranceCompany(m_model.getInsuranceCompany());
    m_view.setAansluitingsnummer(m_model.getAansluitingsnummer());
    m_view.setPlaatsAanpassing(m_model.getPlaatsAanpassing());
    m_view.setPhysician(m_model.getPhysician());
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

void File::teardown()
{
    bool changed = false;
    bool apparaatchanged = false;
    Model::Customer &klantModel = m_model.getCustomer();
    if (klantModel.getTitle() != m_view.getAanspreektitel())
    {
        klantModel.setTitle(m_view.getAanspreektitel());
        changed = true;
    }
    if (klantModel.getName() != m_view.getNaam())
    {
        klantModel.setName(m_view.getNaam());
        changed = true;
    }
    if (klantModel.getFirstName() != m_view.getVoornaam())
    {
        klantModel.setVoornaam(m_view.getVoornaam());
        changed = true;
    }
    if (klantModel.getStreet() != m_view.getStraat())
    {
        klantModel.setStreet(m_view.getStraat());
        changed = true;
    }
    if (klantModel.getPostalCode() != m_view.getPostcode())
    {
        klantModel.setPostalCode(m_view.getPostcode());
        changed = true;
    }
    if (klantModel.getCity() != m_view.getGemeente())
    {
        klantModel.setCity(m_view.getGemeente());
        changed = true;
    }
    if (klantModel.getTelephone() != m_view.getTelefoon())
    {
        klantModel.setTelephone(m_view.getTelefoon());
        changed = true;
    }
    if (klantModel.getDateOfBirth() != m_view.getGeboorteDatum())
    {
        klantModel.setGeboorteDatum(m_view.getGeboorteDatum());
        changed = true;
    }
    if (klantModel.getComments() != m_view.getComments())
    {
        klantModel.setComments(m_view.getComments());
        changed = true;
    }
    if (m_model.getInsuranceCompany() != m_view.getInsuranceCompany())
    {
        m_model.setMutualiteit(m_view.getInsuranceCompany());
        changed = true;
    }
    if (m_model.getAansluitingsnummer() != m_view.getAansluitingsnummer())
    {
        m_model.setAansluitingsnummer(m_view.getAansluitingsnummer());
        changed = true;
    }
    if (m_model.getPlaatsAanpassing() != m_view.getPlaatsAanpassing())
    {
        m_model.setPlaatsAanpassing(m_view.getPlaatsAanpassing());
        changed = true;
    }
    if (m_model.getPhysician() != m_view.getPhysician())
    {
        m_model.setArts(m_view.getPhysician());
        changed = true;
    }
    if (m_model.getRechterHoorapparaatMerk() != m_view.getRechterHoorapparaatMerk())
    {
        m_model.setRechterHoorapparaatMerk(m_view.getRechterHoorapparaatMerk());
        changed = true;
        apparaatchanged = true;
    }
    if (m_model.getRechterHoorapparaatType() != m_view.getRechterHoorapparaatType())
    {
        m_model.setRechterHoorapparaatType(m_view.getRechterHoorapparaatType());
        changed = true;
        apparaatchanged = true;
    }
    if (m_model.getRechterHoorapparaatPrijs() != m_view.getRechterHoorapparaatPrijs())
    {
        m_model.setRechterHoorapparaatPrijs(m_view.getRechterHoorapparaatPrijs());
        changed = true;
    }
    if (m_model.getRechterHoorapparaatSerienummer() != m_view.getRechterHoorapparaatSerienummer())
    {
        m_model.setRechterHoorapparaatSerienummer(m_view.getRechterHoorapparaatSerienummer());
        changed = true;
    }
    if (m_model.getLinkerHoorapparaatMerk() != m_view.getLinkerHoorapparaatMerk())
    {
        m_model.setLinkerHoorapparaatMerk(m_view.getLinkerHoorapparaatMerk());
        changed = true;
        apparaatchanged = true;
    }
    if (m_model.getLinkerHoorapparaatType() != m_view.getLinkerHoorapparaatType())
    {
        m_model.setLinkerHoorapparaatType(m_view.getLinkerHoorapparaatType());
        changed = true;
        apparaatchanged = true;
    }
    if (m_model.getLinkerHoorapparaatPrijs() != m_view.getLinkerHoorapparaatPrijs())
    {
        m_model.setLinkerHoorapparaatPrijs(m_view.getLinkerHoorapparaatPrijs());
        changed = true;
    }
    if (m_model.getLinkerHoorapparaatSerienummer() != m_view.getLinkerHoorapparaatSerienummer())
    {
        m_model.setLinkerHoorapparaatSerienummer(m_view.getLinkerHoorapparaatSerienummer());
        changed = true;
    }
    if (m_model.getOnderzoekDatum() != m_view.getOnderzoekDatum())
    {
        m_model.setOnderzoekDatum(m_view.getOnderzoekDatum());
        changed = true;
    }
    if (m_model.getProefDatum() != m_view.getProefDatum())
    {
        m_model.setProefDatum(m_view.getProefDatum());
        changed = true;
    }
    if (m_model.getNKORapportDatum() != m_view.getNKORapportDatum())
    {
        m_model.setNKORapportDatum(m_view.getNKORapportDatum());
        changed = true;
    }
    if (m_model.getDokterAdviesDatum() != m_view.getDokterAdviesDatum())
    {
        m_model.setDokterAdviesDatum(m_view.getDokterAdviesDatum());
        changed = true;
    }
    if (m_model.getAkkoordMutualiteitDatum() != m_view.getAkkoordMutualiteitDatum())
    {
        m_model.setAkkoordMutualiteitDatum(m_view.getAkkoordMutualiteitDatum());
        changed = true;
    }
    if (m_model.getBetalingDatum() != m_view.getBetalingDatum())
    {
        m_model.setBetalingDatum(m_view.getBetalingDatum());
        changed = true;
    }
    if (m_model.getAfleveringDatum() != m_view.getAfleveringDatum())
    {
        m_model.setAfleveringDatum(m_view.getAfleveringDatum());
        changed = true;
    }
    if (m_model.getWisselDatum() != m_view.getWisselDatum())
    {
        m_model.setWisselDatum(m_view.getWisselDatum());
        changed = true;
    }
    if (m_model.getOnderhoudsContractDatum() != m_view.getOnderhoudsContractDatum())
    {
        m_model.setOnderhoudsContractDatum(m_view.getOnderhoudsContractDatum());
        changed = true;
    }

    if (changed)
    {
        emit edited(m_model.getId());
    }
    if (apparaatchanged)
    {
        emit hoorapparaatGewijzigd();
    }
}

void File::briefArtsTonen()
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
        emit edited(m_model.getId());
    }
}

void File::briefKlantTonen()
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
        emit edited(m_model.getId());
    }
}

void File::briefMutualiteitTonen()
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
        emit edited(m_model.getId());
    }
}

void File::showInvoice()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Invoice invoiceView(m_view.getParentWindow());
    Invoice invoice(invoiceView, m_model.getInvoice());
    invoice.setup();
    if (invoiceView.exec() == QDialog::Accepted)
    {
        invoice.teardown();
        emit edited(m_model.getId());
    }
}

void File::showMeasurements()
{
    // Create a presenter and open the view
    View::Measurements measurementsView(m_view.getParentWindow());
    Measurements measurements(measurementsView, m_model.getMeasurements());
    measurements.setup();
    if (measurementsView.exec() == QDialog::Accepted)
    {
        measurements.teardown();
        emit edited(m_model.getId());
    }
}
