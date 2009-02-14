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
	m_view.setKlantNaam(klantModel.getNaam());
	m_view.setKlantVoornaam(klantModel.getVoornaam());
	m_view.setKlantStraat(klantModel.getStraat());
	m_view.setKlantPostcode(klantModel.getPostcode());
	m_view.setKlantGemeente(klantModel.getGemeente());
	m_view.setKlantTelefoon(klantModel.getTelefoon());
	m_view.setKlantGeboorteDatum(klantModel.getGeboorteDatum());
	m_view.setKlantMutualiteit(klantModel.getMutualiteit());
	m_view.setAansluitingsnummer(klantModel.getAansluitingsnummer());
	m_view.setPlaatsAanpassing(klantModel.getPlaatsAanpassing());
	m_view.setKlantOpmerkingen(klantModel.getOpmerkingen());
}
