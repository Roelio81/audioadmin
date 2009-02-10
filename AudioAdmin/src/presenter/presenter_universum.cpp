#include "presenter_universum.h"
#include "../model/model_universum.h"
#include "../model/model_instellingen.h"
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
	Model::Instellingen *modelInstellingen = m_model.getInstellingen();
	View::Instellingen &viewInstellingen = m_view.getInstellingen();
	Q_ASSERT(modelInstellingen);
	viewInstellingen.setNaam(modelInstellingen->getNaam());
	viewInstellingen.setStraat(modelInstellingen->getStraat());
	viewInstellingen.setPostcode(modelInstellingen->getPostcode());
	viewInstellingen.setGemeente(modelInstellingen->getGemeente());
}

void Universum::teardownInstellingen()
{
	
}
