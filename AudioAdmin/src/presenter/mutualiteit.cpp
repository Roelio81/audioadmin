#include "mutualiteit.h"
#include "../model/mutualiteit.h"
#include "../view/mutualiteit.h"

using namespace Presenter;

Mutualiteit::Mutualiteit(View::Mutualiteit &view, Model::Mutualiteit &model)
: m_view(view)
, m_model(model)
{
}

Mutualiteit::~Mutualiteit()
{
}
