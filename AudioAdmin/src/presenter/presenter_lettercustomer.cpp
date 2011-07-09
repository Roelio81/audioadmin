#include "presenter_lettercustomer.h"
#include "../model/model_letter.h"
#include "../model/model_file.h"
#include "../model/model_settings.h"
#include "../model/model_customer.h"
#include "../model/model_universe.h"
#include "../view/view_letter.h"

#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

using namespace Presenter;

LetterCustomer::LetterCustomer(View::Letter &view, Model::Letter &model)
    : Letter(view, model)
{
}

LetterCustomer::~LetterCustomer()
{
}

QString LetterCustomer::getGreeting() const
{
    const Model::File &file = getModel().getFile();
    const Model::Customer &customer = file.getCustomer();
    switch (customer.getTitle())
    {
        case Model::Customer::MR:
            return tr("Dear Mr,");
        case Model::Customer::MRS:
            return tr("Dear Mrs,");
    }

    Q_ASSERT(false);
    return tr("Dear,");
}

QString LetterCustomer::getAddresseeName() const
{
    const Model::File &file = getModel().getFile();
    const Model::Customer &customer = file.getCustomer();
    return customer.getName() + " " + customer.getFirstName();
}

QString LetterCustomer::getAddresseeStreet() const
{
    const Model::File &file = getModel().getFile();
    const Model::Customer &customer = file.getCustomer();
    return customer.getStreet();
}

QString LetterCustomer::getAddresseeCity() const
{
    const Model::File &file = getModel().getFile();
    const Model::Customer &customer = file.getCustomer();
    return QString::number(customer.getPostalCode()) + " " + customer.getCity();
}

QString LetterCustomer::getDefaultText() const
{
    const Model::File &file = getModel().getFile();
    QString text;
    if (file.getNofHearingAids() == 1)
        text += tr("Enclosed is a transfer for the imposition of the hearing aid.");
    else
        text += tr("Enclosed is a transfer for the imposition of the hearing aids.");
    text += "  ";
    text += tr("You will also find a second transfer you can use to extend warranty from ... years to 5 years.");
    return text;
}
