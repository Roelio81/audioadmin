#include "view_dossier.h"
#include "view_universum.h"

using namespace View;

Dossier::Dossier(Universum &universum)
: m_universum(universum)
{
}

Dossier::~Dossier()
{
}

QWidget *Dossier::getParentWindow()
{
	return &m_universum;
}

void Dossier::leegAanspreektitels()
{
	m_universum.m_aanspreektitel->clear();
}

void Dossier::toevoegenAanspreektitel(const QString &value)
{
	m_universum.m_aanspreektitel->addItem(value);
}

void Dossier::leegArtsenLijst()
{
	m_universum.m_klantArts->clear();
	m_universum.m_klantArts->addItem("");
	m_universum.l_klantArtsStraat->setText("");
	m_universum.l_klantArtsGemeente->setText("");
	m_artsIdToStraat.clear();
	m_artsIdToGemeente.clear();
}

void Dossier::toevoegenArts(int id, const QString &naam, const QString &straat, const QString &gemeente)
{
	m_universum.m_klantArts->addItem(naam);
	m_artsIdToStraat[id] = straat;
	m_artsIdToGemeente[id] = gemeente;
}

QString Dossier::getAanspreektitel() const
{
	return m_universum.m_aanspreektitel->currentText();
}

QString Dossier::getNaam() const
{
	return m_universum.m_klantNaam->text();
}

QString Dossier::getVoornaam() const
{
	return m_universum.m_klantVoornaam->text();
}

QString Dossier::getStraat() const
{
	return m_universum.m_klantStraat->text();
}

int Dossier::getPostcode() const
{
	return m_universum.m_klantPostcode->value();
}

QString Dossier::getGemeente() const
{
	return m_universum.m_klantGemeente->text();
}

QString Dossier::getTelefoon() const
{
	return m_universum.m_klantTelefoon->text();
}

QDate Dossier::getGeboorteDatum() const
{
	return m_universum.m_klantGeboorteDatum->date();
}

int Dossier::getMutualiteit() const
{
	return m_universum.mutualiteitIndexToId(m_universum.m_klantMutualiteit->currentIndex() - 1);
}

QString Dossier::getAansluitingsnummer() const
{
	return m_universum.m_aansluitingsnummer->text();
}

QString Dossier::getPlaatsAanpassing() const
{
	return m_universum.m_plaatsAanpassing->text();
}

QString Dossier::getOpmerkingen() const
{
	return m_universum.m_klantOpmerkingen->toPlainText();
}

int Dossier::getArts() const
{
	return m_universum.artsIndexToId(m_universum.m_klantArts->currentIndex() - 1);
}

void Dossier::setAanspreektitel(const QString &value)
{
	int index = m_universum.m_aanspreektitel->findText(value);
	Q_ASSERT(index >= 0);
	m_universum.m_aanspreektitel->setCurrentIndex(index);
}

void Dossier::setNaam(const QString &value)
{
	m_universum.m_klantNaam->setText(value);
}

void Dossier::setVoornaam(const QString &value)
{
	m_universum.m_klantVoornaam->setText(value);
}

void Dossier::setStraat(const QString &value)
{
	m_universum.m_klantStraat->setText(value);
}

void Dossier::setPostcode(int value)
{
	m_universum.m_klantPostcode->setValue(value);
}

void Dossier::setGemeente(const QString &value)
{
	m_universum.m_klantGemeente->setText(value);
}

void Dossier::setTelefoon(const QString &value)
{
	m_universum.m_klantTelefoon->setText(value);
}

void Dossier::setGeboorteDatum(const QDate &value)
{
	m_universum.m_klantGeboorteDatum->setDate(value);
}

void Dossier::setMutualiteit(int value)
{
	m_universum.m_klantMutualiteit->setCurrentIndex(m_universum.mutualiteitIdToIndex(value) + 1);
}

void Dossier::setAansluitingsnummer(const QString &value)
{
	m_universum.m_aansluitingsnummer->setText(value);
}

void Dossier::setPlaatsAanpassing(const QString &value)
{
	m_universum.m_plaatsAanpassing->setText(value);
}

void Dossier::setOpmerkingen(const QString &value)
{
	m_universum.m_klantOpmerkingen->setPlainText(value);
}

void Dossier::setArts(int value)
{
	m_universum.m_klantArts->setCurrentIndex(m_universum.artsIdToIndex(value) + 1);
}

void Dossier::toonArtsAdres(int value)
{
	int artsId = m_universum.artsIndexToId(value - 1);
	m_universum.l_klantArtsStraat->setText(m_artsIdToStraat.value(artsId, ""));
	m_universum.l_klantArtsGemeente->setText(m_artsIdToGemeente.value(artsId, ""));
}

void Dossier::toonBriefArts()
{
	emit briefArtsSignal();
}

void Dossier::toonBriefKlant()
{
	emit briefKlantSignal();
}

void Dossier::toonBriefMutualiteit()
{
	emit briefMutualiteitSignal();
}

void Dossier::toonFactuur()
{
	emit factuurSignal();
}
