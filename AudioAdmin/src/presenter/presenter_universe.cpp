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
, m_physician(0)
, m_file(0)
, m_insuranceCompany(0)
, m_changed(false)
{
    connect(&m_view, SIGNAL(exitSignal()), this, SLOT(exit()));
    connect(&m_view, SIGNAL(saveSignal()), this, SLOT(save()));
    connect(&m_view, SIGNAL(openLabels()), this, SLOT(openLabels()));
    connect(&m_view, SIGNAL(openSettings()), this, SLOT(openSettings()));
    connect(&m_view, SIGNAL(selectPhysicianSignal(int)), this, SLOT(showPhysician(int)));
    connect(&m_view, SIGNAL(removePhysicianSignal(int)), this, SLOT(removePhysician(int)));
    connect(&m_view, SIGNAL(addPhysicianSignal(QString, QString)), this, SLOT(addPhysician(QString, QString)));
    connect(&m_view, SIGNAL(selectCustomerSignal(int)), this, SLOT(showFile(int)));
    connect(&m_view, SIGNAL(removeCustomerSignal(int)), this, SLOT(removeFile(int)));
    connect(&m_view, SIGNAL(addCustomerSignal(QString, QString)), this, SLOT(addFile(QString, QString)));
    connect(&m_view, SIGNAL(selectInsuranceCompanySignal(int)), this, SLOT(showInsuranceCompany(int)));
    connect(&m_view, SIGNAL(removeInsuranceCompanySignal(int)), this, SLOT(removeInsuranceCompany(int)));
    connect(&m_view, SIGNAL(addInsuranceCompanySignal(QString)), this, SLOT(addInsuranceCompany(QString)));
    connect(&m_view, SIGNAL(closeFileTab()), this, SLOT(teardownFile()));
    connect(&m_view, SIGNAL(closePhysicianTab()), this, SLOT(teardownPhysician()));
    connect(&m_view, SIGNAL(closeInsuranceCompanyTab()), this, SLOT(teardownInsuranceCompany()));
    connect(&m_view, SIGNAL(openFileTab()), this, SLOT(setupFile()));
    connect(&m_view, SIGNAL(openPhysicianTab()), this, SLOT(setupPhysician()));
    connect(&m_view, SIGNAL(openInsuranceCompanyTab()), this, SLOT(setupInsuranceCompany()));

    refreshPhysicianList();
    refreshHearingAidsList();
    refreshCustomerList();
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
    const QVector<Model::Physician *> &physician = m_model.getPhysicians();
    for (QVector<Model::Physician *>::const_iterator it = physician.begin(); it != physician.end(); ++it)
    {
        Q_ASSERT(*it);
        Model::Physician *physician = *it;
        m_view.addPhysician(physician->getId(), physician->getName() + " " + physician->getFirstName(), physician->getStreet(), physician->getPostalCode(), physician->getCity());
    }
} 

void Universe::refreshHearingAidsList()
{
    m_view.clearHearingAidList();
    const QVector<Model::File *> &files = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator it = files.begin(); it != files.end(); ++it)
    {
        Model::File *file = *it;
        Q_ASSERT(file);
        m_view.addHearingAid(file->getRightHearingAidBrand(), file->getRightHearingAidType(), file->getRightHearingAidPrice(), file->getTrialDate());
        m_view.addHearingAid(file->getLeftHearingAidBrand(), file->getLeftHearingAidType(), file->getLeftHearingAidPrice(), file->getTrialDate());
    }
}

void Universe::refreshCustomerList()
{
    m_view.clearCustomerList();
    const QVector<Model::File *> &files = m_model.getFiles();
    for (QVector<Model::File *>::const_iterator it = files.begin(); it != files.end(); ++it)
    {
        Model::File *file = *it;
        Q_ASSERT(file);
        Model::Customer &customer = file->getCustomer();
        m_view.addCustomer(file->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
    }
} 

void Universe::refreshInsuranceCompanyList()
{
    m_view.clearInsuranceCompanyList();
    const QVector<Model::InsuranceCompany *> &insuranceCompanies = m_model.getInsuranceCompanies();
    for (QVector<Model::InsuranceCompany *>::const_iterator it = insuranceCompanies.begin(); it != insuranceCompanies.end(); ++it)
    {
        Q_ASSERT(*it);
        Model::InsuranceCompany *insuranceCompany = *it;
        m_view.addInsuranceCompany(insuranceCompany->getId(), insuranceCompany->getName(), insuranceCompany->getStreet(), insuranceCompany->getPostalCode(), insuranceCompany->getCity());
    }
}

void Universe::showPhysician(int id)
{
    teardownPhysician();
    m_physician = id;
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

void Universe::addPhysician(QString firstName, QString name)
{
    Model::Physician *physician = m_model.addPhysician(firstName, name);
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

void Universe::addInsuranceCompany(QString name)
{
    Model::InsuranceCompany *insuranceCompany = m_model.addInsuranceCompany(name);
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
    Model::File *file = m_model.getFile(id);
    Q_ASSERT(file);
    const Model::Customer &customer = file->getCustomer();
    m_view.setFileListChanged(true);
    m_view.changeCustomer(file->getId(), customer.getName() + " " + customer.getFirstName(), customer.getStreet(), customer.getPostalCode(), customer.getCity());
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

void Universe::editedHearingAids()
{
    refreshHearingAidsList();
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

    if (Model::Physician *model = m_model.getPhysician(m_physician))
    {
        m_physicianPresenter = new Presenter::Physician(m_view.getPhysician(), *model);
        m_physicianPresenter->setup();
        connect(m_physicianPresenter, SIGNAL(edited(int)), this, SLOT(editedPhysician(int)));
        m_view.enableWidgetsForPhysician();
    }
}

void Universe::setupFile()
{
    m_view.cleanupTabFile(m_model.getInvalidDate());

    if (Model::File *model = m_model.getFile(m_file))
    {
        m_filePresenter = new Presenter::File(m_view.getFile(), *model);
        m_filePresenter->setup();
        connect(m_filePresenter, SIGNAL(edited(int)), this, SLOT(editedFile(int)));
        connect(m_filePresenter, SIGNAL(destroyed()), this, SLOT(editedHearingAids()));
        m_view.enableWidgetsForCustomer();
    }
}

void Universe::setupInsuranceCompany()
{
    m_view.cleanupTabInsuranceCompany();

    if (Model::InsuranceCompany *model = m_model.getInsuranceCompany(m_insuranceCompany))
    {
        m_insuranceCompanyPresenter = new Presenter::InsuranceCompany(m_view.getInsuranceCompany(), *model);
        m_insuranceCompanyPresenter->setup();
        connect(m_insuranceCompanyPresenter, SIGNAL(edited(int)), this, SLOT(editedInsuranceCompany(int)));
        m_view.enableWidgetsForInsuranceCompany();
    }
}
