#include "presenter_mutualiteit.h"
#include "../model/model_mutualiteit.h"
#include "../view/view_mutualiteit.h"

using namespace Presenter;

Mutualiteit::Mutualiteit(View::Mutualiteit &view, Model::Mutualiteit &model)
: m_view(view)
, m_model(model)
{
}

Mutualiteit::~Mutualiteit()
{
}

void Mutualiteit::setup()
{
	m_view.setNaam(m_model.getNaam());
	m_view.setStraat(m_model.getStraat());
	m_view.setPostcode(m_model.getPostcode());
	m_view.setGemeente(m_model.getGemeente());
	m_view.setTelefoon(m_model.getTelefoon());
	m_view.setOpmerkingen(m_model.getOpmerkingen());
}
