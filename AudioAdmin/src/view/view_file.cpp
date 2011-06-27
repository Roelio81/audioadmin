#include "view_file.h"
#include "view_universe.h"

using namespace View;

File::File(Universe &universe)
: m_universe(universe)
, m_ui(universe.getUi())
{
}

File::~File()
{
}

QWidget *File::getParentWindow()
{
    return &m_universe;
}

void File::leegAanspreektitels()
{
    m_ui.m_aanspreektitel->clear();
}

void File::toevoegenAanspreektitel(const QString &value)
{
    m_ui.m_aanspreektitel->addItem(value);
}

void File::leegArtsenLijst()
{
    m_ui.m_klantArts->clear();
    m_ui.m_klantArts->addItem("", QVariant(-1));
    m_ui.l_klantArtsStraat->setText("");
    m_ui.l_klantArtsGemeente->setText("");
    m_artsIdToStraat.clear();
    m_artsIdToGemeente.clear();
}

void File::toevoegenArts(int id, const QString &naam, const QString &straat, const QString &gemeente)
{
    m_ui.m_klantArts->addItem(naam, QVariant(id));
    m_artsIdToStraat[id] = straat;
    m_artsIdToGemeente[id] = gemeente;
}

void File::wijzigenArts(int id, const QString &naam, const QString &straat, const QString &gemeente)
{
    int nofArtsen = m_ui.m_klantArts->count();
    for (int index = 0; index < nofArtsen; ++index)
    {
        if (m_ui.m_klantArts->itemData(index).toInt() == id)
        {
            m_ui.m_klantArts->setItemText(index, naam);
            m_artsIdToStraat[id] = straat;
            m_artsIdToGemeente[id] = gemeente;
            return;
        }
    }

    Q_ASSERT(false);
}

void File::toevoegenMutualiteit(int id, const QString &naam)
{
    m_ui.m_klantMutualiteit->addItem(naam, QVariant(id));
}

void File::wijzigenMutualiteit(int id, const QString &naam)
{
    int nofMutualiteiten = m_ui.m_klantMutualiteit->count();
    for (int index = 0; index < nofMutualiteiten; ++index)
    {
        if (m_ui.m_klantMutualiteit->itemData(index).toInt() == id)
        {
            m_ui.m_klantMutualiteit->setItemText(index, naam);
            return;
        }
    }

    Q_ASSERT(false);
}

QString File::getAanspreektitel() const
{
    return m_ui.m_aanspreektitel->currentText();
}

QString File::getNaam() const
{
    return m_ui.m_klantNaam->text();
}

QString File::getVoornaam() const
{
    return m_ui.m_klantVoornaam->text();
}

QString File::getStraat() const
{
    return m_ui.m_klantStraat->text();
}

int File::getPostcode() const
{
    return m_ui.m_klantPostcode->value();
}

QString File::getGemeente() const
{
    return m_ui.m_klantGemeente->text();
}

QString File::getTelefoon() const
{
    return m_ui.m_klantTelefoon->text();
}

QDate File::getGeboorteDatum() const
{
    return m_ui.m_klantGeboorteDatum->date();
}

int File::getMutualiteit() const
{
    int index = m_ui.m_klantMutualiteit->currentIndex();
    int id = m_ui.m_klantMutualiteit->itemData(index).toInt();
    return id;
}

QString File::getAansluitingsnummer() const
{
    return m_ui.m_aansluitingsnummer->text();
}

QString File::getPlaatsAanpassing() const
{
    return m_ui.m_plaatsAanpassing->text();
}

QString File::getOpmerkingen() const
{
    return m_ui.m_klantOpmerkingen->toPlainText();
}

int File::getArts() const
{
    int index = m_ui.m_klantArts->currentIndex();
    return m_ui.m_klantArts->itemData(index).toInt();
}

QString File::getRechterHoorapparaatMerk() const
{
    return m_ui.m_rechterHoorapparaatMerk->currentText();
}

QString File::getRechterHoorapparaatType() const
{
    return m_ui.m_rechterHoorapparaatType->currentText();
}

QString File::getRechterHoorapparaatSerienummer() const
{
    return m_ui.m_rechterHoorapparaatSerienummer->text();
}

double File::getRechterHoorapparaatPrijs() const
{
    return m_ui.m_rechterHoorapparaatPrijs->text().toDouble();
}

QString File::getLinkerHoorapparaatMerk() const
{
    return m_ui.m_linkerHoorapparaatMerk->currentText();
}

QString File::getLinkerHoorapparaatType() const
{
    return m_ui.m_linkerHoorapparaatType->currentText();
}

QString File::getLinkerHoorapparaatSerienummer() const
{
    return m_ui.m_linkerHoorapparaatSerienummer->text();
}

double File::getLinkerHoorapparaatPrijs() const
{
    return m_ui.m_linkerHoorapparaatPrijs->text().toDouble();
}


QDate File::getOnderzoekDatum() const
{
    return m_ui.m_datumOnderzoek->date();
}

QDate File::getProefDatum() const
{
    return m_ui.m_datumProef->date();
}

QDate File::getNKORapportDatum() const
{
    return m_ui.m_datumNKO->date();
}

QDate File::getDokterAdviesDatum() const
{
    return m_ui.m_datumAdviseur->date();
}

QDate File::getAkkoordMutualiteitDatum() const
{
    return m_ui.m_datumMutualiteit->date();
}

QDate File::getBetalingDatum() const
{
    return m_ui.m_datumBetaling->date();
}

QDate File::getAfleveringDatum() const
{
    return m_ui.m_datumAflevering->date();
}

QDate File::getWisselDatum() const
{
    return m_ui.m_datumWissel->date();
}

QDate File::getOnderhoudsContractDatum() const
{
    return m_ui.m_datumOnderhoudsContract->date();
}

void File::setAanspreektitel(const QString &value)
{
    int index = value.isEmpty() ? 0 : m_ui.m_aanspreektitel->findText(value);
    Q_ASSERT(index >= 0);
    m_ui.m_aanspreektitel->setCurrentIndex(index);
}

void File::setNaam(const QString &value)
{
    m_ui.m_klantNaam->setText(value);
    m_ui.b_meetgegevens->setEnabled(value != "");
    m_ui.b_klantBrief->setEnabled(value != "");
}

void File::setVoornaam(const QString &value)
{
    m_ui.m_klantVoornaam->setText(value);
}

void File::setStraat(const QString &value)
{
    m_ui.m_klantStraat->setText(value);
}

void File::setPostcode(int value)
{
    m_ui.m_klantPostcode->setValue(value);
}

void File::setGemeente(const QString &value)
{
    m_ui.m_klantGemeente->setText(value);
}

void File::setTelefoon(const QString &value)
{
    m_ui.m_klantTelefoon->setText(value);
}

void File::setGeboorteDatum(const QDate &value)
{
    m_ui.m_klantGeboorteDatum->setDate(value);
}

void File::setMutualiteit(int value)
{
    for (int index = 1; index < m_ui.m_klantMutualiteit->count(); ++index)
    {
        int id = m_ui.m_klantMutualiteit->itemData(index).toInt();
        if (id == value)
        {
            m_ui.m_klantMutualiteit->setCurrentIndex(index);
            m_ui.b_mutualiteitBrief->setEnabled(true);
            return;
        }
    }

    m_ui.m_klantMutualiteit->setCurrentIndex(0);
    m_ui.b_mutualiteitBrief->setEnabled(false);
}

void File::setAansluitingsnummer(const QString &value)
{
    m_ui.m_aansluitingsnummer->setText(value);
}

void File::setPlaatsAanpassing(const QString &value)
{
    m_ui.m_plaatsAanpassing->setText(value);
}

void File::setOpmerkingen(const QString &value)
{
    m_ui.m_klantOpmerkingen->setPlainText(value);
}

void File::setArts(int value)
{
    for (int index = 1; index < m_ui.m_klantArts->count(); ++index)
    {
        int id = m_ui.m_klantArts->itemData(index).toInt();
        if (id == value)
        {
            m_ui.m_klantArts->setCurrentIndex(index);
            m_ui.b_artsBrief->setEnabled(true);
            return;
        }
    }

    m_ui.m_klantArts->setCurrentIndex(0);
    m_ui.b_artsBrief->setEnabled(false);
}

void File::setRechterHoorapparaatMerk(const QString &value)
{
    QSet<QString> merken = m_universe.getMerkHoorapparaten();
    m_ui.m_rechterHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_ui.m_rechterHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_ui.m_rechterHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_rechterHoorapparaatMerk->addItem(value);
        m_ui.m_rechterHoorapparaatMerk->setCurrentIndex(index);
    }
}

void File::setRechterHoorapparaatType(const QString &value)
{
    QString merk = getRechterHoorapparaatMerk();
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_rechterHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_ui.m_rechterHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_ui.m_rechterHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_rechterHoorapparaatType->addItem(value);
        m_ui.m_rechterHoorapparaatType->setCurrentIndex(index);
    }
}

void File::setRechterHoorapparaatSerienummer(const QString &value)
{
    m_ui.m_rechterHoorapparaatSerienummer->setText(value);
}

void File::setRechterHoorapparaatPrijs(double value)
{
    m_ui.m_rechterHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setLinkerHoorapparaatMerk(const QString &value)
{
    QSet<QString> merken = m_universe.getMerkHoorapparaten();
    m_ui.m_linkerHoorapparaatMerk->clear();
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itMerk = merken.begin(); itMerk != merken.end(); ++itMerk, ++index)
    {
        m_ui.m_linkerHoorapparaatMerk->addItem(*itMerk);
        if (*itMerk == value)
        {
            m_ui.m_linkerHoorapparaatMerk->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_linkerHoorapparaatMerk->addItem(value);
        m_ui.m_linkerHoorapparaatMerk->setCurrentIndex(index);
    }
}

void File::setLinkerHoorapparaatType(const QString &value)
{
    QString merk = getLinkerHoorapparaatMerk();
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_linkerHoorapparaatType->setEditText(value);
    int index = 0;
    bool itemGevonden = false;
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType, ++index)
    {
        m_ui.m_linkerHoorapparaatType->addItem(*itType);
        if (*itType == value)
        {
            m_ui.m_linkerHoorapparaatType->setCurrentIndex(index);
            itemGevonden = true;
        }
    }
    if (! itemGevonden)
    {
        m_ui.m_linkerHoorapparaatType->addItem(value);
        m_ui.m_linkerHoorapparaatType->setCurrentIndex(index);
    }
}

void File::setLinkerHoorapparaatSerienummer(const QString &value)
{
    m_ui.m_linkerHoorapparaatSerienummer->setText(value);
}

void File::setLinkerHoorapparaatPrijs(double value)
{
    m_ui.m_linkerHoorapparaatPrijs->setText(value > 0.0 ? QString::number(value) : "");
}

void File::setOnderzoekDatum(const QDate &value)
{
    m_ui.m_datumOnderzoek->setDate(value);
}

void File::setProefDatum(const QDate &value)
{
    m_ui.m_datumProef->setDate(value);
}

void File::setNKORapportDatum(const QDate &value)
{
    m_ui.m_datumNKO->setDate(value);
}

void File::setDokterAdviesDatum(const QDate &value)
{
    m_ui.m_datumAdviseur->setDate(value);
}

void File::setAkkoordMutualiteitDatum(const QDate &value)
{
    m_ui.m_datumMutualiteit->setDate(value);
}

void File::setBetalingDatum(const QDate &value)
{
    m_ui.m_datumBetaling->setDate(value);
}

void File::setAfleveringDatum(const QDate &value)
{
    m_ui.m_datumAflevering->setDate(value);
}

void File::setWisselDatum(const QDate &value)
{
    m_ui.m_datumWissel->setDate(value);
}

void File::setOnderhoudsContractDatum(const QDate &value)
{
    m_ui.m_datumOnderhoudsContract->setDate(value);
}

void File::toonArts(int value)
{
    int artsId = m_ui.m_klantArts->itemData(value).toInt();
    m_ui.l_klantArtsStraat->setText(m_artsIdToStraat.value(artsId, ""));
    m_ui.l_klantArtsGemeente->setText(m_artsIdToGemeente.value(artsId, ""));
    m_ui.b_artsBrief->setEnabled(value > 0);
}

void File::toonBriefArts()
{
    emit briefArtsTonen();
}

void File::toonBriefKlant()
{
    emit briefKlantTonen();
}

void File::toonBriefMutualiteit()
{
    emit briefMutualiteitTonen();
}

void File::toonFactuur()
{
    emit showInvoice();
}

void File::toonMeetgegevens()
{
    emit showMeasurements();
}

void File::toonMutualiteit(int value)
{
    m_ui.b_mutualiteitBrief->setEnabled(value > 0);
}

void File::refreshRechterHoorapparaatLijst(int indexMerk)
{
    QString merk = m_ui.m_rechterHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_rechterHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_ui.m_rechterHoorapparaatType->addItem(*itType);
}

void File::refreshLinkerHoorapparaatLijst(int indexMerk)
{
    QString merk = m_ui.m_linkerHoorapparaatMerk->itemText(indexMerk);
    QSet<QString> types = m_universe.getTypeHoorapparaten(merk);
    m_ui.m_linkerHoorapparaatType->clear();
    for (QSet<QString>::iterator itType = types.begin(); itType != types.end(); ++itType)
        m_ui.m_linkerHoorapparaatType->addItem(*itType);
}
