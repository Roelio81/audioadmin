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
    connect(&m_view, SIGNAL(showLetterPhysician()), this, SLOT(showLetterPhysician()));
    connect(&m_view, SIGNAL(showLetterCustomer()), this, SLOT(showLetterCustomer()));
    connect(&m_view, SIGNAL(showLetterInsuranceCompany()), this, SLOT(showLetterInsuranceCompany()));
    connect(&m_view, SIGNAL(showInvoice()), this, SLOT(showInvoice()));
    connect(&m_view, SIGNAL(showMeasurements()), this, SLOT(showMeasurements()));
}

File::~File()
{
}

void File::setup()
{
    Model::Customer &customerModel = m_model.getCustomer();
    m_view.clearTitles();
    m_view.addTitle("Dhr.");
    m_view.addTitle("Mevr.");
    m_view.setTitle(customerModel.getTitle());
    m_view.setName(customerModel.getName());
    m_view.setFirstName(customerModel.getFirstName());
    m_view.setStreet(customerModel.getStreet());
    m_view.setPostalCode(customerModel.getPostalCode());
    m_view.setCity(customerModel.getCity());
    m_view.setTelephone(customerModel.getTelephone());
    m_view.setDateOfBirth(customerModel.getDateOfBirth());
    m_view.setComments(customerModel.getComments());
    m_view.setInsuranceCompany(m_model.getInsuranceCompany());
    m_view.setMemberNumber(m_model.getMemberNumber());
    m_view.setPlaceAdjustment(m_model.getPlaceAdjustment());
    m_view.setPhysician(m_model.getPhysician());
    m_view.setRightHearingAidBrand(m_model.getRightHearingAidBrand());
    m_view.setRightHearingAidType(m_model.getRightHearingAidType());
    m_view.setRightHearingAidPrice(m_model.getRightHearingAidPrice());
    m_view.setRightHearingAidSerialNumber(m_model.getRightHearingAidSerialNumber());
    m_view.setLeftHearingAidBrand(m_model.getLeftHearingAidBrand());
    m_view.setLeftHearingAidType(m_model.getLeftHearingAidType());
    m_view.setLeftHearingAidPrice(m_model.getLeftHearingAidPrice());
    m_view.setLeftHearingAidSerialNumber(m_model.getLeftHearingAidSerialNumber());
    m_view.setTestDate(m_model.getTestDate());
    m_view.setTrialDate(m_model.getTrialDate());
    m_view.setPhysicianReportDate(m_model.getPhysicianReportDate());
    m_view.setPhysicianAdviceDate(m_model.getPhysicianAdviceDate());
    m_view.setInsuranceAgreementDate(m_model.getInsuranceAgreementDate());
    m_view.setPaymentDate(m_model.getPaymentDate());
    m_view.setDeliveryDate(m_model.getDeliveryDate());
    m_view.setExchangeDate(m_model.getExchangeDate());
    m_view.setMaintenanceContractDate(m_model.getMaintenanceContractDate());
}

void File::teardown()
{
    bool changed = false;
    Model::Customer &customerModel = m_model.getCustomer();
    if (customerModel.getTitle() != m_view.getTitle())
    {
        customerModel.setTitle(m_view.getTitle());
        changed = true;
    }
    if (customerModel.getName() != m_view.getName())
    {
        customerModel.setName(m_view.getName());
        changed = true;
    }
    if (customerModel.getFirstName() != m_view.getFirstName())
    {
        customerModel.setVoornaam(m_view.getFirstName());
        changed = true;
    }
    if (customerModel.getStreet() != m_view.getStreet())
    {
        customerModel.setStreet(m_view.getStreet());
        changed = true;
    }
    if (customerModel.getPostalCode() != m_view.getPostalCode())
    {
        customerModel.setPostalCode(m_view.getPostalCode());
        changed = true;
    }
    if (customerModel.getCity() != m_view.getCity())
    {
        customerModel.setCity(m_view.getCity());
        changed = true;
    }
    if (customerModel.getTelephone() != m_view.getTelephone())
    {
        customerModel.setTelephone(m_view.getTelephone());
        changed = true;
    }
    if (customerModel.getDateOfBirth() != m_view.getDateOfBirth())
    {
        customerModel.setGeboorteDatum(m_view.getDateOfBirth());
        changed = true;
    }
    if (customerModel.getComments() != m_view.getComments())
    {
        customerModel.setComments(m_view.getComments());
        changed = true;
    }
    if (m_model.getInsuranceCompany() != m_view.getInsuranceCompany())
    {
        m_model.setInsuranceCompany(m_view.getInsuranceCompany());
        changed = true;
    }
    if (m_model.getMemberNumber() != m_view.getMemberNumber())
    {
        m_model.setMemberNumber(m_view.getMemberNumber());
        changed = true;
    }
    if (m_model.getPlaceAdjustment() != m_view.getPlaceAdjustment())
    {
        m_model.setPlaceAdjustment(m_view.getPlaceAdjustment());
        changed = true;
    }
    if (m_model.getPhysician() != m_view.getPhysician())
    {
        m_model.setPhysician(m_view.getPhysician());
        changed = true;
    }
    if (m_model.getRightHearingAidBrand() != m_view.getRightHearingAidBrand())
    {
        m_model.setRightHearingAidBrand(m_view.getRightHearingAidBrand());
        changed = true;
    }
    if (m_model.getRightHearingAidType() != m_view.getRightHearingAidType())
    {
        m_model.setRightHearingAidType(m_view.getRightHearingAidType());
        changed = true;
    }
    if (m_model.getRightHearingAidPrice() != m_view.getRightHearingAidPrice())
    {
        m_model.setRightHearingAidPrice(m_view.getRightHearingAidPrice());
        changed = true;
    }
    if (m_model.getRightHearingAidSerialNumber() != m_view.getRightHearingAidSerialNumber())
    {
        m_model.setRightHearingAidSerialNumber(m_view.getRightHearingAidSerialNumber());
        changed = true;
    }
    if (m_model.getLeftHearingAidBrand() != m_view.getLeftHearingAidBrand())
    {
        m_model.setLeftHearingAidBrand(m_view.getLeftHearingAidBrand());
        changed = true;
    }
    if (m_model.getLeftHearingAidType() != m_view.getLeftHearingAidType())
    {
        m_model.setLeftHearingAidType(m_view.getLeftHearingAidType());
        changed = true;
    }
    if (m_model.getLeftHearingAidPrice() != m_view.getLeftHearingAidPrice())
    {
        m_model.setLeftHearingAidPrice(m_view.getLeftHearingAidPrice());
        changed = true;
    }
    if (m_model.getLeftHearingAidSerialNumber() != m_view.getLeftHearingAidSerialNumber())
    {
        m_model.setLeftHearingAidSerialNumber(m_view.getLeftHearingAidSerialNumber());
        changed = true;
    }
    if (m_model.getTestDate() != m_view.getTestDate())
    {
        m_model.setTestDate(m_view.getTestDate());
        changed = true;
    }
    if (m_model.getTrialDate() != m_view.getTrialDate())
    {
        m_model.setTrialDate(m_view.getTrialDate());
        changed = true;
    }
    if (m_model.getPhysicianReportDate() != m_view.getPhysicianReportDate())
    {
        m_model.setPhysicianReportDate(m_view.getPhysicianReportDate());
        changed = true;
    }
    if (m_model.getPhysicianAdviceDate() != m_view.getPhysicianAdviceDate())
    {
        m_model.setPhysicianAdviceDate(m_view.getPhysicianAdviceDate());
        changed = true;
    }
    if (m_model.getInsuranceAgreementDate() != m_view.getInsuranceAgreementDate())
    {
        m_model.setInsuranceAgreementDate(m_view.getInsuranceAgreementDate());
        changed = true;
    }
    if (m_model.getPaymentDate() != m_view.getPaymentDate())
    {
        m_model.setPaymentDate(m_view.getPaymentDate());
        changed = true;
    }
    if (m_model.getDeliveryDate() != m_view.getDeliveryDate())
    {
        m_model.setDeliveryDate(m_view.getDeliveryDate());
        changed = true;
    }
    if (m_model.getExchangeDate() != m_view.getExchangeDate())
    {
        m_model.setExchangeDate(m_view.getExchangeDate());
        changed = true;
    }
    if (m_model.getMaintenanceContractDate() != m_view.getMaintenanceContractDate())
    {
        m_model.setMaintenanceContractDate(m_view.getMaintenanceContractDate());
        changed = true;
    }

    if (changed)
        emit edited(m_model.getId());
}

void File::showLetterPhysician()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter letterPhysicianView(true, m_view.getParentWindow());
    BriefArts letterPhysician(letterPhysicianView, m_model.getLetterPhysician());
    letterPhysician.setup();
    if (letterPhysicianView.exec() == QDialog::Accepted)
    {
        letterPhysician.teardown();
        emit edited(m_model.getId());
    }
}

void File::showLetterCustomer()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter letterCustomerView(false, m_view.getParentWindow());
    BriefKlant letterCustomer(letterCustomerView, m_model.getLetterCustomer());
    letterCustomer.setup();
    if (letterCustomerView.exec() == QDialog::Accepted)
    {
        letterCustomer.teardown();
        emit edited(m_model.getId());
    }
}

void File::showLetterInsuranceCompany()
{
    // First make sure that we are fully up-to-date
    teardown();
    setup();

    // Create a presenter and open the view
    View::Letter letterInsuranceCompanyView(true, m_view.getParentWindow());
    BriefMutualiteit letterInsuranceCompany(letterInsuranceCompanyView, m_model.getLetterInsuranceCompany());
    letterInsuranceCompany.setup();
    if (letterInsuranceCompanyView.exec() == QDialog::Accepted)
    {
        letterInsuranceCompany.teardown();
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
