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
