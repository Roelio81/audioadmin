#include "presenter_letterinsurancecompany.h"
#include "presenter_measurements.h"
#include "../model/model_letter.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_insurancecompany.h"
#include "../model/model_universe.h"
#include "../view/view_letter.h"
#include "../view/view_measurements.h"

using namespace Presenter;

LetterInsuranceCompany::LetterInsuranceCompany(View::Letter &view, Model::Letter &model)
    : Letter(view, model)
{
}

LetterInsuranceCompany::~LetterInsuranceCompany()
{
}

QString LetterInsuranceCompany::getGreeting() const
{
    return "Geachte geneesheer-adviseur,";
}

QString LetterInsuranceCompany::getAddresseeName() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getInsuranceCompany() >= 0);
    Model::InsuranceCompany *insuranceCompany = file.getUniverse().getInsuranceCompany(file.getInsuranceCompany());
    Q_ASSERT(insuranceCompany);
    return insuranceCompany->getName();
}


QString LetterInsuranceCompany::getAddresseeStreet() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getInsuranceCompany() >= 0);
    Model::InsuranceCompany *insuranceCompany = file.getUniverse().getInsuranceCompany(file.getInsuranceCompany());
    Q_ASSERT(insuranceCompany);
    return insuranceCompany->getStreet();
}

QString LetterInsuranceCompany::getAddresseeCity() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getInsuranceCompany() >= 0);
    Model::InsuranceCompany *insuranceCompany = file.getUniverse().getInsuranceCompany(file.getInsuranceCompany());
    Q_ASSERT(insuranceCompany);
    return QString::number(insuranceCompany->getPostalCode()) + " " + insuranceCompany->getCity();
}

QString LetterInsuranceCompany::getDefaultText() const
{
    const Model::File &file = getModel().getFile();
    const Model::Customer &customer = file.getCustomer();

    QString titleUpperCase;
    QString titleLowerCase;
    switch (customer.getTitle())
    {
        case Model::Customer::MR:
            titleUpperCase = "Mijnheer";
            titleLowerCase = "mijnheer";
            break;
        case Model::Customer::MRS:
            titleUpperCase = "Mevrouw";
            titleLowerCase = "mevrouw";
            break;
    }

    QString text = "Ingesloten vindt u het proefrapport ter gehoorcorrectie van ";
    text += titleLowerCase + " " + customer.getName() + " " + customer.getFirstName();
    QDate dateOfBirth = customer.getDateOfBirth();
    if (dateOfBirth != file.getUniverse().getInvalidDate())
    {
        text += " (" + QString(char(0xb0)) + " " + dateOfBirth.toString("dd-MM-yyyy") + "). ";
    }
    if (file.getNofHearingAids() > 0)
    {
        text += titleUpperCase + " heeft geopteerd voor een ";
        if (file.getNofHearingAids() == 1)
        {
            text += "monofonische aanpassing met ";
            if (!file.getLeftHearingAidBrand().isEmpty() || !file.getLeftHearingAidType().isEmpty())
            {
                text += "het apparaat ";
                text += file.getLeftHearingAidBrand() + " " + file.getLeftHearingAidType() + " (links). ";
            }
            else
            {
                text += "het apparaat ";
                text += file.getRightHearingAidBrand() + " " + file.getRightHearingAidType() + " (rechts). ";
            }
        }
        else
        {
            Q_ASSERT(file.getNofHearingAids() == 2);
            text += "stereofonsiche aanpassing met ";
            if (file.getLeftHearingAidBrand() == file.getRightHearingAidBrand() &&
                file.getLeftHearingAidType() == file.getRightHearingAidType())
            {
                text += "het apparaat ";
                text += file.getLeftHearingAidBrand() + " " + file.getLeftHearingAidType() + ". ";
            }
            else
            {
                text += "de apparaten ";
                text += file.getRightHearingAidBrand() + " " + file.getRightHearingAidType() + " (rechts) en ";
                text += file.getLeftHearingAidBrand() + " " + file.getLeftHearingAidType() + " (links). ";
            }
        }
    }
    text += "Gelieve ten spoedigste een goedkeuring te laten geworden op bovenstaan adres.";
    return text;
}
