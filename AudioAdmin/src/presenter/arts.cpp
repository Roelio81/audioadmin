#include "arts.h"
#include "../model/arts.h"
#include "../view/arts.h"

using namespace Presenter;

Arts::Arts(View::Arts &view, Model::Arts &model)
: m_view(view)
, m_model(model)
{
}

Arts::~Arts()
{
}
