#include "model_dossier.h"

#include <QDomElement>

using namespace Model;

namespace
{
    QDate ongeldigeDatum(1900, 1, 1);
}

Dossier::Dossier(int id, double standaardBtwPercentage)
: m_id(id)
, m_klant()
, m_arts(-1)
, m_mutualiteit(-1)
, m_rechterHoorapparaatPrijs(0.0)
, m_linkerHoorapparaatPrijs(0.0)
, m_onderzoekDatum(ongeldigeDatum)
, m_proefDatum(ongeldigeDatum)
, m_nkoRapportDatum(ongeldigeDatum)
, m_dokterAdviesDatum(ongeldigeDatum)
, m_akkoordMutualiteitDatum(ongeldigeDatum)
, m_betalingDatum(ongeldigeDatum)
, m_afleveringDatum(ongeldigeDatum)
, m_wisselDatum(ongeldigeDatum)
, m_onderhoudsContractDatum(ongeldigeDatum)
, m_factuur(standaardBtwPercentage)
{
}

Dossier::~Dossier()
{
}

void Dossier::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "aanpassing")
        {
            m_plaatsAanpassing = element.text();
        }
        else if (element.tagName() == "data")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QDate date = QDate::fromString(ee.text(), "yyyy-MM-dd");
                if (ee.tagName() == "onderzoek")
                    m_onderzoekDatum = date;
                else if (ee.tagName() == "proef")
                    m_proefDatum = date;
                else if (ee.tagName() == "nkoRapport")
                    m_nkoRapportDatum = date;
                else if (ee.tagName() == "dokterAdv")
                    m_dokterAdviesDatum = date;
                else if (ee.tagName() == "akkoordMut")
                    m_akkoordMutualiteitDatum = date;
                else if (ee.tagName() == "betaling")
                    m_betalingDatum = date;
                else if (ee.tagName() == "aflevering")
                    m_afleveringDatum = date;
                else if (ee.tagName() == "wissel")
                    m_wisselDatum = date;
                else if (ee.tagName() == "onderhoudsContract")
                    m_onderhoudsContractDatum = date;
            }
        }
        else if (element.tagName() == "apparaten")
        {
            m_rechterHoorapparaatMerk = "";
            m_rechterHoorapparaatType = "";
            m_linkerHoorapparaatMerk = "";
            m_linkerHoorapparaatType = "";
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                Q_ASSERT(ee.tagName() == "apparaat");
                QString plaats = ee.attribute("plaats");
                QString merk = ee.attribute("merk");
                QString type = ee.attribute("type");
                QString serienummer = ee.firstChildElement("serienummer").text();
                double prijs = ee.firstChildElement("prijs").text().toDouble();
                if (plaats == "rechts")
                {
                    m_rechterHoorapparaatMerk = merk;
                    m_rechterHoorapparaatType = type;
                    m_rechterHoorapparaatSerienummer = serienummer;
                    m_rechterHoorapparaatPrijs = prijs;
                }
                else if (plaats == "links")
                {
                    m_linkerHoorapparaatMerk = merk;
                    m_linkerHoorapparaatType = type;
                    m_linkerHoorapparaatSerienummer = serienummer;
                    m_linkerHoorapparaatPrijs = prijs;
                }
            }
        }
        else if (element.tagName() == "brief")
        {
            m_briefKlantPostdatum = element.attribute("datum");
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "tekst")
                    m_briefKlantTekstblok = ee.text().replace("\r\n", "\n");
            }
        }
        else if (element.tagName() == "nkoArts")
        {
            m_arts = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "brief")
                {
                    m_briefArtsPostdatum = ee.attribute("datum");
                    for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                    {
                        if (eee.tagName() == "tekst")
                            m_briefArtsTekstblok = eee.text().replace("\r\n", "\n");
                        else if (eee.tagName() == "besluit")
                            m_briefArtsConclusie = eee.text().replace("\r\n", "\n");
                    }
                }
            }
        }
        else if (element.tagName() == "mutualiteit")
        {
            m_mutualiteit = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            m_aansluitingsnummer = element.attribute("aansluitingsnummer");
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "brief")
                {
                    m_briefMutualiteitPostdatum = ee.attribute("datum");
                    for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                    {
                        if (eee.tagName() == "tekst")
                            m_briefMutualiteitTekstblok = eee.text().replace("\r\n", "\n");
                        else if (eee.tagName() == "besluit")
                            m_briefMutualiteitConclusie = eee.text().replace("\r\n", "\n");
                    }
                }
            }
        }
        else if (element.tagName() == "audiometrie")
        {
            m_meetgegevens.fromDomElement(element);
        }
        else if (element.tagName() == "factuur")
        {
            m_factuur.fromDomElement(element);
        }
    }

    m_klant.fromDomElement(e);
}

QDomElement Dossier::toDomElement(QDomDocument &d) const
{
    QDomElement result = m_klant.toDomElement(d);
    QDomElement aanpassing = d.createElement("aanpassing");
    aanpassing.appendChild(d.createTextNode(m_plaatsAanpassing));
    result.appendChild(aanpassing);
    QDomElement data = d.createElement("data");
    if (m_onderzoekDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("onderzoek");
        datum.appendChild(d.createTextNode(m_onderzoekDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_proefDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("proef");
        datum.appendChild(d.createTextNode(m_proefDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_nkoRapportDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("nkoRapport");
        datum.appendChild(d.createTextNode(m_nkoRapportDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_dokterAdviesDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("dokterAdv");
        datum.appendChild(d.createTextNode(m_dokterAdviesDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_akkoordMutualiteitDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("akkoordMut");
        datum.appendChild(d.createTextNode(m_akkoordMutualiteitDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_betalingDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("betaling");
        datum.appendChild(d.createTextNode(m_betalingDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_afleveringDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("aflevering");
        datum.appendChild(d.createTextNode(m_afleveringDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_wisselDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("wissel");
        datum.appendChild(d.createTextNode(m_wisselDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_onderhoudsContractDatum != ongeldigeDatum)
    {
        QDomElement datum = d.createElement("onderhoudsContract");
        datum.appendChild(d.createTextNode(m_onderhoudsContractDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    result.appendChild(data);
    QDomElement apparaten = d.createElement("apparaten");
    if (!m_linkerHoorapparaatType.isEmpty() || !m_linkerHoorapparaatMerk.isEmpty())
    {
        QDomElement apparaat = d.createElement("apparaat");
        apparaat.setAttribute("merk", m_linkerHoorapparaatMerk);
        apparaat.setAttribute("type", m_linkerHoorapparaatType);
        apparaat.setAttribute("plaats", "links");
        if (!m_linkerHoorapparaatSerienummer.isEmpty())
        {
            QDomElement serieNummer = d.createElement("serienummer");
            serieNummer.appendChild(d.createTextNode(m_linkerHoorapparaatSerienummer));
            apparaat.appendChild(serieNummer);
        }
        if (m_linkerHoorapparaatPrijs != 0.0)
        {
            QDomElement prijs = d.createElement("prijs");
            prijs.appendChild(d.createTextNode(QString::number(m_linkerHoorapparaatPrijs, 'f', 0)));
            apparaat.appendChild(prijs);
        }
        apparaten.appendChild(apparaat);
    }
    if (!m_rechterHoorapparaatType.isEmpty() || !m_rechterHoorapparaatMerk.isEmpty())
    {
        QDomElement apparaat = d.createElement("apparaat");
        apparaat.setAttribute("merk", m_rechterHoorapparaatMerk);
        apparaat.setAttribute("type", m_rechterHoorapparaatType);
        apparaat.setAttribute("plaats", "rechts");
        if (!m_rechterHoorapparaatSerienummer.isEmpty())
        {
            QDomElement serieNummer = d.createElement("serienummer");
            serieNummer.appendChild(d.createTextNode(m_rechterHoorapparaatSerienummer));
            apparaat.appendChild(serieNummer);
        }
        if (m_rechterHoorapparaatPrijs != 0.0)
        {
            QDomElement prijs = d.createElement("prijs");
            prijs.appendChild(d.createTextNode(QString::number(m_rechterHoorapparaatPrijs, 'f', 0)));
            apparaat.appendChild(prijs);
        }
        apparaten.appendChild(apparaat);
    }
    result.appendChild(apparaten);
    if (!m_briefKlantTekstblok.isEmpty())
    {
        QDomElement brief = d.createElement("brief");
        brief.setAttribute("datum", m_briefKlantPostdatum);
        QDomElement tekst = d.createElement("tekst");
        tekst.appendChild(d.createTextNode(m_briefKlantTekstblok));
        brief.appendChild(tekst);
        result.appendChild(brief);
    }
    QDomElement nkoArts = d.createElement("nkoArts");
    nkoArts.setAttribute("id", (m_arts >= 0) ? QString::number(m_arts) : "");
    if (!m_briefArtsTekstblok.isEmpty())
    {
        QDomElement brief = d.createElement("brief");
        brief.setAttribute("datum", m_briefArtsPostdatum);
        QDomElement tekst = d.createElement("tekst");
        tekst.appendChild(d.createTextNode(m_briefArtsTekstblok));
        brief.appendChild(tekst);
        QDomElement conclusie = d.createElement("conclusie");
        conclusie.appendChild(d.createTextNode(m_briefArtsConclusie));
        brief.appendChild(conclusie);
        nkoArts.appendChild(brief);
    }
    result.appendChild(nkoArts);
    QDomElement mutualiteit = d.createElement("mutualiteit");
    mutualiteit.setAttribute("id", (m_mutualiteit >= 0) ? QString::number(m_mutualiteit) : "");
    mutualiteit.setAttribute("aansluitingsnummer", m_aansluitingsnummer);
    if (!m_briefMutualiteitTekstblok.isEmpty())
    {
        QDomElement brief = d.createElement("brief");
        brief.setAttribute("datum", m_briefMutualiteitPostdatum);
        QDomElement tekst = d.createElement("tekst");
        tekst.appendChild(d.createTextNode(m_briefMutualiteitTekstblok));
        brief.appendChild(tekst);
        QDomElement conclusie = d.createElement("conclusie");
        conclusie.appendChild(d.createTextNode(m_briefMutualiteitConclusie));
        brief.appendChild(conclusie);
        mutualiteit.appendChild(brief);
    }
    result.appendChild(mutualiteit);
    QDomElement audiometrie = m_meetgegevens.toDomElement(d);
    result.appendChild(audiometrie);
    result.setTagName("dossier");
    result.setAttribute("id", m_id);
    return result;
}

Klant &Dossier::getKlant()
{
    return m_klant;
}

Meetgegevens &Dossier::getMeetgegevens()
{
    return m_meetgegevens;
}

Factuur &Dossier::getFactuur()
{
    return m_factuur;
}

int Dossier::getId() const
{
    return m_id;
}

int Dossier::getArts() const
{
    return m_arts;
}

int Dossier::getMutualiteit() const
{
    return m_mutualiteit;
}

QString Dossier::getAansluitingsnummer() const
{
    return m_aansluitingsnummer;
}

QString Dossier::getPlaatsAanpassing() const
{
    return m_plaatsAanpassing;
}

QString Dossier::getBriefArtsPostdatum() const
{
    return m_briefArtsPostdatum;
}

QString Dossier::getBriefArtsTekstblok() const
{
    return m_briefArtsTekstblok;
}

QString Dossier::getBriefArtsConclusie() const
{
    return m_briefArtsConclusie;
}

QString Dossier::getBriefKlantPostdatum() const
{
    return m_briefKlantPostdatum;
}

QString Dossier::getBriefKlantTekstblok() const
{
    return m_briefKlantTekstblok;
}

QString Dossier::getBriefMutualiteitPostdatum() const
{
    return m_briefMutualiteitPostdatum;
}

QString Dossier::getBriefMutualiteitTekstblok() const
{
    return m_briefMutualiteitTekstblok;
}

QString Dossier::getBriefMutualiteitConclusie() const
{
    return m_briefMutualiteitConclusie;
}

QString Dossier::getRechterHoorapparaatMerk() const
{
    return m_rechterHoorapparaatMerk;
}

QString Dossier::getRechterHoorapparaatType() const
{
    return m_rechterHoorapparaatType;
}

QString Dossier::getRechterHoorapparaatSerienummer() const
{
    return m_rechterHoorapparaatSerienummer;
}

double Dossier::getRechterHoorapparaatPrijs() const
{
    return m_rechterHoorapparaatPrijs;
}

QString Dossier::getLinkerHoorapparaatMerk() const
{
    return m_linkerHoorapparaatMerk;
}

QString Dossier::getLinkerHoorapparaatType() const
{
    return m_linkerHoorapparaatType;
}

QString Dossier::getLinkerHoorapparaatSerienummer() const
{
    return m_linkerHoorapparaatSerienummer;
}

double Dossier::getLinkerHoorapparaatPrijs() const
{
    return m_linkerHoorapparaatPrijs;
}

int Dossier::getAantalHoorapparaten() const
{
    int aantal = 0;
    if (!m_rechterHoorapparaatMerk.isEmpty() || !m_rechterHoorapparaatType.isEmpty()) aantal++;
    if (!m_linkerHoorapparaatMerk.isEmpty() || !m_linkerHoorapparaatType.isEmpty()) aantal++;
    return aantal;
}

QDate Dossier::getOnderzoekDatum() const
{
    return m_onderzoekDatum;
}

QDate Dossier::getProefDatum() const
{
    return m_proefDatum;
}

QDate Dossier::getNKORapportDatum() const
{
    return m_nkoRapportDatum;
}

QDate Dossier::getDokterAdviesDatum() const
{
    return m_dokterAdviesDatum;
}

QDate Dossier::getAkkoordMutualiteitDatum() const
{
    return m_akkoordMutualiteitDatum;
}

QDate Dossier::getBetalingDatum() const
{
    return m_betalingDatum;
}

QDate Dossier::getAfleveringDatum() const
{
    return m_afleveringDatum;
}

QDate Dossier::getWisselDatum() const
{
    return m_wisselDatum;
}

QDate Dossier::getOnderhoudsContractDatum() const
{
    return m_onderhoudsContractDatum;
}

void Dossier::setArts(int value)
{
    m_arts = value;
}

void Dossier::setMutualiteit(int value)
{
    m_mutualiteit = value;
}

void Dossier::setAansluitingsnummer(const QString &value)
{
    m_aansluitingsnummer = value;
}

void Dossier::setPlaatsAanpassing(const QString &value)
{
    m_plaatsAanpassing = value;
}

void Dossier::setBriefArtsPostdatum(const QString &value)
{
    m_briefArtsPostdatum = value;
}

void Dossier::setBriefArtsTekstblok(const QString &value)
{
    m_briefArtsTekstblok = value;
}

void Dossier::setBriefArtsConclusie(const QString &value)
{
    m_briefArtsConclusie = value;
}

void Dossier::setBriefKlantPostdatum(const QString &value)
{
    m_briefKlantPostdatum = value;
}

void Dossier::setBriefKlantTekstblok(const QString &value)
{
    m_briefKlantTekstblok = value;
}

void Dossier::setBriefMutualiteitPostdatum(const QString &value)
{
    m_briefMutualiteitPostdatum = value;
}

void Dossier::setBriefMutualiteitTekstblok(const QString &value)
{
    m_briefMutualiteitTekstblok = value;
}

void Dossier::setBriefMutualiteitConclusie(const QString &value)
{
    m_briefMutualiteitConclusie = value;
}

void Dossier::setRechterHoorapparaatMerk(const QString &value)
{
    m_rechterHoorapparaatMerk = value;
}

void Dossier::setRechterHoorapparaatType(const QString &value)
{
    m_rechterHoorapparaatType = value;
}

void Dossier::setRechterHoorapparaatSerienummer(const QString &value)
{
    m_rechterHoorapparaatSerienummer = value;
}

void Dossier::setRechterHoorapparaatPrijs(double value)
{
    m_rechterHoorapparaatPrijs = value;
}

void Dossier::setLinkerHoorapparaatMerk(const QString &value)
{
    m_linkerHoorapparaatMerk = value;
}

void Dossier::setLinkerHoorapparaatType(const QString &value)
{
    m_linkerHoorapparaatType = value;
}

void Dossier::setLinkerHoorapparaatSerienummer(const QString &value)
{
    m_linkerHoorapparaatSerienummer = value;
}

void Dossier::setLinkerHoorapparaatPrijs(double value)
{
    m_linkerHoorapparaatPrijs = value;
}

void Dossier::setOnderzoekDatum(const QDate &value)
{
    m_onderzoekDatum = value;
}

void Dossier::setProefDatum(const QDate &value)
{
    m_proefDatum = value;
}

void Dossier::setNKORapportDatum(const QDate &value)
{
    m_nkoRapportDatum = value;
}

void Dossier::setDokterAdviesDatum(const QDate &value)
{
    m_dokterAdviesDatum = value;
}

void Dossier::setAkkoordMutualiteitDatum(const QDate &value)
{
    m_akkoordMutualiteitDatum = value;
}

void Dossier::setBetalingDatum(const QDate &value)
{
    m_betalingDatum = value;
}

void Dossier::setAfleveringDatum(const QDate &value)
{
    m_afleveringDatum = value;
}

void Dossier::setWisselDatum(const QDate &value)
{
    m_wisselDatum = value;
}

void Dossier::setOnderhoudsContractDatum(const QDate &value)
{
    m_onderhoudsContractDatum = value;
}
