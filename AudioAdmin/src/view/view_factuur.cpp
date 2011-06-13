#include "view_factuur.h"

using namespace View;

Factuur::Factuur(QWidget *parent) 
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
    connect(b_ok, SIGNAL(clicked()), this, SLOT(okFactuur()));
    connect(b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerFactuur()));
}

Factuur::~Factuur()
{
}

void Factuur::setAudioloogNaam(const QString &value)
{
    l_audioloogNaam->setText(value);
}

void Factuur::setAudioloogStraat(const QString &value)
{
    l_audioloogStraat->setText(value);
}

void Factuur::setAudioloogGemeente(const QString &value)
{
    l_audioloogGemeente->setText(value);
    l_audioloogGemeente_2->setText(QString(value).remove(0, value.indexOf(" ") + 1) + ", ");
}

void Factuur::setAudioloogTelefoon(const QString &value)
{
    l_audioloogTelefoon->setText(value);
}

void Factuur::setAudioloogGSM(const QString &value)
{
    l_audioloogGSM->setText(value);
}

void Factuur::setKlantNaam(const QString &value)
{
    l_klantNaam->setText(value);
}

void Factuur::setKlantStraat(const QString &value)
{
    l_klantStraat->setText(value);
}

void Factuur::setKlantGemeente(const QString &value)
{
    l_klantGemeente->setText(value);
}

void Factuur::setNummer(const QString &value)
{
    m_nummer->setText(value);
}

void Factuur::setDatum(const QDate &value)
{
    m_datum->setDate(value);
}

void Factuur::setVervalDatum(const QDate &value)
{
    m_vervaldatum->setDate(value);
}

void Factuur::setKortingPercentage(double value)
{
    m_kortingPercentage->setValue(value);
}

void Factuur::setBtwPercentage(double value)
{
    m_btwPercentage->setValue(value);
}

void Factuur::setCondities(const QString &value)
{
    m_condities->setText(value);
}

void Factuur::setTekst(const QString &value)
{
    m_tekst->setPlainText(value);
}

QString Factuur::getNummer() const
{
    return m_nummer->text();
}

QDate Factuur::getDatum() const
{
    return m_datum->date();
}

QDate Factuur::getVervalDatum() const
{
    return m_vervaldatum->date();
}

double Factuur::getKortingPercentage() const
{
    return m_kortingPercentage->value();
}

double Factuur::getBtwPercentage() const
{
    return m_btwPercentage->value();
}

QString Factuur::getCondities() const
{
    return m_condities->text();
}

QString Factuur::getTekst() const
{
    return m_tekst->toPlainText();
}

void Factuur::okFactuur()
{
    emit factuurBewaren();
    emit factuurSluiten();
}

void Factuur::annuleerFactuur()
{
    emit factuurSluiten();
}
