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
            return "Geachte meneer,";
        case Model::Customer::MRS:
            return "Geachte mevrouw,";
    }

    Q_ASSERT(false);
    return "Geachte,";
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
    QString text = "Ingesloten vindt u een overschrijving voor de opleg van ";
    if (file.getNofHearingAids() == 1)
        text += "het hoorapparaat.";
    else
        text += "de hoorapparaten.";
    text += "Tevens vindt u een tweede overschrijving die u kan gebruiken indien u 5 jaar garantie wenst i.p.v. ... jaar.";
    return text;
}
