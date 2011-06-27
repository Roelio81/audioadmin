#include "view_physician.h"
#include "ui_universe.h"

using namespace View;

Physician::Physician(Ui::Universe &universe)
: m_universe(universe)
{
}

Physician::~Physician()
{
}

QString Physician::getName() const
{
    return m_universe.m_artsNaam->text();
}

QString Physician::getFirstName() const
{
    return m_universe.m_artsVoornaam->text();
}

QString Physician::getStreet() const
{
    return m_universe.m_artsStraat->text();
}

int Physician::getPostalCode() const
{
    return m_universe.m_artsPostcode->value();
}

QString Physician::getCity() const
{
    return m_universe.m_artsGemeente->text();
}

QString Physician::getTelephone() const
{
    return m_universe.m_artsTelefoon->text();
}

QString Physician::getComments() const
{
    return m_universe.m_artsOpmerkingen->toPlainText();
}

void Physician::setName(const QString &value)
{
    m_universe.m_artsNaam->setText(value);
}

void Physician::setFirstName(const QString &value)
{
    m_universe.m_artsVoornaam->setText(value);
}

void Physician::setStreet(const QString &value)
{
    m_universe.m_artsStraat->setText(value);
}

void Physician::setPostalCode(int value)
{
    m_universe.m_artsPostcode->setValue(value);
}

void Physician::setCity(const QString &value)
{
    m_universe.m_artsGemeente->setText(value);
}

void Physician::setTelephone(const QString &value)
{
    m_universe.m_artsTelefoon->setText(value);
}

void Physician::setComments(const QString &value)
{
    m_universe.m_artsOpmerkingen->setPlainText(value);
}
