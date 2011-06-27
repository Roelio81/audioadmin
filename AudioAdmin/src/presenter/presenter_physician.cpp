#include "presenter_physician.h"
#include "../model/model_physician.h"
#include "../view/view_physician.h"

using namespace Presenter;

Physician::Physician(View::Physician &view, Model::Physician &model)
: m_view(view)
, m_model(model)
{
}

Physician::~Physician()
{
}

void Physician::setup()
{
    m_view.setName(m_model.getName());
    m_view.setFirstName(m_model.getFirstName());
    m_view.setStreet(m_model.getStreet());
    m_view.setPostalCode(m_model.getPostalCode());
    m_view.setCity(m_model.getCity());
    m_view.setTelephone(m_model.getTelephone());
    m_view.setComments(m_model.getComments());
}

void Physician::teardown()
{
    bool changed = false;
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
    if (m_model.getComments() != m_view.getComments())
    {
        m_model.setComments(m_view.getComments());
        changed = true;
    }

    if (changed)
    {
        emit edited(m_model.getId());
    }
}
