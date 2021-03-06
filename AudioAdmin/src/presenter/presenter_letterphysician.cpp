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
    return tr("Dear doctor,");
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

    QString title;
    switch (customer.getTitle())
    {
        case Model::Customer::MR:
            title = tr("Mr");
            break;
        case Model::Customer::MRS:
            title = tr("Mrs");
            break;
    }

    // Determine some chunks of text that will be added to the default letter
    QString text;
    QString nameString = (customer.getName() + " " + customer.getFirstName());
    QDate dateOfBirth = customer.getDateOfBirth();
    QString dateOfBirthString;
    if (dateOfBirth != file.getUniverse().getInvalidDate())
        dateOfBirthString = " (" + QString(char(0xb0)) + " " + dateOfBirth.toString(tr("yyyy-MM-dd")) + ")";
    QString leftBrandAndType = file.getLeftHearingAidBrand() + " " + file.getLeftHearingAidType();
    QString rightBrandAndType = file.getRightHearingAidBrand() + " " + file.getRightHearingAidType();
    bool hasLeftSide = (!leftBrandAndType.trimmed().isEmpty());
    bool hasRightSide = (!rightBrandAndType.trimmed().isEmpty());

    // Create the default text by combining the previously created strings
    text = tr("Enclosed is the test report for hearing correction of %1 %2%3.").arg(title, nameString, dateOfBirthString);
    text += "  ";
    switch (customer.getTitle())
    {
        case Model::Customer::MR:
            {
            if (hasLeftSide && hasRightSide && (leftBrandAndType == rightBrandAndType))
                text += tr("Mr. has opted for a binaural adaptation with the device %1.").arg(leftBrandAndType);
            else if (hasLeftSide && hasRightSide)
                text += tr("Mr. has opted for a binaural adjustment with the devices %1 (right) and %2 (left).").arg(rightBrandAndType, leftBrandAndType);
            else if (hasLeftSide)
                text += tr("Mr. has opted for a monaural adjustment with the device %1 (left).").arg(leftBrandAndType);
            else if (hasRightSide)
                text += tr("Mr. has opted for a monaural adjustment with the device %1 (right).").arg(rightBrandAndType);
            }
            break;
        case Model::Customer::MRS:
            {
            if (hasLeftSide && hasRightSide && (leftBrandAndType == rightBrandAndType))
                text += tr("Mrs. has opted for a binaural adaptation with the device %1.").arg(leftBrandAndType);
            else if (hasLeftSide && hasRightSide)
                text += tr("Mrs. has opted for a binaural adjustment with the devices %1 (right) and %2 (left).").arg(rightBrandAndType, leftBrandAndType);
            else if (hasLeftSide)
                text += tr("Mrs. has opted for a monaural adjustment with the device %1 (left).").arg(leftBrandAndType);
            else if (hasRightSide)
                text += tr("Mrs. has opted for a monaural adjustment with the device %1 (right).").arg(rightBrandAndType);
            }
            break;
    }

    return text;
}
