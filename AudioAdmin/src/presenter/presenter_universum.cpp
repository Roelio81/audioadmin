#include "presenter_universum.h"
#include "../model/model_arts.h"
#include "../model/model_dossier.h"
#include "../model/model_instellingen.h"
#include "../model/model_mutualiteit.h"
#include "../model/model_universum.h"
#include "../view/view_universum.h"

using namespace Presenter;

Universum::Universum(View::Universum &view, Model::Universum &model)
: m_view(view)
, m_model(model)
{
	connect(&m_view, SIGNAL(backupSignal(const ::QString &)), this, SLOT(openen(const ::QString &)));
	connect(&m_view, SIGNAL(restoreSignal(const ::QString &)), this, SLOT(bewaren(const ::QString &)));
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

void Universum::refreshArtsenLijst()
{
	m_view.leegArtsenLijst();
	QVector<Model::Arts *> &artsen = m_model.getArtsen();
	for (QVector<Model::Arts *>::const_iterator itArts = artsen.begin(); itArts != artsen.end(); ++itArts)
	{
		Q_ASSERT(*itArts);
		Model::Arts &arts = *(*itArts);
		m_view.toevoegenArts(arts.getNaam(), arts.getStraat(), arts.getPostcode(), arts.getGemeente());	
	}
} 

void Universum::refreshKlantenLijst()
{
	m_view.leegKlantenLijst();
	QVector<Model::Dossier *> &dossiers = m_model.getDossiers();
	for (QVector<Model::Dossier *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
	{
		Model::Dossier *dossier = *itDossier;
		Q_ASSERT(dossier);
		Model::Klant &klant = dossier->getKlant();
		m_view.toevoegenKlant(klant.getNaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());	
	}
} 

void Universum::refreshMutualiteitenLijst()
{
	m_view.leegMutualiteitenLijst();
	QVector<Model::Mutualiteit *> &mutualiteiten = m_model.getMutualiteiten();
	for (QVector<Model::Mutualiteit *>::const_iterator itMutualiteit = mutualiteiten.begin(); itMutualiteit != mutualiteiten.end(); ++itMutualiteit)
	{
		Q_ASSERT(*itMutualiteit);
		Model::Mutualiteit &mutualiteit = *(*itMutualiteit);
		m_view.toevoegenMutualiteit(mutualiteit.getNaam(), mutualiteit.getStraat(), mutualiteit.getPostcode(), mutualiteit.getGemeente());	
	}
} 

void Universum::openen(const QString &bestandsNaam)
{
	m_model.openen(bestandsNaam);
}

void Universum::bewaren(const QString &bestandsNaam)
{
	m_model.bewaren(bestandsNaam);
}
