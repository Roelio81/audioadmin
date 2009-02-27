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
