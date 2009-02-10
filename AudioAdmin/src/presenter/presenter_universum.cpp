#include "presenter_universum.h"
#include "../model/model_universum.h"
#include "../view/view_universum.h"

using namespace Presenter;

Universum::Universum(View::Universum &view, Model::Universum &model)
: m_view(view)
, m_model(model)
{
	connect(&m_view, SIGNAL(backupSignal(const ::QString &)), &m_model, SLOT(save(const ::QString &)));
	connect(&m_view, SIGNAL(restoreSignal(const ::QString &)), &m_model, SLOT(load(const ::QString &)));
	connect(&m_view, SIGNAL(instellingenSignal()), this, SLOT(instellingen()));
}

Universum::~Universum()
{
}

void Universum::instellingen()
{
	setupInstellingen();
	m_view.getInstellingen().show();
}

void Universum::setupInstellingen()
{
	m_view.getInstellingen().setNaam(m_model.getNaam());
}

void Universum::teardownInstellingen()
{
	
}
