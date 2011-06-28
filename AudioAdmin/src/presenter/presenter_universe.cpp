#include "presenter_universe.h"
#include "presenter_physician.h"
#include "presenter_file.h"
#include "presenter_insurancecompany.h"
#include "../model/model_physician.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_insurancecompany.h"
#include "../model/model_universe.h"
#include "../view/view_universe.h"

#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

using namespace Presenter;

Universum::Universum(View::Universe &view, Model::Universe &model)
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
    connect(&m_view, SIGNAL(afsluitenSignal()), this, SLOT(afsluiten()));
    connect(&m_view, SIGNAL(bewarenSignal()), this, SLOT(bewaren()));
    connect(&m_view, SIGNAL(etikettenSignal()), this, SLOT(etiketten()));
    connect(&m_view, SIGNAL(openSettings()), this, SLOT(openSettings()));
    connect(&m_view, SIGNAL(artsSelectieSignal(int)), this, SLOT(showPhysician(int)));
    connect(&m_view, SIGNAL(artsVerwijderenSignal(int)), this, SLOT(removePhysician(int)));
    connect(&m_view, SIGNAL(artsToevoegenSignal(QString, QString)), this, SLOT(addPhysician(QString, QString)));
    connect(&m_view, SIGNAL(klantSelectieSignal(int)), this, SLOT(showFile(int)));
    connect(&m_view, SIGNAL(klantVerwijderenSignal(int)), this, SLOT(removeFile(int)));
    connect(&m_view, SIGNAL(klantToevoegenSignal(QString, QString)), this, SLOT(addFile(QString, QString)));
    connect(&m_view, SIGNAL(mutualiteitSelectieSignal(int)), this, SLOT(showInsuranceCompany(int)));
    connect(&m_view, SIGNAL(mutualiteitVerwijderenSignal(int)), this, SLOT(removeInsuranceCompany(int)));
    connect(&m_view, SIGNAL(mutualiteitToevoegenSignal(QString)), this, SLOT(toevoegenMutualiteit(QString)));
    connect(&m_view, SIGNAL(sluitArtsTab()), this, SLOT(teardownPhysician()));
    connect(&m_view, SIGNAL(sluitDossierTab()), this, SLOT(teardownFile()));
    connect(&m_view, SIGNAL(sluitMutualiteitTab()), this, SLOT(teardownInsuranceCompany()));
    connect(&m_view, SIGNAL(openArtsTab()), this, SLOT(setupPhysician()));
    connect(&m_view, SIGNAL(openDossierTab()), this, SLOT(setupFile()));
    connect(&m_view, SIGNAL(openMutualiteitTab()), this, SLOT(setupInsuranceCompany()));

    refreshArtsenLijst();
    refreshHoorapparatenLijst();
    refreshKlantenLijst();
    refreshMutualiteitenLijst();

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

Universum::~Universum()
{
}

void Universum::afsluiten()
{
    teardownPhysician();
    teardownFile();
    teardownInsuranceCompany();
    teardownSettings();
    if (m_changed)
        m_view.bewarenBijAfsluiten();
}

void Universum::bewaren()
{
    m_model.save();
    m_view.setPhysicianListChanged(false);
    m_view.setFileListChanged(false);
    m_view.setInsuranceCompanyListChanged(false);
    m_changed = false;
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

void Universum::openSettings()
{
    setupSettings();
    if (m_view.getInstellingen().exec() == QDialog::Accepted)
        teardownSettings();
}

void Universum::setupEtiketten()
{
    View::Etiketten &viewEtiketten = m_view.getEtiketten();
    viewEtiketten.leegPlaatsenAanpassing();
    const QVector<Model::File *> &dossiers = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        viewEtiketten.toevoegenPlaatsAanpassing(dossier->getPlaatsAanpassing());
    }
    viewEtiketten.setDatumOnderzoek(QDate::currentDate().addYears(-2));
}

void Universum::setupSettings()
{
    Model::Settings &modelSettings = m_model.getSettings();
    View::Settings &viewSettings = m_view.getInstellingen();
    viewSettings.setName(modelSettings.getName());
    viewSettings.setStreet(modelSettings.getStreet());
    viewSettings.setPostalCode(modelSettings.getPostalCode());
    viewSettings.setCity(modelSettings.getCity());
    viewSettings.setTelephone(modelSettings.getTelephone());
    viewSettings.setMobilePhone(modelSettings.getMobilePhone());
    viewSettings.setEmail(modelSettings.getEmail());
    viewSettings.setOnderschrift(modelSettings.getOnderschrift());
    viewSettings.setRiziv(modelSettings.getRiziv());
    viewSettings.setVATPercentage(modelSettings.getVATPercentage());
    viewSettings.setVATNumber(modelSettings.getBtwNummer());
    viewSettings.setRekeningNummer(modelSettings.getRekeningNummer());
}

void Universum::teardownEtiketten()
{
}

void Universum::teardownSettings()
{
    Model::Settings &modelInstellingen = m_model.getSettings();
    View::Settings &viewInstellingen = m_view.getInstellingen();
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
    modelInstellingen.setBtwNummer(viewInstellingen.getVATNumber());
    modelInstellingen.setRekeningNummer(viewInstellingen.getRekeningNummer());
}

void Universum::refreshArtsenLijst()
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

void Universum::refreshHoorapparatenLijst()
{
    m_view.leegHoorapparatenLijst();
    const QVector<Model::File *> &dossiers = m_model.getFiles();
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
    const QVector<Model::File *> &dossiers = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator itDossier = dossiers.begin(); itDossier != dossiers.end(); ++itDossier)
    {
        Model::File *dossier = *itDossier;
        Q_ASSERT(dossier);
        Model::Customer &klant = dossier->getCustomer();
        m_view.addCustomer(dossier->getId(), klant.getName() + " " + klant.getFirstName(), klant.getStreet(), klant.getPostalCode(), klant.getCity());
    }
} 

void Universum::refreshMutualiteitenLijst()
{
    m_view.leegMutualiteitenLijst();
    const QVector<Model::InsuranceCompany *> &mutualiteiten = m_model.getInsuranceCompanies();
    for (QVector<Model::InsuranceCompany *>::const_iterator itMutualiteit = mutualiteiten.begin(); itMutualiteit != mutualiteiten.end(); ++itMutualiteit)
    {
        Q_ASSERT(*itMutualiteit);
        Model::InsuranceCompany &mutualiteit = *(*itMutualiteit);
        m_view.addInsuranceCompany(mutualiteit.getId(), mutualiteit.getName(), mutualiteit.getStreet(), mutualiteit.getPostalCode(), mutualiteit.getCity());
    }
}

void Universum::showPhysician(int id)
{
    teardownPhysician();
    m_arts = id;
    setupPhysician();
}

void Universum::showFile(int id)
{
    teardownFile();
    m_file = id;
    setupFile();
    }

void Universum::showInsuranceCompany(int id)
{
    teardownInsuranceCompany();
    m_insuranceCompany = id;
    setupInsuranceCompany();
}

void Universum::removePhysician(int id)
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

void Universum::removeFile(int id)
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

void Universum::removeInsuranceCompany(int id)
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

void Universum::addPhysician(QString voornaam, QString naam)
{
    Model::Physician *physician = m_model.addPhysician(voornaam, naam);
    Q_ASSERT(physician);
    m_view.setPhysicianListChanged(true);
    m_view.addPhysician(physician->getId(), physician->getName() + " " + physician->getFirstName(), physician->getStreet(), physician->getPostalCode(), physician->getCity());
    m_view.selectPhysician(physician->getId());
    m_changed = true;
}

void Universum::addFile(QString firstName, QString name)
{
    Model::File *file = m_model.addFile(firstName, name);
    Q_ASSERT(file);
    const Model::Customer &customer = file->getCustomer();
    m_view.setFileListChanged(true);
    m_view.addCustomer(file->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
    m_view.selectCustomer(file->getId());
    m_changed = true;
}

void Universum::toevoegenMutualiteit(QString naam)
{
    Model::InsuranceCompany *insuranceCompany = m_model.addInsuranceCompany(naam);
    Q_ASSERT(insuranceCompany);
    m_view.setInsuranceCompanyListChanged(true);
    m_view.addInsuranceCompany(insuranceCompany->getId(), insuranceCompany->getName(), insuranceCompany->getStreet(), insuranceCompany->getPostalCode(), insuranceCompany->getCity());
    m_view.selectInsuranceCompany(insuranceCompany->getId());
    m_changed = true;
}

void Universum::editedPhysician(int id)
{
    Model::Physician *physician = m_model.getPhysician(id);
    Q_ASSERT(physician);
    m_view.setPhysicianListChanged(true);
    m_view.changePhysician(physician->getId(), physician->getName() + " " + physician->getFirstName(), physician->getStreet(), physician->getPostalCode(), physician->getCity());
    m_changed = true;
}

void Universum::editedFile(int id)
{
    Model::File *dossier = m_model.getFile(id);
    Q_ASSERT(dossier);
    const Model::Customer &customer = dossier->getCustomer();
    m_view.setFileListChanged(true);
    m_view.changeCustomer(dossier->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
    m_changed = true;
}

void Universum::editedInsuranceCompany(int id)
{
    Model::InsuranceCompany *insuranceCompany = m_model.getInsuranceCompany(id);
    Q_ASSERT(insuranceCompany);
    m_view.setInsuranceCompanyListChanged(true);
    m_view.wijzigenMutualiteit(insuranceCompany->getId(), insuranceCompany->getName(), insuranceCompany->getStreet(), insuranceCompany->getPostalCode(), insuranceCompany->getCity());
    m_changed = true;
}

void Universum::hoorapparaatGewijzigd()
{
    refreshHoorapparatenLijst();
}

void Universum::teardownPhysician()
{
    if (!m_physicianPresenter)
        return;
    m_physicianPresenter->teardown();
    disconnect(this, SLOT(editedPhysician(int)));
    delete m_physicianPresenter;
    m_physicianPresenter = 0;
}

void Universum::teardownFile()
{
    if (!m_filePresenter)
        return;
    m_filePresenter->teardown();
    disconnect(this, SLOT(editedFile(int)));
    delete m_filePresenter;
    m_filePresenter = 0;
}

void Universum::teardownInsuranceCompany()
{
    if (!m_insuranceCompanyPresenter)
        return;
    m_insuranceCompanyPresenter->teardown();
    disconnect(this, SLOT(editedInsuranceCompany(int)));
    delete m_insuranceCompanyPresenter;
    m_insuranceCompanyPresenter = 0;
}

void Universum::setupPhysician()
{
    m_view.cleanupTabPhysician();

    if (Model::Physician *artsModel = m_model.getPhysician(m_arts))
    {
        m_physicianPresenter = new Presenter::Physician(m_view.getArts(), *artsModel);
        m_physicianPresenter->setup();
        connect(m_physicianPresenter, SIGNAL(edited(int)), this, SLOT(editedPhysician(int)));
        m_view.enableWidgetsForPhysician();
    }
}

void Universum::setupFile()
{
    m_view.cleanupTabFile(m_model.getInvalidDate());

    if (Model::File *dossierModel = m_model.getFile(m_file))
    {
        m_filePresenter = new Presenter::Dossier(m_view.getDossier(), *dossierModel);
        m_filePresenter->setup();
        connect(m_filePresenter, SIGNAL(edited(int)), this, SLOT(editedFile(int)));
        connect(m_filePresenter, SIGNAL(destroyed()), this, SLOT(hoorapparaatGewijzigd()));
        m_view.enableWidgetsForCustomer();
    }
}

void Universum::setupInsuranceCompany()
{
    m_view.cleanupTabInsuranceCompany();

    if (Model::InsuranceCompany *mutualiteitModel = m_model.getInsuranceCompany(m_insuranceCompany))
    {
        m_insuranceCompanyPresenter = new Presenter::InsuranceCompany(m_view.getMutualiteit(), *mutualiteitModel);
        m_insuranceCompanyPresenter->setup();
        connect(m_insuranceCompanyPresenter, SIGNAL(edited(int)), this, SLOT(editedInsuranceCompany(int)));
        m_view.enableWidgetsForInsuranceCompany();
    }
}
