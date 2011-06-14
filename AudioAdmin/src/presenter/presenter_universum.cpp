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

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

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
, m_gewijzigd(false)
{
    connect(&m_view, SIGNAL(afsluitenSignal()), this, SLOT(afsluiten()));
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

    cleanupArtsTab();
    if (!m_model.getArtsen().empty())
        m_view.selecteerArts(m_model.getArtsen().front()->getId());

    cleanupDossierTab();
    if (!m_model.getDossiers().empty())
        m_view.selecteerKlant(m_model.getDossiers().front()->getId());

    cleanupMutualiteitTab();
    if (!m_model.getMutualiteiten().empty())
        m_view.selecteerMutualiteit(m_model.getMutualiteiten().front()->getId());
}

Universum::~Universum()
{
}

void Universum::afsluiten()
{
    teardownArts();
    teardownDossier();
    teardownMutualiteit();
    teardownInstellingen();
    if (m_gewijzigd)
        m_view.bewarenBijAfsluiten();
}

void Universum::bewaren()
{
    m_model.bewaren();
    m_view.markeerArtsenLijstStatus(false);
    m_view.markeerKlantenLijstStatus(false);
    m_view.markeerMutualiteitenLijstStatus(false);
    m_gewijzigd = false;
}

void Universum::etiketten()
{
    setupEtiketten();
    connect(m_view.getEtiketten().b_afdrukken, SIGNAL(clicked()), this, SLOT(afdrukkenEtiketten()));
    connect(m_view.getEtiketten().b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerEtiketten()));
    m_view.getEtiketten().exec();
    disconnect(m_view.getEtiketten().b_afdrukken, SIGNAL(clicked()), this, SLOT(afdrukkenEtiketten()));
    disconnect(m_view.getEtiketten().b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerEtiketten()));
}

void Universum::afdrukkenEtiketten()
{
    teardownEtiketten();
    m_view.getEtiketten().hide();
    QPrintDialog printDialog(&m_view);
    if (printDialog.exec() != QDialog::Accepted)
        return;

    if (QPrinter *printer = printDialog.printer())
    {
        QPainter painter(printer);

    }
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
    Model::Instellingen &modelInstellingen = m_model.getInstellingen();
    View::Instellingen &viewInstellingen = m_view.getInstellingen();
    Q_ASSERT(modelInstellingen);
    viewInstellingen.setNaam(modelInstellingen.getNaam());
    viewInstellingen.setStraat(modelInstellingen.getStraat());
    viewInstellingen.setPostcode(modelInstellingen.getPostcode());
    viewInstellingen.setGemeente(modelInstellingen.getGemeente());
    viewInstellingen.setTelefoon(modelInstellingen.getTelefoon());
    viewInstellingen.setGsm(modelInstellingen.getGsm());
    viewInstellingen.setEmail(modelInstellingen.getEmail());
    viewInstellingen.setOnderschrift(modelInstellingen.getOnderschrift());
    viewInstellingen.setRiziv(modelInstellingen.getRiziv());
    viewInstellingen.setBtwPercentage(modelInstellingen.getBtwPercentage());
    viewInstellingen.setBtwNummer(modelInstellingen.getBtwNummer());
    viewInstellingen.setRekeningNummer(modelInstellingen.getRekeningNummer());
}

void Universum::teardownEtiketten()
{
}

void Universum::teardownInstellingen()
{
    Model::Instellingen &modelInstellingen = m_model.getInstellingen();
    View::Instellingen &viewInstellingen = m_view.getInstellingen();
    Q_ASSERT(modelInstellingen);
    modelInstellingen.setNaam(viewInstellingen.getNaam());
    modelInstellingen.setStraat(viewInstellingen.getStraat());
    modelInstellingen.setPostcode(viewInstellingen.getPostcode());
    modelInstellingen.setGemeente(viewInstellingen.getGemeente());
    modelInstellingen.setTelefoon(viewInstellingen.getTelefoon());
    modelInstellingen.setGsm(viewInstellingen.getGsm());
    modelInstellingen.setEmail(viewInstellingen.getEmail());
    modelInstellingen.setOnderschrift(viewInstellingen.getOnderschrift());
    modelInstellingen.setRiziv(viewInstellingen.getRiziv());
    modelInstellingen.setBtwPercentage(viewInstellingen.getBtwPercentage());
    modelInstellingen.setBtwNummer(viewInstellingen.getBtwNummer());
    modelInstellingen.setRekeningNummer(viewInstellingen.getRekeningNummer());
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

void Universum::cleanupArtsTab()
{
    m_view.m_artsNaam->setText("");
    m_view.m_artsVoornaam->setText("");
    m_view.m_artsStraat->setText("");
    m_view.m_artsPostcode->setValue(1000);
    m_view.m_artsGemeente->setText("");
    m_view.m_artsTelefoon->setText("");
    m_view.m_artsEmail->setText("");
    m_view.m_artsOpmerkingen->setText("");
    m_view.g_artsgegevens->setEnabled(false);
    m_view.b_artsVerwijderen->setEnabled(false);
}

void Universum::cleanupDossierTab()
{
    m_view.m_aanspreektitel->setCurrentIndex(-1);
    m_view.m_klantNaam->setText("");
    m_view.m_klantVoornaam->setText("");
    m_view.m_klantStraat->setText("");
    m_view.m_klantPostcode->setValue(1000);
    m_view.m_klantGemeente->setText("");
    m_view.m_klantTelefoon->setText("");
    m_view.m_klantGeboorteDatum->setDate(m_model.getInvalidDate());
    m_view.m_klantMutualiteit->setCurrentIndex(-1);
    m_view.m_aansluitingsnummer->setText("");
    m_view.m_plaatsAanpassing->setText("");
    m_view.m_klantOpmerkingen->setText("");
    m_view.m_datumProef->setDate(m_model.getInvalidDate());
    m_view.m_datumNKO->setDate(m_model.getInvalidDate());
    m_view.m_datumAdviseur->setDate(m_model.getInvalidDate());
    m_view.m_datumMutualiteit->setDate(m_model.getInvalidDate());
    m_view.m_datumBetaling->setDate(m_model.getInvalidDate());
    m_view.m_datumAflevering->setDate(m_model.getInvalidDate());
    m_view.m_datumWissel->setDate(m_model.getInvalidDate());
    m_view.m_datumOnderhoudsContract->setDate(m_model.getInvalidDate());
    m_view.m_datumOnderzoek->setDate(m_model.getInvalidDate());
    m_view.m_klantArts->setCurrentIndex(-1);
    m_view.m_linkerHoorapparaatMerk->setCurrentIndex(-1);
    m_view.m_linkerHoorapparaatType->setCurrentIndex(-1);
    m_view.m_linkerHoorapparaatSerienummer->setText("");
    m_view.m_linkerHoorapparaatPrijs->setText("");
    m_view.m_rechterHoorapparaatMerk->setCurrentIndex(-1);
    m_view.m_rechterHoorapparaatType->setCurrentIndex(-1);
    m_view.m_rechterHoorapparaatSerienummer->setText("");
    m_view.m_rechterHoorapparaatPrijs->setText("");
    m_view.g_klantgegevens->setEnabled(false);
    m_view.g_datums->setEnabled(false);
    m_view.g_brieven->setEnabled(false);
    m_view.g_hoorapparaten->setEnabled(false);
    m_view.g_meetgegevens->setEnabled(false);
    m_view.g_klantArts->setEnabled(false);
    m_view.b_dossierVerwijderen->setEnabled(false);
}

void Universum::cleanupMutualiteitTab()
{
    m_view.m_mutualiteitNaam->setText("");
    m_view.m_mutualiteitStraat->setText("");
    m_view.m_mutualiteitPostcode->setValue(1000);
    m_view.m_mutualiteitGemeente->setText("");
    m_view.m_mutualiteitTelefoon->setText("");
    m_view.m_mutualiteitEmail->setText("");
    m_view.m_mutualiteitOpmerkingen->setText("");
    m_view.g_mutualiteitsgegevens->setEnabled(false);
    m_view.b_mutualiteitVerwijderen->setEnabled(false);
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
    m_view.markeerArtsenLijstStatus(true);
    m_gewijzigd = true;
}

void Universum::verwijderDossier(int id)
{
    if (m_dossierPresenter)
    {
        delete m_dossierPresenter;
        m_dossierPresenter = 0;
    }
    m_model.verwijderenDossier(id);
    m_view.markeerKlantenLijstStatus(true);
    m_gewijzigd = true;
}

void Universum::verwijderMutualiteit(int id)
{
    if (m_mutualiteitPresenter)
    {
        delete m_mutualiteitPresenter;
        m_mutualiteitPresenter = 0;
    }
    m_model.verwijderenMutualiteit(id);
    m_view.markeerMutualiteitenLijstStatus(true);
    m_gewijzigd = true;
}

void Universum::toevoegenArts(QString voornaam, QString naam)
{
    Model::Arts *arts = m_model.toevoegenArts(voornaam, naam);
    Q_ASSERT(arts);
    m_view.markeerArtsenLijstStatus(true);
    m_view.toevoegenArts(arts->getId(), arts->getNaam() + " " + arts->getVoornaam(), arts->getStraat(), arts->getPostcode(), arts->getGemeente());
    m_view.selecteerArts(arts->getId());
    m_gewijzigd = true;
}

void Universum::toevoegenDossier(QString voornaam, QString naam)
{
    Model::Dossier *dossier = m_model.toevoegenDossier(voornaam, naam);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.markeerKlantenLijstStatus(true);
    m_view.toevoegenKlant(dossier->getId(), klant.getNaam() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());
    m_view.selecteerKlant(dossier->getId());
    m_gewijzigd = true;
}

void Universum::toevoegenMutualiteit(QString naam)
{
    Model::Mutualiteit *mutualiteit = m_model.toevoegenMutualiteit(naam);
    Q_ASSERT(mutualiteit);
    m_view.markeerMutualiteitenLijstStatus(true);
    m_view.toevoegenMutualiteit(mutualiteit->getId(), mutualiteit->getNaam(), mutualiteit->getStraat(), mutualiteit->getPostcode(), mutualiteit->getGemeente());
    m_view.selecteerMutualiteit(mutualiteit->getId());
    m_gewijzigd = true;
}

void Universum::artsGewijzigd(int id)
{
    Model::Arts *arts = m_model.getArts(id);
    Q_ASSERT(arts);
    m_view.markeerArtsenLijstStatus(true);
    m_view.wijzigenArts(arts->getId(), arts->getNaam() + " " + arts->getVoornaam(), arts->getStraat(), arts->getPostcode(), arts->getGemeente());
    m_gewijzigd = true;
}

void Universum::dossierGewijzigd(int id)
{
    Model::Dossier *dossier = m_model.getDossier(id);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.markeerKlantenLijstStatus(true);
    m_view.wijzigenKlant(dossier->getId(), klant.getNaam() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostcode(), klant.getGemeente());
    m_gewijzigd = true;
}

void Universum::mutualiteitGewijzigd(int id)
{
    Model::Mutualiteit *mutualiteit = m_model.getMutualiteit(id);
    Q_ASSERT(mutualiteit);
    m_view.markeerMutualiteitenLijstStatus(true);
    m_view.wijzigenMutualiteit(mutualiteit->getId(), mutualiteit->getNaam(), mutualiteit->getStraat(), mutualiteit->getPostcode(), mutualiteit->getGemeente());
    m_gewijzigd = true;
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
    cleanupArtsTab();

    if (Model::Arts *artsModel = m_model.getArts(m_arts))
    {
        m_view.g_artsgegevens->setEnabled(true);
        m_view.b_artsVerwijderen->setEnabled(true);
        m_artsPresenter = new Presenter::Arts(m_view.getArts(), *artsModel);
        m_artsPresenter->setup();
        connect(m_artsPresenter, SIGNAL(artsGewijzigd(int)), this, SLOT(artsGewijzigd(int)));
    }
}

void Universum::setupDossier()
{
    cleanupDossierTab();

    if (Model::Dossier *dossierModel = m_model.getDossier(m_dossier))
    {
        m_view.g_klantgegevens->setEnabled(true);
        m_view.g_datums->setEnabled(true);
        m_view.g_brieven->setEnabled(true);
        m_view.g_hoorapparaten->setEnabled(true);
        m_view.g_meetgegevens->setEnabled(true);
        m_view.g_klantArts->setEnabled(true);
        m_view.b_dossierVerwijderen->setEnabled(true);
        m_dossierPresenter = new Presenter::Dossier(m_view.getDossier(), *dossierModel);
        m_dossierPresenter->attachToUniversum(&m_model);
        m_dossierPresenter->setup();
        connect(m_dossierPresenter, SIGNAL(dossierGewijzigd(int)), this, SLOT(dossierGewijzigd(int)));
        connect(m_dossierPresenter, SIGNAL(destroyed()), this, SLOT(hoorapparaatGewijzigd()));
    }
}

void Universum::setupMutualiteit()
{
    cleanupMutualiteitTab();

    if (Model::Mutualiteit *mutualiteitModel = m_model.getMutualiteit(m_mutualiteit))
    {
        m_view.g_mutualiteitsgegevens->setEnabled(true);
        m_view.b_mutualiteitVerwijderen->setEnabled(true);
        m_mutualiteitPresenter = new Presenter::Mutualiteit(m_view.getMutualiteit(), *mutualiteitModel);
        m_mutualiteitPresenter->setup();
        connect(m_mutualiteitPresenter, SIGNAL(mutualiteitGewijzigd(int)), this, SLOT(mutualiteitGewijzigd(int)));
    }
}
