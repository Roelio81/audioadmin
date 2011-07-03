#include "presenter_customer.h"
#include "../model/model_customer.h"
#include "../view/view_customer.h"

using namespace Presenter;

namespace
{
QString titleToString(const Model::Customer::Title &title)
    {
    switch (title)
        {
        case Model::Customer::MR:
            return Customer::tr("Mr.");
        case Model::Customer::MRS:
            return Customer::tr("Mrs.");
        }

    Q_ASSERT(false);
    return Customer::tr("Mr.");
    }

Model::Customer::Title titleFromString(const QString &title)
    {
    if (title == Customer::tr("Mr."))
        return Model::Customer::MR;
    if (title == Customer::tr("Mrs."))
        return Model::Customer::MRS;

    Q_ASSERT(false);
    return Model::Customer::MR;
    }
}

Customer::Customer(View::Customer &view, Model::Customer &model)
    : m_view(view)
    , m_model(model)
{
}

Customer::~Customer()
{
}

void Customer::setup()
{
    m_view.clearTitles();
    m_view.addTitle(titleToString(Model::Customer::MR));
    m_view.addTitle(titleToString(Model::Customer::MRS));
    m_view.setTitle(titleToString(m_model.getTitle()));
    m_view.setName(m_model.getName());
    m_view.setFirstName(m_model.getFirstName());
    m_view.setStreet(m_model.getStreet());
    m_view.setPostalCode(m_model.getPostalCode());
    m_view.setCity(m_model.getCity());
    m_view.setTelephone(m_model.getTelephone());
    m_view.setDateOfBirth(m_model.getDateOfBirth());
    m_view.setComments(m_model.getComments());
}

void Customer::teardown()
{
    bool changed = false;
    if (m_model.getTitle() != titleFromString(m_view.getTitle()))
    {
        m_model.setTitle(titleFromString(m_view.getTitle()));
        changed = true;
    }
    if (m_model.getName() != m_view.getName())
    {
        m_model.setName(m_view.getName());
        changed = true;
    }
    if (m_model.getFirstName() != m_view.getFirstName())
    {
        m_model.setFirstName(m_view.getFirstName());
        changed = true;
    }
    if (m_model.getStreet() != m_view.getStreet())
    {
        m_model.setStreet(m_view.getStreet());
        changed = true;
    }
    if (m_model.getPostalCode() != m_view.getPostalCode())
    {
        m_model.setPostalCode(m_view.getPostalCode());
        changed = true;
    }
    if (m_model.getCity() != m_view.getCity())
    {
        m_model.setCity(m_view.getCity());
        changed = true;
    }
    if (m_model.getTelephone() != m_view.getTelephone())
    {
        m_model.setTelephone(m_view.getTelephone());
        changed = true;
    }
    if (m_model.getDateOfBirth() != m_view.getDateOfBirth())
    {
        m_model.setDateOfBirth(m_view.getDateOfBirth());
        changed = true;
    }
    if (m_model.getComments() != m_view.getComments())
    {
        m_model.setComments(m_view.getComments());
        changed = true;
    }

    if (changed)
        emit edited();
}
