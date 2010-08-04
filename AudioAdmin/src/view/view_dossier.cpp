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
    m_universum.m_klantArts->addItem("", QVariant(-1));
    m_universum.l_klantArtsStraat->setText("");
    m_universum.l_klantArtsGemeente->setText("");
    m_artsIdToStraat.clear();
    m_artsIdToGemeente.clear();
}

void Dossier::toevoegenArts(int id, const QString &naam, const QString &straat, const QString &gemeente)
{
    m_universum.m_klantArts->addItem(naam, QVariant(id));
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
    return m_universum.m_klantMutualiteit->itemData(m_universum.m_klantMutualiteit->currentIndex()).toInt();
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
    return m_universum.m_klantArts->itemData(m_universum.m_klantArts->currentIndex()).toInt();
}

QString Dossier::getRechterHoorapparaatMerk() const
{
    return m_universum.m_rechterHoorapparaatMerk->currentText();
}

QString Dossier::getRechterHoorapparaatType() const
{
    return m_universum.m_rechterHoorapparaatType->currentText();
}

QString Dossier::geRechterHoorapparaatSerienummer() const
{
    return m_universum.m_rechterHoorapparaatSerienummer->text();
}

double Dossier::getRechterHoorapparaatPrijs() const
{
    return m_universum.m_rechterHoorapparaatPrijs->text().toDouble();
}

QString Dossier::getLinkerHoorapparaatMerk() const
{
    return m_universum.m_linkerHoorapparaatMerk->currentText();
}

QString Dossier::getLinkerHoorapparaatType() const
{
    return m_universum.m_linkerHoorapparaatType->currentText();
}

QString Dossier::getLinkerHoorapparaatSerienummer() const
{
    return m_universum.m_linkerHoorapparaatSerienummer->text();
}

double Dossier::getLinkerHoorapparaatPrijs() const
{
    return m_universum.m_linkerHoorapparaatPrijs->text().toDouble();
}


QDate *Dossier::getOnderzoekDatum() const
{
    Q_ASSERT(m_universum.m_datumOnderzoek);
    Q_ASSERT(m_universum.c_datumOnderzoek);
    return (m_universum.c_datumOnderzoek->isChecked()) ? new QDate(m_universum.m_datumOnderzoek->date()) : 0;
}

QDate *Dossier::getProefDatum() const
{
    Q_ASSERT(m_universum.m_datumProef);
    Q_ASSERT(m_universum.c_datumProef);
    return (m_universum.c_datumProef->isChecked()) ? new QDate(m_universum.m_datumProef->date()) : 0;
}

QDate *Dossier::getNKORapportDatum() const
{
    Q_ASSERT(m_universum.m_datumNKO);
    Q_ASSERT(m_universum.c_datumNKO);
    return (m_universum.c_datumNKO->isChecked()) ? new QDate(m_universum.m_datumNKO->date()) : 0;
}

QDate *Dossier::getDokterAdviesDatum() const
{
    Q_ASSERT(m_universum.m_datumAdviseur);
    Q_ASSERT(m_universum.c_datumAdviseur);
    return (m_universum.c_datumAdviseur->isChecked()) ? new QDate(m_universum.m_datumAdviseur->date()) : 0;
}

QDate *Dossier::getAkkoordMutualiteitDatum() const
{
    Q_ASSERT(m_universum.m_datumMutualiteit);
    Q_ASSERT(m_universum.c_datumMutualiteit);
    return (m_universum.c_datumMutualiteit->isChecked()) ? new QDate(m_universum.m_datumMutualiteit->date()) : 0;
}

QDate *Dossier::getBetalingDatum() const
{
    Q_ASSERT(m_universum.m_datumBetaling);
    Q_ASSERT(m_universum.c_datumBetaling);
    return (m_universum.c_datumBetaling->isChecked()) ? new QDate(m_universum.m_datumBetaling->date()) : 0;
}

QDate *Dossier::getAfleveringDatum() const
{
    Q_ASSERT(m_universum.m_datumAflevering);
    Q_ASSERT(m_universum.c_datumAflevering);
    return (m_universum.c_datumAflevering->isChecked()) ? new QDate(m_universum.m_datumAflevering->date()) : 0;
}

QDate *Dossier::getWisselDatum() const
{
    Q_ASSERT(m_universum.m_datumWissel);
    Q_ASSERT(m_universum.c_datumWissel);
    return (m_universum.c_datumWissel->isChecked()) ? new QDate(m_universum.m_datumWissel->date()) : 0;
}

QDate *Dossier::getOHKDatum() const
{
    Q_ASSERT(m_universum.m_datumOHK);
    Q_ASSERT(m_universum.c_datumOHK);
    return (m_universum.c_datumOHK->isChecked()) ? new QDate(m_universum.m_datumOHK->date()) : 0;
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
    m_universum.b_meetgegevens->setEnabled(value != "");
    m_universum.b_klantBrief->setEnabled(value != "");
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
    for (int index = 0; index < m_universum.m_klantMutualiteit->count(); ++index)
    {
        int id = m_universum.m_klantMutualiteit->itemData(index).toInt();
        if (id == value)
        {
            m_universum.m_klantMutualiteit->setCurrentIndex(index);
            m_universum.b_mutualiteitBrief->setEnabled(true);
            return;
        }
    }

    m_universum.m_klantMutualiteit->setCurrentIndex(0);
    m_universum.b_mutualiteitBrief->setEnabled(false);
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
    for (int index = 0; index < m_universum.m_klantArts->count(); ++index)
    {
        int id = m_universum.m_klantArts->itemData(index).toInt();
        if (id == value)
        {
            m_universum.m_klantArts->setCurrentIndex(index);
            m_universum.b_artsBrief->setEnabled(true);
            return;
        }
    }

    m_universum.m_klantArts->setCurrentIndex(0);
    m_universum.b_artsBrief->setEnabled(false);
}

void Dossier::setRechterHoorapparaatMerk(const QString &value)
{
    QSet<QString> merken = m_universum.getMerkHoorapparaten();
    m_universum.m_rechterHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_universum.m_rechterHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_universum.m_rechterHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_universum.m_rechterHoorapparaatMerk->addItem(value);
        m_universum.m_rechterHoorapparaatMerk->setCurrentIndex(index);
    }
}

void Dossier::setRechterHoorapparaatType(const QString &value)
{
    QString merk = getRechterHoorapparaatMerk();
    QSet<QString> types = m_universum.getTypeHoorapparaten(merk);
    m_universum.m_rechterHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_universum.m_rechterHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_universum.m_rechterHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_universum.m_rechterHoorapparaatType->addItem(value);
        m_universum.m_rechterHoorapparaatType->setCurrentIndex(index);
    }
}

void Dossier::setRechterHoorapparaatSerienummer(const QString &value)
{
    m_universum.m_rechterHoorapparaatSerienummer->setText(value);
}

void Dossier::setRechterHoorapparaatPrijs(double value)
{
    m_universum.m_rechterHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void Dossier::setLinkerHoorapparaatMerk(const QString &value)
{
    QSet<QString> merken = m_universum.getMerkHoorapparaten();
    m_universum.m_linkerHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_universum.m_linkerHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_universum.m_linkerHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_universum.m_linkerHoorapparaatMerk->addItem(value);
        m_universum.m_linkerHoorapparaatMerk->setCurrentIndex(index);
    }
}

void Dossier::setLinkerHoorapparaatType(const QString &value)
{
    QString merk = getLinkerHoorapparaatMerk();
    QSet<QString> types = m_universum.getTypeHoorapparaten(merk);
    m_universum.m_linkerHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_universum.m_linkerHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_universum.m_linkerHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_universum.m_linkerHoorapparaatType->addItem(value);
        m_universum.m_linkerHoorapparaatType->setCurrentIndex(index);
    }
}

void Dossier::setLinkerHoorapparaatSerienummer(const QString &value)
{
    m_universum.m_linkerHoorapparaatSerienummer->setText(value);
}

void Dossier::setLinkerHoorapparaatPrijs(double value)
{
    m_universum.m_linkerHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void Dossier::setOnderzoekDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumOnderzoek);
    m_universum.m_datumOnderzoek->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumOnderzoek);
    m_universum.c_datumOnderzoek->setChecked(value != 0);
}

void Dossier::setProefDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumProef);
    m_universum.m_datumProef->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumProef);
    m_universum.c_datumProef->setChecked(value != 0);
}

void Dossier::setNKORapportDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumNKO);
    m_universum.m_datumNKO->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumNKO);
    m_universum.c_datumNKO->setChecked(value != 0);
}

void Dossier::setDokterAdviesDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumAdviseur);
    m_universum.m_datumAdviseur->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumAdviseur);
    m_universum.c_datumAdviseur->setChecked(value != 0);
}

void Dossier::setAkkoordMutualiteitDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumMutualiteit);
    m_universum.m_datumMutualiteit->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumMutualiteit);
    m_universum.c_datumMutualiteit->setChecked(value != 0);
}

void Dossier::setBetalingDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumBetaling);
    m_universum.m_datumBetaling->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumBetaling);
    m_universum.c_datumBetaling->setChecked(value != 0);
}

void Dossier::setAfleveringDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumAflevering);
    m_universum.m_datumAflevering->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumAflevering);
    m_universum.c_datumAflevering->setChecked(value != 0);
}

void Dossier::setWisselDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumWissel);
    m_universum.m_datumWissel->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumWissel);
    m_universum.c_datumWissel->setChecked(value != 0);
}

void Dossier::setOHKDatum(QDate *value)
{
    Q_ASSERT(m_universum.m_datumOHK);
    m_universum.m_datumOHK->setDate(value ? *value : QDate());
    Q_ASSERT(m_universum.c_datumOHK);
    m_universum.c_datumOHK->setChecked(value != 0);
}

void Dossier::toonArts(int value)
{
    int artsId = m_universum.m_klantArts->itemData(value).toInt();
    m_universum.l_klantArtsStraat->setText(m_artsIdToStraat.value(artsId, ""));
    m_universum.l_klantArtsGemeente->setText(m_artsIdToGemeente.value(artsId, ""));
    m_universum.b_artsBrief->setEnabled(value > 0);
}

void Dossier::toonBriefArts()
{
    emit briefArtsTonen();
}

void Dossier::toonBriefKlant()
{
    emit briefKlantTonen();
}

void Dossier::toonBriefMutualiteit()
{
    emit briefMutualiteitTonen();
}

void Dossier::toonFactuur()
{
    emit factuurTonen();
}

void Dossier::toonMeetgegevens()
{
    emit meetgegevensTonen();
}

void Dossier::toonMutualiteit(int value)
{
    m_universum.b_mutualiteitBrief->setEnabled(value > 0);
}

void Dossier::refreshRechterHoorapparaatLijst(int indexMerk)
{
    QString merk = m_universum.m_rechterHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universum.getTypeHoorapparaten(merk);
    m_universum.m_rechterHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_universum.m_rechterHoorapparaatType->addItem(*itType);
}

void Dossier::refreshLinkerHoorapparaatLijst(int indexMerk)
{
    QString merk = m_universum.m_linkerHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universum.getTypeHoorapparaten(merk);
    m_universum.m_linkerHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_universum.m_linkerHoorapparaatType->addItem(*itType);
}
