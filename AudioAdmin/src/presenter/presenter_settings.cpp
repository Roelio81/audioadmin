#include "presenter_settings.h"
#include "../model/model_settings.h"
#include "../view/view_settings.h"

using namespace Presenter;

Settings::Settings(View::Settings &view, Model::Settings &model)
    : m_view(view)
    , m_model(model)
{
}

Settings::~Settings()
{
}

void Settings::setup()
{
    m_view.setName(m_model.getName());
    m_view.setStreet(m_model.getStreet());
    m_view.setPostalCode(m_model.getPostalCode());
    m_view.setCity(m_model.getCity());
    m_view.setTelephone(m_model.getTelephone());
    m_view.setMobilePhone(m_model.getMobilePhone());
    m_view.setEmail(m_model.getEmail());
    m_view.setCaption(m_model.getCaption());
    m_view.setNationalId(m_model.getNationalId());
    m_view.setVATPercentage(m_model.getVATPercentage());
    m_view.setVATNumber(m_model.getVATNumber());
    m_view.setBankAccount(m_model.getBankAccount());
}

void Settings::teardown()
{
    m_model.setName(m_view.getName());
    m_model.setStreet(m_view.getStreet());
    m_model.setPostalCode(m_view.getPostalCode());
    m_model.setCity(m_view.getCity());
    m_model.setTelephone(m_view.getTelephone());
    m_model.setMobilePhone(m_view.getMobilePhone());
    m_model.setEmail(m_view.getEmail());
    m_model.setCaption(m_view.getCaption());
    m_model.setNationalId(m_view.getNationalId());
    m_model.setVATPercentage(m_view.getVATPercentage());
    m_model.setVATNumber(m_view.getVATNumber());
    m_model.setBankAccount(m_view.getBankAccount());
}
