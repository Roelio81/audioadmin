#include "presenter_universum.h"
#include "presenter_arts.h"
#include "presenter_dossier.h"
#include "presenter_mutualiteit.h"
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
, m_artsPresenter(0)
, m_dossierPresenter(0)
, m_mutualiteitPresenter(0)
{
    connect(&m_view, SIGNAL(backupSignal(QString)), this, SLOT(openen(QString)));
    connect(&m_view, SIGNAL(restoreSignal(QString)), this, SLOT(bewaren(QString)));
    connect(&m_view, SIGNAL(etikettenSignal()), this, SLOT(etiketten()));
    connect(&m_view, SIGNAL(instellingenSignal()), this, SLOT(instellingen()));
    connect(&m_view, SIGNAL(artsSelectieSignal(int)), this, SLOT(toonArts(int)));
    connect(&m_view, SIGNAL(klantSelectieSignal(int)), this, SLOT(toonDossier(int)));
    connect(&m_view, SIGNAL(mutualiteitSelectieSignal(int)), this, SLOT(toonMutualiteit(int)));
    refreshArtsenLijst();
    refreshKlantenLijst();
    refreshMutualiteitenLijst();
    if (m_model.getArtsen().size() > 0) 
    {
        m_view.selecteerArts(m_model.getArtsen().front()->getId());
        
    }
    if (m_model.getDossiers().size() > 0) 
    {
        m_view.selecteerKlant(m_model.getDossiers().front()->getId());
    }
    if (m_model.getMutualiteiten().size() > 0) 
    {
        m_view.selecteerMutualiteit(m_model.getMutualiteiten().front()->getId());
    }
}

Universum::~Universum()
{
}

void Universum::etiketten()
{
    setupEtiketten();
    m_view.getEtiketten().show();
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
    viewInstellingen.setTelefoon(modelInstellingen->getTelefoon());
    viewInstellingen.setGsm(modelInstellingen->getGsm());
    viewInstellingen.setEmail(modelInstellingen->getEmail());
    viewInstellingen.setOnderschrift(modelInstellingen->getOnderschrift());
    viewInstellingen.setRiziv(modelInstellingen->getRiziv());
    viewInstellingen.setBtwPercentage(modelInstellingen->getBtwPercentage());
    viewInstellingen.setBtwNummer(modelInstellingen->getBtwNummer());
    viewInstellingen.setRekeningNummer(modelInstellingen->getRekeningNummer());
}

void Universum::setupEtiketten()
{
    View::Etiketten &viewEtiketten = m_view.getEtiketten();
    viewEtiketten.leegPlaatsenAanpassing();
    QVector<Model::Dossier *> &dossiers = m_model.getDossiers();
    for (QVector<Model::Dossier *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::Dossier *dossier = *itDossier;
        Q_ASSERT(dossier);
        viewEtiketten.toevoegenPlaatsAanpassing(dossier->getPlaatsAanpassing());
    }
    viewEtiketten.setDatumOnderzoek(QDate::currentDate().addYears(-2));
}

void Universum::teardownEtiketten()
{
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
        m_view.toevoegenArts(arts.getId(), arts.getNaam() + " " + arts.getVoornaam(), arts.getStraat(), arts.getPostcode(), arts.getGemeente());
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
        m_view.toevoegenKlant(dossier->getId(), klant.getNaam() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());
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
        m_view.toevoegenMutualiteit(mutualiteit.getId(), mutualiteit.getNaam(), mutualiteit.getStraat(), mutualiteit.getPostcode(), mutualiteit.getGemeente());
    }
}

void Universum::openen(QString bestandsNaam)
{
    m_model.openen(bestandsNaam);
    refreshArtsenLijst();
    refreshKlantenLijst();
    refreshMutualiteitenLijst();
}

void Universum::bewaren(QString bestandsNaam)
{
    m_model.bewaren(bestandsNaam);
}

void Universum::toonArts(int id)
{
    if (m_artsPresenter)
    {
        delete m_artsPresenter;
        m_artsPresenter = 0;
    }
    Model::Arts *artsModel = m_model.getArts(id);
    Q_ASSERT(artsModel);
    m_artsPresenter = new Presenter::Arts(m_view.getArts(), *artsModel);
    m_artsPresenter->setup();
}

void Universum::toonDossier(int id)
{
    if (m_dossierPresenter)
    {
        m_dossierPresenter->detachFromUniversum();
        delete m_dossierPresenter;
        m_dossierPresenter = 0;
    }
    Model::Dossier *dossierModel = m_model.getDossier(id);
    Q_ASSERT(dossierModel);
    m_dossierPresenter = new Presenter::Dossier(m_view.getDossier(), *dossierModel);
    m_dossierPresenter->attachToUniversum(&m_model);
    m_dossierPresenter->setup();
}

void Universum::toonMutualiteit(int id)
{
    if (m_mutualiteitPresenter)
    {
        delete m_mutualiteitPresenter;
        m_mutualiteitPresenter = 0;
    }
    Model::Mutualiteit *mutualiteitModel = m_model.getMutualiteit(id);
    Q_ASSERT(mutualiteitModel);
    m_mutualiteitPresenter = new Presenter::Mutualiteit(m_view.getMutualiteit(), *mutualiteitModel);
    m_mutualiteitPresenter->setup();
}
