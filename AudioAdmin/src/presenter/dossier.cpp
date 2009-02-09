#include "dossier.h"
#include "../model/dossier.h"
#include "../view/dossier.h"

using namespace Presenter;

Dossier::Dossier(View::Dossier &view, Model::Dossier &model)
: m_view(view)
, m_model(model)
{
}

Dossier::~Dossier()
{
}
