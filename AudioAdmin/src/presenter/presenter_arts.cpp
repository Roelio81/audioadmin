#include "presenter_arts.h"
#include "../model/model_arts.h"
#include "../view/view_arts.h"

using namespace Presenter;

Arts::Arts(View::Arts &view, Model::Arts &model)
: m_view(view)
, m_model(model)
{
}

Arts::~Arts()
{
}

void Arts::setup()
{
    m_view.setNaam(m_model.getNaam());
    m_view.setVoornaam(m_model.getVoornaam());
    m_view.setStraat(m_model.getStraat());
    m_view.setPostcode(m_model.getPostcode());
    m_view.setGemeente(m_model.getGemeente());
    m_view.setTelefoon(m_model.getTelefoon());
    m_view.setOpmerkingen(m_model.getOpmerkingen());
}

void Arts::teardown()
{
    bool gewijzigd = false;
    if (m_model.getNaam() != m_view.getNaam())
    {
        m_model.setNaam(m_view.getNaam());
        gewijzigd = true;
    }
    if (m_model.getVoornaam() != m_view.getVoornaam())
    {
        m_model.setVoornaam(m_view.getVoornaam());
        gewijzigd = true;
    }
    if (m_model.getStraat() != m_view.getStraat())
    {
        m_model.setStraat(m_view.getStraat());
        gewijzigd = true;
    }
    if (m_model.getPostcode() != m_view.getPostcode())
    {
        m_model.setPostcode(m_view.getPostcode());
        gewijzigd = true;
    }
    if (m_model.getGemeente() != m_view.getGemeente())
    {
        m_model.setGemeente(m_view.getGemeente());
        gewijzigd = true;
    }
    if (m_model.getTelefoon() != m_view.getTelefoon())
    {
        m_model.setTelefoon(m_view.getTelefoon());
        gewijzigd = true;
    }
    if (m_model.getOpmerkingen() != m_view.getOpmerkingen())
    {
        m_model.setOpmerkingen(m_view.getOpmerkingen());
        gewijzigd = true;
    }

    if (gewijzigd)
    {
        emit artsGewijzigd(m_model.getId());
    }
}
