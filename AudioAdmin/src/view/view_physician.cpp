#include "view_physician.h"
#include "ui_universe.h"

using namespace View;

Physician::Physician(Ui::Universe &universe)
: m_ui(universe)
{
}

Physician::~Physician()
{
}

QString Physician::getName() const
{
    return m_ui.m_physicianName->text();
}

QString Physician::getFirstName() const
{
    return m_ui.m_physicianFirstName->text();
}

QString Physician::getStreet() const
{
    return m_ui.m_physicianStreet->text();
}

int Physician::getPostalCode() const
{
    return m_ui.m_physicianPostalCode->value();
}

QString Physician::getCity() const
{
    return m_ui.m_physicianCity->text();
}

QString Physician::getTelephone() const
{
    return m_ui.m_physicianTelephone->text();
}

QString Physician::getComments() const
{
    return m_ui.m_physicianComments->toPlainText();
}

void Physician::setName(const QString &value)
{
    m_ui.m_physicianName->setText(value);
}

void Physician::setFirstName(const QString &value)
{
    m_ui.m_physicianFirstName->setText(value);
}

void Physician::setStreet(const QString &value)
{
    m_ui.m_physicianStreet->setText(value);
}

void Physician::setPostalCode(int value)
{
    m_ui.m_physicianPostalCode->setValue(value);
}

void Physician::setCity(const QString &value)
{
    m_ui.m_physicianCity->setText(value);
}

void Physician::setTelephone(const QString &value)
{
    m_ui.m_physicianTelephone->setText(value);
}

void Physician::setComments(const QString &value)
{
    m_ui.m_physicianComments->setPlainText(value);
}
