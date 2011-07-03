#include "presenter_letterphysician.h"
#include "../model/model_file.h"
#include "../model/model_physician.h"
#include "../model/model_universe.h"

using namespace Presenter;

LetterPhysician::LetterPhysician(View::Letter &view, Model::Letter &model)
    : Letter(view, model)
{
}

LetterPhysician::~LetterPhysician()
{
}

QString LetterPhysician::getGreeting() const
{
    return "Geachte dokter,";
}

QString LetterPhysician::getAddresseeName() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getPhysician() >= 0);
    Model::Physician *physician = file.getUniverse().getPhysician(file.getPhysician());
    Q_ASSERT(physician);
    return physician->getName() + " " + physician->getFirstName();
}

QString LetterPhysician::getAddresseeStreet() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getPhysician() >= 0);
    Model::Physician *physician = file.getUniverse().getPhysician(file.getPhysician());
    Q_ASSERT(physician);
    return physician->getStreet();
}


QString LetterPhysician::getAddresseeCity() const
{
    const Model::File &file = getModel().getFile();
    Q_ASSERT(file.getPhysician() >= 0);
    Model::Physician *physician = file.getUniverse().getPhysician(file.getPhysician());
    Q_ASSERT(physician);
    return QString::number(physician->getPostalCode()) + " " + physician->getCity();
}

QString LetterPhysician::getDefaultText() const
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
    QDate geboorteDatum = customer.getDateOfBirth();
    if (geboorteDatum != file.getUniverse().getInvalidDate())
    {
        text += " (" + QString(char(0xb0)) + " " + geboorteDatum.toString("dd-MM-yyyy") + "). ";
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
            text += "stereofonische aanpassing met ";
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

    return text;
}
