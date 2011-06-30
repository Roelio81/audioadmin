#include "view_invoice.h"

using namespace View;

Invoice::Invoice(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
}

Invoice::~Invoice()
{
}

void Invoice::setName(const QString &value)
{
    m_ui.l_name->setText(value);
}

void Invoice::setStreet(const QString &value)
{
    m_ui.l_street->setText(value);
}

void Invoice::setCity(const QString &value)
{
    m_ui.l_city->setText(value);
    m_ui.l_city_2->setText(QString(value).remove(0, value.indexOf(" ") + 1) + ", ");
}

void Invoice::setTelephone(const QString &value)
{
    m_ui.l_telephone->setText(value);
}

void Invoice::setMobilePhone(const QString &value)
{
    m_ui.l_mobilePhone->setText(value);
}

void Invoice::setCustomerName(const QString &value)
{
    m_ui.l_customerName->setText(value);
}

void Invoice::setCustomerStreet(const QString &value)
{
    m_ui.l_customerStreet->setText(value);
}

void Invoice::setCustomerCity(const QString &value)
{
    m_ui.l_customerCity->setText(value);
}

void Invoice::setNumber(const QString &value)
{
    m_ui.m_invoiceNr->setText(value);
}

void Invoice::setDate(const QDate &value)
{
    m_ui.m_date->setDate(value);
}

void Invoice::setExpirationDate(const QDate &value)
{
    m_ui.m_expirationDate->setDate(value);
}

void Invoice::setReductionPercentage(double value)
{
    m_ui.m_reductionPercentage->setValue(value);
}

void Invoice::setVATPercentage(double value)
{
    m_ui.m_vatPercentage->setValue(value);
}

void Invoice::setConditions(const QString &value)
{
    m_ui.m_conditions->setText(value);
}

void Invoice::setText(const QString &value)
{
    m_ui.m_text->setPlainText(value);
}

QString Invoice::getNumber() const
{
    return m_ui.m_invoiceNr->text();
}

QDate Invoice::getDate() const
{
    return m_ui.m_date->date();
}

QDate Invoice::getExpirationDate() const
{
    return m_ui.m_expirationDate->date();
}

double Invoice::getReductionPercentage() const
{
    return m_ui.m_reductionPercentage->value();
}

double Invoice::getVATPercentage() const
{
    return m_ui.m_vatPercentage->value();
}

QString Invoice::getConditions() const
{
    return m_ui.m_conditions->text();
}

QString Invoice::getText() const
{
    return m_ui.m_text->toPlainText();
}
