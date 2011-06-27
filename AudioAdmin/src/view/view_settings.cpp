#include "view_settings.h"

#include <QLineEdit>

using namespace View;

Instellingen::Instellingen(::QWidget *parent) 
: ::QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
}

Instellingen::~Instellingen()
{
}

QString Instellingen::getNaam() const
{
    return m_naam->text();
}

QString Instellingen::getStraat() const
{
    return m_straat->text();
}

int Instellingen::getPostcode() const
{
    return m_postcode->value();
}

QString Instellingen::getGemeente() const
{
    return m_gemeente->text();
}

QString Instellingen::getTelefoon() const
{
    return m_telefoon->text();
}

QString Instellingen::getGsm() const
{
    return m_gsm->text();
}

QString Instellingen::getEmail() const
{
    return m_email->text();
}

QString Instellingen::getOnderschrift() const
{
    return m_onderschrift->text();
}

QString Instellingen::getRiziv() const
{
    return m_riziv->text();
}

int Instellingen::getBtwPercentage() const
{
    return m_btwpercentage->value();
}

QString Instellingen::getBtwNummer() const
{
    return m_btwnummer->text();
}

QString Instellingen::getRekeningNummer() const
{
    return m_rekeningnummer->text();
}

void Instellingen::setNaam(const QString &value)
{
    m_naam->setText(value);
}

void Instellingen::setStraat(const QString &value)
{
    m_straat->setText(value);
}

void Instellingen::setPostcode(const int &value)
{
    m_postcode->setValue(value);
}

void Instellingen::setGemeente(const QString &value)
{
    m_gemeente->setText(value);
}

void Instellingen::setTelefoon(const QString &value)
{
    m_telefoon->setText(value);
}

void Instellingen::setGsm(const QString &value)
{
    m_gsm->setText(value);
}

void Instellingen::setEmail(const QString &value)
{
    m_email->setText(value);
}

void Instellingen::setOnderschrift(const QString &value)
{
    m_onderschrift->setText(value);
}

void Instellingen::setRiziv(const QString &value)
{
    m_riziv->setText(value);
}

void Instellingen::setBtwPercentage(const int &value)
{
    m_btwpercentage->setValue(value);
}

void Instellingen::setBtwNummer(const QString &value)
{
    m_btwnummer->setText(value);
}

void Instellingen::setRekeningNummer(const QString &value)
{
    m_rekeningnummer->setText(value);
}
