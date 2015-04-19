#include "presenter_invoice.h"
#include "../model/model_customer.h"
#include "../model/model_file.h"
#include "../model/model_invoice.h"
#include "../model/model_settings.h"
#include "../model/model_universe.h"
#include "../view/view_invoice.h"

using namespace Presenter;

Invoice::Invoice(View::Invoice &view, Model::Invoice &model)
    : m_view(view)
    , m_model(model)
{
}

Invoice::~Invoice()
{
}

void Invoice::setup()
{
    const Model::File &file = m_model.getFile();
    const Model::Customer &customer = file.getCustomer();
    const Model::Settings &settings = file.getUniverse().getSettings();

    QString title;
    switch (customer.getTitle())
    {
        case Model::Customer::MR:
            title = tr("Mr");
            break;
        case Model::Customer::MRS:
            title = tr("Mrs");
            break;
    }

    m_view.setCustomerName(title + " " + customer.getName() + " " + customer.getFirstName());
    m_view.setCustomerStreet(customer.getStreet());
    m_view.setCustomerCity(QString::number(customer.getPostalCode()) + " " + customer.getCity());
    m_view.setName(settings.getName());
    m_view.setStreet(settings.getStreet());
    m_view.setCity(QString::number(settings.getPostalCode()) + " " + settings.getCity());
    m_view.setTelephone(settings.getTelephone());
    m_view.setMobilePhone(settings.getMobilePhone());
    m_view.setNumber(m_model.getNumber());
    m_view.setDate(m_model.getDate());
    m_view.setExpirationDate(m_model.getExpirationDate());
    m_view.setReductionPercentage(m_model.getReductionPercentage());
    m_view.setVATPercentage(m_model.getVATPercentage());
    m_view.setConditions(m_model.getConditions());
    m_view.setText(m_model.getText());
}

void Invoice::teardown()
{
    m_model.setNumber(m_view.getNumber());
    m_model.setDate(m_view.getDate());
    m_model.setExpirationDate(m_view.getExpirationDate());
    m_model.setReductionPercentage(m_view.getReductionPercentage());
    m_model.setVATPercentage(m_view.getVATPercentage());
    m_model.setConditions(m_view.getConditions());
    m_model.setText(m_view.getText());
}
