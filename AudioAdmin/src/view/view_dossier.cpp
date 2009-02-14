#include "view_dossier.h"
#include "view_universum.h"
#include <QComboBox>

using namespace View;

Dossier::Dossier(Universum &universum)
: m_universum(universum)
{
}

Dossier::~Dossier()
{
}

void Dossier::toevoegenAanspreektitel(const QString &value)
{
	m_universum.m_aanspreektitel->addItem(value);
}

void Dossier::leegAanspreektitels()
{
	m_universum.m_aanspreektitel->clear();
}

QString Dossier::getAanspreektitel() const
{
	return m_universum.m_aanspreektitel->currentText();
}

QString Dossier::getKlantNaam() const
{
	return m_universum.m_klantNaam->text();
}

QString Dossier::getKlantVoornaam() const
{
	return m_universum.m_klantVoornaam->text();
}

QString Dossier::getKlantStraat() const
{
	return m_universum.m_klantStraat->text();
}

int Dossier::getKlantPostcode() const
{
	return m_universum.m_klantPostcode->value();
}

QString Dossier::getKlantGemeente() const
{
	return m_universum.m_klantGemeente->text();
}

QString Dossier::getKlantTelefoon() const
{
	return m_universum.m_klantTelefoon->text();
}

QDate Dossier::getKlantGeboorteDatum() const
{
	return m_universum.m_klantGeboorteDatum->date();
}

int Dossier::getKlantMutualiteit() const
{
	return m_universum.mutualiteitIndexToId(m_universum.m_klantMutualiteit->currentIndex());
}

QString Dossier::getAansluitingsnummer() const
{
	return m_universum.m_aansluitingsnummer->text();
}

QString Dossier::getPlaatsAanpassing() const
{
	return m_universum.m_plaatsAanpassing->text();
}

QString Dossier::getKlantOpmerkingen() const
{
	return m_universum.m_klantOpmerkingen->toPlainText();
}

void Dossier::setAanspreektitel(const QString &value)
{
	int index = m_universum.m_aanspreektitel->findText(value);
	Q_ASSERT(index >= 0);
	m_universum.m_aanspreektitel->setCurrentIndex(index);
}

void Dossier::setKlantNaam(const QString &value)
{
	m_universum.m_klantNaam->setText(value);
}

void Dossier::setKlantVoornaam(const QString &value)
{
	m_universum.m_klantVoornaam->setText(value);
}

void Dossier::setKlantStraat(const QString &value)
{
	m_universum.m_klantStraat->setText(value);
}

void Dossier::setKlantPostcode(int value)
{
	m_universum.m_klantPostcode->setValue(value);
}

void Dossier::setKlantGemeente(const QString &value)
{
	m_universum.m_klantGemeente->setText(value);
}

void Dossier::setKlantTelefoon(const QString &value)
{
	m_universum.m_klantTelefoon->setText(value);
}

void Dossier::setKlantGeboorteDatum(const QDate &value)
{
	m_universum.m_klantGeboorteDatum->setDate(value);
}

void Dossier::setKlantMutualiteit(int value)
{
	m_universum.m_klantMutualiteit->setCurrentIndex(m_universum.mutualiteitIdToIndex(value));
}

void Dossier::setAansluitingsnummer(const QString &value)
{
	m_universum.m_aansluitingsnummer->setText(value);
}

void Dossier::setPlaatsAanpassing(const QString &value)
{
	m_universum.m_plaatsAanpassing->setText(value);
}

void Dossier::setKlantOpmerkingen(const QString &value)
{
	m_universum.m_klantOpmerkingen->setPlainText(value);
}
