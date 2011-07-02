#include "presenter_universe.h"
#include "presenter_physician.h"
#include "presenter_file.h"
#include "presenter_insurancecompany.h"
#include "presenter_labels.h"
#include "presenter_settings.h"
#include "../model/model_physician.h"
#include "../model/model_file.h"
#include "../model/model_insurancecompany.h"
#include "../model/model_universe.h"
#include "../view/view_universe.h"

using namespace Presenter;

Universe::Universe(View::Universe &view, Model::Universe &model)
: m_view(view)
, m_model(model)
, m_physicianPresenter(0)
, m_filePresenter(0)
, m_insuranceCompanyPresenter(0)
, m_arts(0)
, m_file(0)
, m_insuranceCompany(0)
, m_changed(false)
{
    connect(&m_view, SIGNAL(exitSignal()), this, SLOT(exit()));
    connect(&m_view, SIGNAL(saveSignal()), this, SLOT(save()));
    connect(&m_view, SIGNAL(openLabels()), this, SLOT(openLabels()));
    connect(&m_view, SIGNAL(openSettings()), this, SLOT(openSettings()));
    connect(&m_view, SIGNAL(artsSelectieSignal(int)), this, SLOT(showPhysician(int)));
    connect(&m_view, SIGNAL(artsVerwijderenSignal(int)), this, SLOT(removePhysician(int)));
    connect(&m_view, SIGNAL(artsToevoegenSignal(QString, QString)), this, SLOT(addPhysician(QString, QString)));
    connect(&m_view, SIGNAL(klantSelectieSignal(int)), this, SLOT(showFile(int)));
    connect(&m_view, SIGNAL(klantVerwijderenSignal(int)), this, SLOT(removeFile(int)));
    connect(&m_view, SIGNAL(klantToevoegenSignal(QString, QString)), this, SLOT(addFile(QString, QString)));
    connect(&m_view, SIGNAL(mutualiteitSelectieSignal(int)), this, SLOT(showInsuranceCompany(int)));
    connect(&m_view, SIGNAL(mutualiteitVerwijderenSignal(int)), this, SLOT(removeInsuranceCompany(int)));
    connect(&m_view, SIGNAL(mutualiteitToevoegenSignal(QString)), this, SLOT(addInsuranceCompany(QString)));
    connect(&m_view, SIGNAL(closeFileTab()), this, SLOT(teardownFile()));
    connect(&m_view, SIGNAL(closePhysicianTab()), this, SLOT(teardownPhysician()));
    connect(&m_view, SIGNAL(closeInsuranceCompanyTab()), this, SLOT(teardownInsuranceCompany()));
    connect(&m_view, SIGNAL(openArtsTab()), this, SLOT(setupPhysician()));
    connect(&m_view, SIGNAL(openDossierTab()), this, SLOT(setupFile()));
    connect(&m_view, SIGNAL(openMutualiteitTab()), this, SLOT(setupInsuranceCompany()));

    refreshPhysicianList();
    refreshHoorapparatenLijst();
    refreshKlantenLijst();
    refreshInsuranceCompanyList();

    m_view.cleanupTabPhysician();
    if (!m_model.getPhysicians().empty())
        m_view.selectPhysician(m_model.getPhysicians().front()->getId());

    m_view.cleanupTabFile(m_model.getInvalidDate());
    if (!m_model.getFiles().empty())
        m_view.selectCustomer(m_model.getFiles().front()->getId());

    m_view.cleanupTabInsuranceCompany();
    if (!m_model.getInsuranceCompanies().empty())
        m_view.selectInsuranceCompany(m_model.getInsuranceCompanies().front()->getId());
}

Universe::~Universe()
{
}

void Universe::exit()
{
    teardownPhysician();
    teardownFile();
    teardownInsuranceCompany();
    if (m_changed)
        m_view.saveAtExit();
}

void Universe::save()
{
    m_model.save();
    m_view.setPhysicianListChanged(false);
    m_view.setFileListChanged(false);
    m_view.setInsuranceCompanyListChanged(false);
    m_changed = false;
}

void Universe::openSettings()
{
    Settings settings(m_view.getSettings(), m_model.getSettings());
    settings.setup();
    if (m_view.getSettings().exec() == QDialog::Accepted)
        settings.teardown();
}

void Universe::openLabels()
{
    Labels labels(m_view.getLabels(), m_model);
    labels.setup();
    if (m_view.getLabels().exec() == QDialog::Accepted)
        labels.teardown();
}

void Universe::refreshPhysicianList()
{
    m_view.clearPhysicianList();
    const QVector<Model::Physician *> &artsen = m_model.getPhysicians();
    for (QVector<Model::Physician *>::const_iterator itArts = artsen.begin(); itArts != artsen.end(); ++itArts)
    {
        Q_ASSERT(*itArts);
        Model::Physician &arts = *(*itArts);
        m_view.addPhysician(arts.getId(), arts.getName() + " " + arts.getFirstName(), arts.getStreet(), arts.getPostalCode(), arts.getCity());
    }
} 

void Universe::refreshHoorapparatenLijst()
{
    m_view.leegHoorapparatenLijst();
    const QVector<Model::File *> &dossiers = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        m_view.toevoegenHoorapparaat(dossier->getRightHearingAidBrand(), dossier->getRightHearingAidType(), dossier->getRightHearingAidPrice(), dossier->getTrialDate());
        m_view.toevoegenHoorapparaat(dossier->getLeftHearingAidBrand(), dossier->getLeftHearingAidType(), dossier->getLeftHearingAidPrice(), dossier->getTrialDate());
    }
}

void Universe::refreshKlantenLijst()
{
    m_view.leegKlantenLijst();
    const QVector<Model::File *> &dossiers = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        Model::Customer &klant = dossier->getCustomer();
        m_view.addCustomer(dossier->getId(), klant.getName() + " " + klant.getFirstName(), klant.getStreet(), klant.getPostalCode(), klant.getCity());
    }
} 

void Universe::refreshInsuranceCompanyList()
{
    m_view.clearInsuranceCompanyList();
    const QVector<Model::InsuranceCompany *> &mutualiteiten = m_model.getInsuranceCompanies();
    for (QVector<Model::InsuranceCompany *>::const_iterator itMutualiteit = mutualiteiten.begin(); itMutualiteit != mutualiteiten.end(); ++itMutualiteit)
    {
        Q_ASSERT(*itMutualiteit);
        Model::InsuranceCompany &mutualiteit = *(*itMutualiteit);
        m_view.addInsuranceCompany(mutualiteit.getId(), mutualiteit.getName(), mutualiteit.getStreet(), mutualiteit.getPostalCode(), mutualiteit.getCity());
    }
}

void Universe::showPhysician(int id)
{
    teardownPhysician();
    m_arts = id;
    setupPhysician();
}

void Universe::showFile(int id)
{
    teardownFile();
    m_file = id;
    setupFile();
    }

void Universe::showInsuranceCompany(int id)
{
    teardownInsuranceCompany();
    m_insuranceCompany = id;
    setupInsuranceCompany();
}

void Universe::removePhysician(int id)
{
    if (m_physicianPresenter)
    {
        delete m_physicianPresenter;
        m_physicianPresenter = 0;
    }
    m_model.removePhysician(id);
    m_view.setPhysicianListChanged(true);
    m_changed = true;
}

void Universe::removeFile(int id)
{
    if (m_filePresenter)
    {
        delete m_filePresenter;
        m_filePresenter = 0;
    }
    m_model.removeFile(id);
    m_view.setFileListChanged(true);
    m_changed = true;
}

void Universe::removeInsuranceCompany(int id)
{
    if (m_insuranceCompanyPresenter)
    {
        delete m_insuranceCompanyPresenter;
        m_insuranceCompanyPresenter = 0;
    }
    m_model.removeInsuranceCompany(id);
    m_view.setInsuranceCompanyListChanged(true);
    m_changed = true;
}

void Universe::addPhysician(QString voornaam, QString naam)
{
    Model::Physician *physician = m_model.addPhysician(voornaam, naam);
    Q_ASSERT(physician);
    m_view.setPhysicianListChanged(true);
    m_view.addPhysician(physician->getId(), physician->getName() + " " + physician->getFirstName(), physician->getStreet(), physician->getPostalCode(), physician->getCity());
    m_view.selectPhysician(physician->getId());
    m_changed = true;
}

void Universe::addFile(QString firstName, QString name)
{
    Model::File *file = m_model.addFile(firstName, name);
    Q_ASSERT(file);
    const Model::Customer &customer = file->getCustomer();
    m_view.setFileListChanged(true);
    m_view.addCustomer(file->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
    m_view.selectCustomer(file->getId());
    m_changed = true;
}

void Universe::addInsuranceCompany(QString naam)
{
    Model::InsuranceCompany *insuranceCompany = m_model.addInsuranceCompany(naam);
    Q_ASSERT(insuranceCompany);
    m_view.setInsuranceCompanyListChanged(true);
    m_view.addInsuranceCompany(insuranceCompany->getId(), insuranceCompany->getName(), insuranceCompany->getStreet(), insuranceCompany->getPostalCode(), insuranceCompany->getCity());
    m_view.selectInsuranceCompany(insuranceCompany->getId());
    m_changed = true;
}

void Universe::editedPhysician(int id)
{
    Model::Physician *physician = m_model.getPhysician(id);
    Q_ASSERT(physician);
    m_view.setPhysicianListChanged(true);
    m_view.changePhysician(physician->getId(), physician->getName() + " " + physician->getFirstName(), physician->getStreet(), physician->getPostalCode(), physician->getCity());
    m_changed = true;
}

void Universe::editedFile(int id)
{
    Model::File *dossier = m_model.getFile(id);
    Q_ASSERT(dossier);
    const Model::Customer &customer = dossier->getCustomer();
    m_view.setFileListChanged(true);
    m_view.changeCustomer(dossier->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
    m_changed = true;
}

void Universe::editedInsuranceCompany(int id)
{
    Model::InsuranceCompany *insuranceCompany = m_model.getInsuranceCompany(id);
    Q_ASSERT(insuranceCompany);
    m_view.setInsuranceCompanyListChanged(true);
    m_view.changeInsuranceCompany(insuranceCompany->getId(), insuranceCompany->getName(), insuranceCompany->getStreet(), insuranceCompany->getPostalCode(), insuranceCompany->getCity());
    m_changed = true;
}

void Universe::hoorapparaatGewijzigd()
{
    refreshHoorapparatenLijst();
}

void Universe::teardownPhysician()
{
    if (!m_physicianPresenter)
        return;
    m_physicianPresenter->teardown();
    disconnect(this, SLOT(editedPhysician(int)));
    delete m_physicianPresenter;
    m_physicianPresenter = 0;
}

void Universe::teardownFile()
{
    if (!m_filePresenter)
        return;
    m_filePresenter->teardown();
    disconnect(this, SLOT(editedFile(int)));
    delete m_filePresenter;
    m_filePresenter = 0;
}

void Universe::teardownInsuranceCompany()
{
    if (!m_insuranceCompanyPresenter)
        return;
    m_insuranceCompanyPresenter->teardown();
    disconnect(this, SLOT(editedInsuranceCompany(int)));
    delete m_insuranceCompanyPresenter;
    m_insuranceCompanyPresenter = 0;
}

void Universe::setupPhysician()
{
    m_view.cleanupTabPhysician();

    if (Model::Physician *artsModel = m_model.getPhysician(m_arts))
    {
        m_physicianPresenter = new Presenter::Physician(m_view.getPhysician(), *artsModel);
        m_physicianPresenter->setup();
        connect(m_physicianPresenter, SIGNAL(edited(int)), this, SLOT(editedPhysician(int)));
        m_view.enableWidgetsForPhysician();
    }
}

void Universe::setupFile()
{
    m_view.cleanupTabFile(m_model.getInvalidDate());

    if (Model::File *dossierModel = m_model.getFile(m_file))
    {
        m_filePresenter = new Presenter::File(m_view.getFile(), *dossierModel);
        m_filePresenter->setup();
        connect(m_filePresenter, SIGNAL(edited(int)), this, SLOT(editedFile(int)));
        connect(m_filePresenter, SIGNAL(destroyed()), this, SLOT(hoorapparaatGewijzigd()));
        m_view.enableWidgetsForCustomer();
    }
}

void Universe::setupInsuranceCompany()
{
    m_view.cleanupTabInsuranceCompany();

    if (Model::InsuranceCompany *mutualiteitModel = m_model.getInsuranceCompany(m_insuranceCompany))
    {
        m_insuranceCompanyPresenter = new Presenter::InsuranceCompany(m_view.getInsuranceCompany(), *mutualiteitModel);
        m_insuranceCompanyPresenter->setup();
        connect(m_insuranceCompanyPresenter, SIGNAL(edited(int)), this, SLOT(editedInsuranceCompany(int)));
        m_view.enableWidgetsForInsuranceCompany();
    }
}
