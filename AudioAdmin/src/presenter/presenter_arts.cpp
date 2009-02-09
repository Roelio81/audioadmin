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
