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
