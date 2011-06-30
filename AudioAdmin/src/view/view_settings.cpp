#include "view_settings.h"

#include <QLineEdit>

using namespace View;

Settings::Settings(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
}

Settings::~Settings()
{
}

QString Settings::getName() const
{
    return m_ui.m_name->text();
}

QString Settings::getStreet() const
{
    return m_ui.m_street->text();
}

int Settings::getPostalCode() const
{
    return m_ui.m_postalCode->value();
}

QString Settings::getCity() const
{
    return m_ui.m_city->text();
}

QString Settings::getTelephone() const
{
    return m_ui.m_telephone->text();
}

QString Settings::getMobilePhone() const
{
    return m_ui.m_mobilePhone->text();
}

QString Settings::getEmail() const
{
    return m_ui.m_email->text();
}

QString Settings::getCaption() const
{
    return m_ui.m_caption->text();
}

QString Settings::getNationalId() const
{
    return m_ui.m_nationalId->text();
}

int Settings::getVATPercentage() const
{
    return m_ui.m_vatPercentage->value();
}

QString Settings::getVATNumber() const
{
    return m_ui.m_vatNumber->text();
}

QString Settings::getBankAccount() const
{
    return m_ui.m_bankAccount->text();
}

void Settings::setName(const QString &value)
{
    m_ui.m_name->setText(value);
}

void Settings::setStreet(const QString &value)
{
    m_ui.m_street->setText(value);
}

void Settings::setPostalCode(const int &value)
{
    m_ui.m_postalCode->setValue(value);
}

void Settings::setCity(const QString &value)
{
    m_ui.m_city->setText(value);
}

void Settings::setTelephone(const QString &value)
{
    m_ui.m_telephone->setText(value);
}

void Settings::setMobilePhone(const QString &value)
{
    m_ui.m_mobilePhone->setText(value);
}

void Settings::setEmail(const QString &value)
{
    m_ui.m_email->setText(value);
}

void Settings::setCaption(const QString &value)
{
    m_ui.m_caption->setText(value);
}

void Settings::setNationalId(const QString &value)
{
    m_ui.m_nationalId->setText(value);
}

void Settings::setVATPercentage(const int &value)
{
    m_ui.m_vatPercentage->setValue(value);
}

void Settings::setVATNumber(const QString &value)
{
    m_ui.m_vatNumber->setText(value);
}

void Settings::setBankAccount(const QString &value)
{
    m_ui.m_bankAccount->setText(value);
}
