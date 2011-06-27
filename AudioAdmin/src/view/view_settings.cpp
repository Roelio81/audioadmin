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

QString Settings::getNaam() const
{
    return m_ui.m_naam->text();
}

QString Settings::getStraat() const
{
    return m_ui.m_straat->text();
}

int Settings::getPostcode() const
{
    return m_ui.m_postcode->value();
}

QString Settings::getGemeente() const
{
    return m_ui.m_gemeente->text();
}

QString Settings::getTelefoon() const
{
    return m_ui.m_telefoon->text();
}

QString Settings::getGsm() const
{
    return m_ui.m_gsm->text();
}

QString Settings::getEmail() const
{
    return m_ui.m_email->text();
}

QString Settings::getOnderschrift() const
{
    return m_ui.m_onderschrift->text();
}

QString Settings::getRiziv() const
{
    return m_ui.m_riziv->text();
}

int Settings::getBtwPercentage() const
{
    return m_ui.m_btwpercentage->value();
}

QString Settings::getVATNumber() const
{
    return m_ui.m_btwnummer->text();
}

QString Settings::getRekeningNummer() const
{
    return m_ui.m_rekeningnummer->text();
}

void Settings::setName(const QString &value)
{
    m_ui.m_naam->setText(value);
}

void Settings::setStreet(const QString &value)
{
    m_ui.m_straat->setText(value);
}

void Settings::setPostalCode(const int &value)
{
    m_ui.m_postcode->setValue(value);
}

void Settings::setCity(const QString &value)
{
    m_ui.m_gemeente->setText(value);
}

void Settings::setTelephone(const QString &value)
{
    m_ui.m_telefoon->setText(value);
}

void Settings::setMobilePhone(const QString &value)
{
    m_ui.m_gsm->setText(value);
}

void Settings::setEmail(const QString &value)
{
    m_ui.m_email->setText(value);
}

void Settings::setOnderschrift(const QString &value)
{
    m_ui.m_onderschrift->setText(value);
}

void Settings::setRiziv(const QString &value)
{
    m_ui.m_riziv->setText(value);
}

void Settings::setVATPercentage(const int &value)
{
    m_ui.m_btwpercentage->setValue(value);
}

void Settings::setVATNumber(const QString &value)
{
    m_ui.m_btwnummer->setText(value);
}

void Settings::setRekeningNummer(const QString &value)
{
    m_ui.m_rekeningnummer->setText(value);
}
