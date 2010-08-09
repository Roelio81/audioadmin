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
, m_arts(0)
, m_dossier(0)
, m_mutualiteit(0)
{
    connect(&m_view, SIGNAL(bewarenSignal()), this, SLOT(bewaren()));
    connect(&m_view, SIGNAL(etikettenSignal()), this, SLOT(etiketten()));
    connect(&m_view, SIGNAL(instellingenSignal()), this, SLOT(instellingen()));
    connect(&m_view, SIGNAL(artsSelectieSignal(int)), this, SLOT(toonArts(int)));
    connect(&m_view, SIGNAL(artsVerwijderenSignal(int)), this, SLOT(toonDossier(int)));
    connect(&m_view, SIGNAL(artsToevoegenSignal(QString, QString)), this, SLOT(toevoegenArts(QString, QString)));
    connect(&m_view, SIGNAL(klantSelectieSignal(int)), this, SLOT(toonDossier(int)));
    connect(&m_view, SIGNAL(klantVerwijderenSignal(int)), this, SLOT(verwijderDossier(int)));
    connect(&m_view, SIGNAL(klantToevoegenSignal(QString, QString)), this, SLOT(toevoegenDossier(QString, QString)));
    connect(&m_view, SIGNAL(mutualiteitSelectieSignal(int)), this, SLOT(toonMutualiteit(int)));
    connect(&m_view, SIGNAL(mutualiteitVerwijderenSignal(int)), this, SLOT(verwijderMutualiteit(int)));
    connect(&m_view, SIGNAL(mutualiteitToevoegenSignal(QString)), this, SLOT(toevoegenMutualiteit(QString)));
    connect(&m_view, SIGNAL(sluitArtsTab()), this, SLOT(teardownArts()));
    connect(&m_view, SIGNAL(sluitDossierTab()), this, SLOT(teardownDossier()));
    connect(&m_view, SIGNAL(sluitMutualiteitTab()), this, SLOT(teardownMutualiteit()));
    connect(&m_view, SIGNAL(openArtsTab()), this, SLOT(setupArts()));
    connect(&m_view, SIGNAL(openDossierTab()), this, SLOT(setupDossier()));
    connect(&m_view, SIGNAL(openMutualiteitTab()), this, SLOT(setupMutualiteit()));
    refreshArtsenLijst();
    refreshHoorapparatenLijst();
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

void Universum::bewaren()
{
    m_model.bewaren();
}

void Universum::etiketten()
{
    setupEtiketten();
    connect(m_view.getEtiketten().b_ok, SIGNAL(clicked()), this, SLOT(okEtiketten()));
    connect(m_view.getEtiketten().b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerEtiketten()));
    m_view.getEtiketten().show();
    disconnect(this, SLOT(okEtiketten()));
    disconnect(this, SLOT(annuleerEtiketten()));
}

void Universum::okEtiketten()
{
    teardownEtiketten();
    m_view.getEtiketten().hide();
}

void Universum::annuleerEtiketten()
{
    m_view.getEtiketten().hide();
}

void Universum::instellingen()
{
    setupInstellingen();
    connect(m_view.getInstellingen().b_ok, SIGNAL(clicked()), this, SLOT(okInstellingen()));
    connect(m_view.getInstellingen().b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerInstellingen()));
    m_view.getInstellingen().show();
    disconnect(this, SLOT(okInstellingen()));
    disconnect(this, SLOT(annuleerInstellingen()));
}

void Universum::okInstellingen()
{
    teardownInstellingen();
    m_view.getInstellingen().hide();
}

void Universum::annuleerInstellingen()
{
    m_view.getInstellingen().hide();
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

void Universum::teardownEtiketten()
{
}

void Universum::teardownInstellingen()
{
    Model::Instellingen *modelInstellingen = m_model.getInstellingen();
    View::Instellingen &viewInstellingen = m_view.getInstellingen();
    Q_ASSERT(modelInstellingen);
    modelInstellingen->setNaam(viewInstellingen.getNaam());
    modelInstellingen->setStraat(viewInstellingen.getStraat());
    modelInstellingen->setPostcode(viewInstellingen.getPostcode());
    modelInstellingen->setGemeente(viewInstellingen.getGemeente());
    modelInstellingen->setTelefoon(viewInstellingen.getTelefoon());
    modelInstellingen->setGsm(viewInstellingen.getGsm());
    modelInstellingen->setEmail(viewInstellingen.getEmail());
    modelInstellingen->setOnderschrift(viewInstellingen.getOnderschrift());
    modelInstellingen->setRiziv(viewInstellingen.getRiziv());
    modelInstellingen->setBtwPercentage(viewInstellingen.getBtwPercentage());
    modelInstellingen->setBtwNummer(viewInstellingen.getBtwNummer());
    modelInstellingen->setRekeningNummer(viewInstellingen.getRekeningNummer());
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

void Universum::refreshHoorapparatenLijst()
{
    m_view.leegHoorapparatenLijst();
    QVector<Model::Dossier *> &dossiers = m_model.getDossiers();
    for (QVector<Model::Dossier *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::Dossier *dossier = *itDossier;
        Q_ASSERT(dossier);
        m_view.toevoegenHoorapparaat(dossier->getRechterHoorapparaatMerk(), dossier->getRechterHoorapparaatType(), dossier->getRechterHoorapparaatPrijs(), dossier->getProefDatum());
        m_view.toevoegenHoorapparaat(dossier->getLinkerHoorapparaatMerk(), dossier->getLinkerHoorapparaatType(), dossier->getLinkerHoorapparaatPrijs(), dossier->getProefDatum());
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

void Universum::toonArts(int id)
{
    teardownArts();
    m_arts = id;
    setupArts();
}

void Universum::toonDossier(int id)
{
    teardownDossier();
    m_dossier = id;
    setupDossier();
    }

void Universum::toonMutualiteit(int id)
{
    teardownMutualiteit();
    m_mutualiteit = id;
    setupMutualiteit();
}

void Universum::verwijderArts(int id)
{
    if (m_artsPresenter)
    {
        delete m_artsPresenter;
        m_artsPresenter = 0;
    }
    m_model.verwijderenArts(id);
}

void Universum::verwijderDossier(int id)
{
    if (m_dossierPresenter)
    {
        delete m_dossierPresenter;
        m_dossierPresenter = 0;
    }
    m_model.verwijderenDossier(id);
}

void Universum::verwijderMutualiteit(int id)
{
    if (m_mutualiteitPresenter)
    {
        delete m_mutualiteitPresenter;
        m_mutualiteitPresenter = 0;
    }
    m_model.verwijderenMutualiteit(id);
}

void Universum::toevoegenArts(QString voornaam, QString naam)
{
    Model::Arts *arts = m_model.toevoegenArts(voornaam, naam);
    Q_ASSERT(arts);
    m_view.toevoegenArts(arts->getId(), arts->getNaam() + " " + arts->getVoornaam(), arts->getStraat(), arts->getPostcode(), arts->getGemeente());
    m_view.selecteerArts(arts->getId());
}

void Universum::toevoegenDossier(QString voornaam, QString naam)
{
    Model::Dossier *dossier = m_model.toevoegenDossier(voornaam, naam);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.toevoegenKlant(dossier->getId(), klant.getNaam() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());
    m_view.selecteerKlant(dossier->getId());
}

void Universum::toevoegenMutualiteit(QString naam)
{
    Model::Mutualiteit *mutualiteit = m_model.toevoegenMutualiteit(naam);
    Q_ASSERT(mutualiteit);
    m_view.toevoegenMutualiteit(mutualiteit->getId(), mutualiteit->getNaam(), mutualiteit->getStraat(), mutualiteit->getPostcode(), mutualiteit->getGemeente());
    m_view.selecteerMutualiteit(mutualiteit->getId());
}

void Universum::artsGewijzigd(int id)
{
    Model::Arts *arts = m_model.getArts(id);
    Q_ASSERT(arts);
    m_view.markeerArtsenLijstStatus(true);
    m_view.wijzigenArts(arts->getId(), arts->getNaam() + " " + arts->getVoornaam(), arts->getStraat(), arts->getPostcode(), arts->getGemeente());
}

void Universum::dossierGewijzigd(int id)
{
    Model::Dossier *dossier = m_model.getDossier(id);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.markeerKlantenLijstStatus(true);
    m_view.wijzigenKlant(dossier->getId(), klant.getNaam() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());
}

void Universum::mutualiteitGewijzigd(int id)
{
    Model::Mutualiteit *mutualiteit = m_model.getMutualiteit(id);
    Q_ASSERT(mutualiteit);
    m_view.markeerArtsenLijstStatus(true);
    m_view.wijzigenMutualiteit(mutualiteit->getId(), mutualiteit->getNaam(), mutualiteit->getStraat(), mutualiteit->getPostcode(), mutualiteit->getGemeente());
}

void Universum::hoorapparaatGewijzigd()
{
    refreshHoorapparatenLijst();
}

void Universum::teardownArts()
{
    if (!m_artsPresenter)
        return;
    m_artsPresenter->teardown();
    disconnect(this, SLOT(artsGewijzigd(int)));
    delete m_artsPresenter;
    m_artsPresenter = 0;
}

void Universum::teardownDossier()
{
    if (!m_dossierPresenter)
        return;
    m_dossierPresenter->detachFromUniversum();
    m_dossierPresenter->teardown();
    disconnect(this, SLOT(dossierGewijzigd(int)));
    delete m_dossierPresenter;
    m_dossierPresenter = 0;
}

void Universum::teardownMutualiteit()
{
    if (!m_mutualiteitPresenter)
        return;
    m_mutualiteitPresenter->teardown();
    disconnect(this, SLOT(mutualiteitGewijzigd(int)));
    delete m_mutualiteitPresenter;
    m_mutualiteitPresenter = 0;
}

void Universum::setupArts()
{
    Model::Arts *artsModel = m_model.getArts(m_arts);
    Q_ASSERT(artsModel);
    m_artsPresenter = new Presenter::Arts(m_view.getArts(), *artsModel);
    m_artsPresenter->setup();
    connect(m_artsPresenter, SIGNAL(artsGewijzigd(int)), this, SLOT(artsGewijzigd(int)));
}

void Universum::setupDossier()
{
    Model::Dossier *dossierModel = m_model.getDossier(m_dossier);
    Q_ASSERT(dossierModel);
    m_dossierPresenter = new Presenter::Dossier(m_view.getDossier(), *dossierModel);
    m_dossierPresenter->attachToUniversum(&m_model);
    m_dossierPresenter->setup();
    connect(m_dossierPresenter, SIGNAL(dossierGewijzigd(int)), this, SLOT(dossierGewijzigd(int)));
    connect(m_dossierPresenter, SIGNAL(destroyed()), this, SLOT(hoorapparaatGewijzigd()));
}

void Universum::setupMutualiteit()
{
    Model::Mutualiteit *mutualiteitModel = m_model.getMutualiteit(m_mutualiteit);
    Q_ASSERT(mutualiteitModel);
    m_mutualiteitPresenter = new Presenter::Mutualiteit(m_view.getMutualiteit(), *mutualiteitModel);
    m_mutualiteitPresenter->setup();
    connect(m_mutualiteitPresenter, SIGNAL(mutualiteitGewijzigd(int)), this, SLOT(mutualiteitGewijzigd(int)));
}
