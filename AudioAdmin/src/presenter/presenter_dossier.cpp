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
	m_view.setKlantNaam(klantModel.getNaam());
}
