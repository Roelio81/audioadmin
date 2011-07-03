#include "view_customer.h"
#include "view_file.h"
#include "view_universe.h"

using namespace View;

Customer::Customer(File &file)
    : m_ui(file.getUniverse().getUi())
{
}

Customer::~Customer()
{
}

void Customer::clearTitles()
{
    m_ui.m_aanspreektitel->clear();
}

void Customer::addTitle(const QString &value)
{
    m_ui.m_aanspreektitel->addItem(value);
}


QString Customer::getTitle() const
{
    return m_ui.m_aanspreektitel->currentText();
}

QString Customer::getName() const
{
    return m_ui.m_klantNaam->text();
}

QString Customer::getFirstName() const
{
    return m_ui.m_klantVoornaam->text();
}

QString Customer::getStreet() const
{
    return m_ui.m_klantStraat->text();
}

int Customer::getPostalCode() const
{
    return m_ui.m_klantPostcode->value();
}

QString Customer::getCity() const
{
    return m_ui.m_klantGemeente->text();
}

QString Customer::getTelephone() const
{
    return m_ui.m_klantTelefoon->text();
}

QDate Customer::getDateOfBirth() const
{
    return m_ui.m_klantGeboorteDatum->date();
}

QString Customer::getComments() const
{
    return m_ui.m_klantOpmerkingen->toPlainText();
}

void Customer::setTitle(const QString &value)
{
    int index = value.isEmpty() ? 0 : m_ui.m_aanspreektitel->findText(value);
    Q_ASSERT(index >= 0);
    m_ui.m_aanspreektitel->setCurrentIndex(index);
}

void Customer::setName(const QString &value)
{
    m_ui.m_klantNaam->setText(value);
    m_ui.b_meetgegevens->setEnabled(value != "");
    m_ui.b_klantBrief->setEnabled(value != "");
}

void Customer::setFirstName(const QString &value)
{
    m_ui.m_klantVoornaam->setText(value);
}

void Customer::setStreet(const QString &value)
{
    m_ui.m_klantStraat->setText(value);
}

void Customer::setPostalCode(int value)
{
    m_ui.m_klantPostcode->setValue(value);
}

void Customer::setCity(const QString &value)
{
    m_ui.m_klantGemeente->setText(value);
}

void Customer::setTelephone(const QString &value)
{
    m_ui.m_klantTelefoon->setText(value);
}

void Customer::setDateOfBirth(const QDate &value)
{
    m_ui.m_klantGeboorteDatum->setDate(value);
}

void Customer::setComments(const QString &value)
{
    m_ui.m_klantOpmerkingen->setPlainText(value);
}
