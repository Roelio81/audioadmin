#include "presenter_dossier.h"
#include "../model/model_dossier.h"
#include "../view/view_dossier.h"

using namespace Presenter;

Dossier::Dossier(View::Dossier &view, Model::Dossier &model)
: m_view(view)
, m_model(model)
{
}

Dossier::~Dossier()
{
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
	m_view.setMutualiteit(klantModel.getMutualiteit());
	m_view.setAansluitingsnummer(klantModel.getAansluitingsnummer());
	m_view.setPlaatsAanpassing(klantModel.getPlaatsAanpassing());
	m_view.setOpmerkingen(klantModel.getOpmerkingen());
	m_view.setArts(m_model.getArts());
}
