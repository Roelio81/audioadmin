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
    m_ui.m_customerTitle->clear();
}

void Customer::addTitle(const QString &value)
{
    m_ui.m_customerTitle->addItem(value);
}


QString Customer::getTitle() const
{
    return m_ui.m_customerTitle->currentText();
}

QString Customer::getName() const
{
    return m_ui.m_customerName->text();
}

QString Customer::getFirstName() const
{
    return m_ui.m_customerFirstName->text();
}

QString Customer::getStreet() const
{
    return m_ui.m_customerStreet->text();
}

int Customer::getPostalCode() const
{
    return m_ui.m_customerPostalCode->value();
}

QString Customer::getCity() const
{
    return m_ui.m_customerCity->text();
}

QString Customer::getTelephone() const
{
    return m_ui.m_customerTelephone->text();
}

QDate Customer::getDateOfBirth() const
{
    return m_ui.m_customerDateOfBirth->date();
}

QString Customer::getComments() const
{
    return m_ui.m_customerComments->toPlainText();
}

void Customer::setTitle(const QString &value)
{
    int index = value.isEmpty() ? 0 : m_ui.m_customerTitle->findText(value);
    Q_ASSERT(index >= 0);
    m_ui.m_customerTitle->setCurrentIndex(index);
}

void Customer::setName(const QString &value)
{
    m_ui.m_customerName->setText(value);
    m_ui.b_measurements->setEnabled(value != "");
    m_ui.b_letterCustomer->setEnabled(value != "");
}

void Customer::setFirstName(const QString &value)
{
    m_ui.m_customerFirstName->setText(value);
}

void Customer::setStreet(const QString &value)
{
    m_ui.m_customerStreet->setText(value);
}

void Customer::setPostalCode(int value)
{
    m_ui.m_customerPostalCode->setValue(value);
}

void Customer::setCity(const QString &value)
{
    m_ui.m_customerCity->setText(value);
}

void Customer::setTelephone(const QString &value)
{
    m_ui.m_customerTelephone->setText(value);
}

void Customer::setDateOfBirth(const QDate &value)
{
    m_ui.m_customerDateOfBirth->setDate(value);
}

void Customer::setComments(const QString &value)
{
    m_ui.m_customerComments->setPlainText(value);
}
