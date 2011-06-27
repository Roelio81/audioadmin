#include "presenter_universe.h"
#include "presenter_physician.h"
#include "presenter_file.h"
#include "presenter_insurancecompany.h"
#include "../model/model_physician.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_insurance.h"
#include "../model/model_universe.h"
#include "../view/view_universe.h"

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

using namespace Presenter;

Universum::Universum(View::Universe &view, Model::Universe &model)
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
    connect(&m_view, SIGNAL(artsVerwijderenSignal(int)), this, SLOT(verwijderArts(int)));
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
    connect(&m_view, SIGNAL(openArtsTab()), this, SLOT(setupPhysician()));
    connect(&m_view, SIGNAL(openDossierTab()), this, SLOT(setupFile()));
    connect(&m_view, SIGNAL(openMutualiteitTab()), this, SLOT(setupInsuranceCompany()));

    refreshArtsenLijst();
    refreshHoorapparatenLijst();
    refreshKlantenLijst();
    refreshMutualiteitenLijst();

    m_view.cleanupTabPhysician();
    if (!m_model.getArtsen().empty())
        m_view.selecteerArts(m_model.getArtsen().front()->getId());

    m_view.cleanupTabFile(m_model.getInvalidDate());
    if (!m_model.getDossiers().empty())
        m_view.selecteerKlant(m_model.getDossiers().front()->getId());

    m_view.cleanupTabInsuranceCompany();
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
    QVector<Model::File *> &dossiers = m_model.getDossiers();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        viewEtiketten.toevoegenPlaatsAanpassing(dossier->getPlaatsAanpassing());
    }
    viewEtiketten.setDatumOnderzoek(QDate::currentDate().addYears(-2));
}

void Universum::setupInstellingen()
{
    Model::Settings &modelInstellingen = m_model.getSettings();
    View::Instellingen &viewInstellingen = m_view.getInstellingen();
    viewInstellingen.setNaam(modelInstellingen.getName());
    viewInstellingen.setStraat(modelInstellingen.getStreet());
    viewInstellingen.setPostcode(modelInstellingen.getPostalCode());
    viewInstellingen.setGemeente(modelInstellingen.getCity());
    viewInstellingen.setTelefoon(modelInstellingen.getTelephone());
    viewInstellingen.setGsm(modelInstellingen.getMobilePhone());
    viewInstellingen.setEmail(modelInstellingen.getEmail());
    viewInstellingen.setOnderschrift(modelInstellingen.getOnderschrift());
    viewInstellingen.setRiziv(modelInstellingen.getRiziv());
    viewInstellingen.setBtwPercentage(modelInstellingen.getVATPercentage());
    viewInstellingen.setBtwNummer(modelInstellingen.getBtwNummer());
    viewInstellingen.setRekeningNummer(modelInstellingen.getRekeningNummer());
}

void Universum::teardownEtiketten()
{
}

void Universum::teardownInstellingen()
{
    Model::Settings &modelInstellingen = m_model.getSettings();
    View::Instellingen &viewInstellingen = m_view.getInstellingen();
    modelInstellingen.setName(viewInstellingen.getNaam());
    modelInstellingen.setStreet(viewInstellingen.getStraat());
    modelInstellingen.setPostalCode(viewInstellingen.getPostcode());
    modelInstellingen.setCity(viewInstellingen.getGemeente());
    modelInstellingen.setTelephone(viewInstellingen.getTelefoon());
    modelInstellingen.setMobilePhone(viewInstellingen.getGsm());
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
    QVector<Model::Physician *> &artsen = m_model.getArtsen();
    for (QVector<Model::Physician *>::const_iterator itArts = artsen.begin(); itArts != artsen.end(); ++itArts)
    {
        Q_ASSERT(*itArts);
        Model::Physician &arts = *(*itArts);
        m_view.toevoegenArts(arts.getId(), arts.getName() + " " + arts.getFirstName(), arts.getStraat(), arts.getPostalCode(), arts.getCity());
    }
} 

void Universum::refreshHoorapparatenLijst()
{
    m_view.leegHoorapparatenLijst();
    QVector<Model::File *> &dossiers = m_model.getDossiers();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        m_view.toevoegenHoorapparaat(dossier->getRechterHoorapparaatMerk(), dossier->getRechterHoorapparaatType(), dossier->getRechterHoorapparaatPrijs(), dossier->getProefDatum());
        m_view.toevoegenHoorapparaat(dossier->getLinkerHoorapparaatMerk(), dossier->getLinkerHoorapparaatType(), dossier->getLinkerHoorapparaatPrijs(), dossier->getProefDatum());
    }
}

void Universum::refreshKlantenLijst()
{
    m_view.leegKlantenLijst();
    QVector<Model::File *> &dossiers = m_model.getDossiers();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        Model::Klant &klant = dossier->getKlant();
        m_view.toevoegenKlant(dossier->getId(), klant.getName() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostalCode(), klant.getCity());
    }
} 

void Universum::refreshMutualiteitenLijst()
{
    m_view.leegMutualiteitenLijst();
    QVector<Model::InsuranceCompany *> &mutualiteiten = m_model.getMutualiteiten();
    for (QVector<Model::InsuranceCompany *>::const_iterator itMutualiteit = mutualiteiten.begin(); itMutualiteit != mutualiteiten.end(); ++itMutualiteit)
    {
        Q_ASSERT(*itMutualiteit);
        Model::InsuranceCompany &mutualiteit = *(*itMutualiteit);
        m_view.toevoegenMutualiteit(mutualiteit.getId(), mutualiteit.getName(), mutualiteit.getStraat(), mutualiteit.getPostalCode(), mutualiteit.getCity());
    }
}

void Universum::toonArts(int id)
{
    teardownArts();
    m_arts = id;
    setupPhysician();
}

void Universum::toonDossier(int id)
{
    teardownDossier();
    m_dossier = id;
    setupFile();
    }

void Universum::toonMutualiteit(int id)
{
    teardownMutualiteit();
    m_mutualiteit = id;
    setupInsuranceCompany();
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
    Model::Physician *arts = m_model.toevoegenArts(voornaam, naam);
    Q_ASSERT(arts);
    m_view.markeerArtsenLijstStatus(true);
    m_view.toevoegenArts(arts->getId(), arts->getName() + " " + arts->getFirstName(), arts->getStraat(), arts->getPostalCode(), arts->getCity());
    m_view.selecteerArts(arts->getId());
    m_gewijzigd = true;
}

void Universum::toevoegenDossier(QString voornaam, QString naam)
{
    Model::File *dossier = m_model.toevoegenDossier(voornaam, naam);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.markeerKlantenLijstStatus(true);
    m_view.toevoegenKlant(dossier->getId(), klant.getName() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostalCode(), klant.getCity());
    m_view.selecteerKlant(dossier->getId());
    m_gewijzigd = true;
}

void Universum::toevoegenMutualiteit(QString naam)
{
    Model::InsuranceCompany *mutualiteit = m_model.toevoegenMutualiteit(naam);
    Q_ASSERT(mutualiteit);
    m_view.markeerMutualiteitenLijstStatus(true);
    m_view.toevoegenMutualiteit(mutualiteit->getId(), mutualiteit->getName(), mutualiteit->getStraat(), mutualiteit->getPostalCode(), mutualiteit->getCity());
    m_view.selecteerMutualiteit(mutualiteit->getId());
    m_gewijzigd = true;
}

void Universum::editedPhysician(int id)
{
    Model::Physician *arts = m_model.getArts(id);
    Q_ASSERT(arts);
    m_view.markeerArtsenLijstStatus(true);
    m_view.wijzigenArts(arts->getId(), arts->getName() + " " + arts->getFirstName(), arts->getStraat(), arts->getPostalCode(), arts->getCity());
    m_gewijzigd = true;
}

void Universum::editedFile(int id)
{
    Model::File *dossier = m_model.getDossier(id);
    Q_ASSERT(dossier);
    const Model::Klant &klant = dossier->getKlant();
    m_view.markeerKlantenLijstStatus(true);
    m_view.wijzigenKlant(dossier->getId(), klant.getName() + " " + klant.getVoornaam(), klant.getStraat(), klant.getPostalCode(), klant.getCity());
    m_gewijzigd = true;
}

void Universum::editedInsuranceCompany(int id)
{
    Model::InsuranceCompany *mutualiteit = m_model.getMutualiteit(id);
    Q_ASSERT(mutualiteit);
    m_view.markeerMutualiteitenLijstStatus(true);
    m_view.wijzigenMutualiteit(mutualiteit->getId(), mutualiteit->getName(), mutualiteit->getStraat(), mutualiteit->getPostalCode(), mutualiteit->getCity());
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
    disconnect(this, SLOT(editedPhysician(int)));
    delete m_artsPresenter;
    m_artsPresenter = 0;
}

void Universum::teardownDossier()
{
    if (!m_dossierPresenter)
        return;
    m_dossierPresenter->detachFromUniversum();
    m_dossierPresenter->teardown();
    disconnect(this, SLOT(editedFile(int)));
    delete m_dossierPresenter;
    m_dossierPresenter = 0;
}

void Universum::teardownMutualiteit()
{
    if (!m_mutualiteitPresenter)
        return;
    m_mutualiteitPresenter->teardown();
    disconnect(this, SLOT(editedInsuranceCompany(int)));
    delete m_mutualiteitPresenter;
    m_mutualiteitPresenter = 0;
}

void Universum::setupPhysician()
{
    m_view.cleanupTabPhysician();

    if (Model::Physician *artsModel = m_model.getArts(m_arts))
    {
//        m_view.g_artsgegevens->setEnabled(true);
//        m_view.b_artsVerwijderen->setEnabled(true);
        m_artsPresenter = new Presenter::Physician(m_view.getArts(), *artsModel);
        m_artsPresenter->setup();
        connect(m_artsPresenter, SIGNAL(edited(int)), this, SLOT(editedPhysician(int)));
    }
}

void Universum::setupFile()
{
    m_view.cleanupTabFile(m_model.getInvalidDate());

    if (Model::File *dossierModel = m_model.getDossier(m_dossier))
    {
//        m_view.g_klantgegevens->setEnabled(true);
//        m_view.g_datums->setEnabled(true);
//        m_view.g_brieven->setEnabled(true);
//        m_view.g_hoorapparaten->setEnabled(true);
//        m_view.g_meetgegevens->setEnabled(true);
//        m_view.g_klantArts->setEnabled(true);
//        m_view.b_dossierVerwijderen->setEnabled(true);
        m_dossierPresenter = new Presenter::Dossier(m_view.getDossier(), *dossierModel);
        m_dossierPresenter->attachToUniversum(&m_model);
        m_dossierPresenter->setup();
        connect(m_dossierPresenter, SIGNAL(edited(int)), this, SLOT(editedFile(int)));
        connect(m_dossierPresenter, SIGNAL(destroyed()), this, SLOT(hoorapparaatGewijzigd()));
    }
}

void Universum::setupInsuranceCompany()
{
    m_view.cleanupTabInsuranceCompany();

    if (Model::InsuranceCompany *mutualiteitModel = m_model.getMutualiteit(m_mutualiteit))
    {
//        m_view.g_mutualiteitsgegevens->setEnabled(true);
//        m_view.b_mutualiteitVerwijderen->setEnabled(true);
        m_mutualiteitPresenter = new Presenter::InsuranceCompany(m_view.getMutualiteit(), *mutualiteitModel);
        m_mutualiteitPresenter->setup();
        connect(m_mutualiteitPresenter, SIGNAL(edited(int)), this, SLOT(editedInsuranceCompany(int)));
    }
}
