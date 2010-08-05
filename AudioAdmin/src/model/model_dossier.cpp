#include "model_dossier.h"

#include <QDomElement>

using namespace Model;

Dossier::Dossier(int id)
: m_id(id)
, m_klant()
, m_arts(-1)
, m_mutualiteit(-1)
, m_onderzoekDatum(0)
, m_proefDatum(0)
, m_nkoRapportDatum(0)
, m_dokterAdviesDatum(0)
, m_akkoordMutualiteitDatum(0)
, m_betalingDatum(0)
, m_afleveringDatum(0)
, m_wisselDatum(0)
, m_ohkDatum(0)
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
        else if (element.tagName() == "brief")
        {
            m_briefKlantPostdatum = element.attribute("datum");
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "tekst") m_briefKlantTekstblok = ee.text();
            }
        }
        else if (element.tagName() == "nkoArts")
        {
            m_arts = element.attribute("id").toInt();
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "brief")
                {
                    m_briefArtsPostdatum = ee.attribute("datum");
                    for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                    {
                        if (eee.tagName() == "tekst") m_briefArtsTekstblok = eee.text();
                        else if (eee.tagName() == "besluit") m_briefArtsConclusie = eee.text();
                    }
                }
            }
        }
        else if (element.tagName() == "mutualiteit")
        {
            m_mutualiteit = element.attribute("id").toInt();
            m_aansluitingsnummer = element.attribute("aansluitingsnummer");
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                if (ee.tagName() == "brief")
                {
                    m_briefMutualiteitPostdatum = ee.attribute("datum");
                    for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                    {
                        if (eee.tagName() == "tekst") m_briefMutualiteitTekstblok = eee.text();
                        else if (eee.tagName() == "besluit") m_briefMutualiteitConclusie = eee.text();
                    }
                }
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
                QString serienummer = ee.attribute("serienummer");
                double prijs = ee.attribute("prijs").toDouble();
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
        else if (element.tagName() == "audiometrie")
        {
            m_meetgegevens.fromDomElement(element);
        }
    }

    m_klant.fromDomElement(e);
}

QDomElement Dossier::toDomElement() const
{
    QDomElement result = m_klant.toDomElement();
    QDomElement aanpassing;
    aanpassing.setTagName("aanpassing");
    aanpassing.setNodeValue(m_plaatsAanpassing);
    result.appendChild(aanpassing);
    QDomElement nkoArts;
    nkoArts.setTagName("nkoArts");
    nkoArts.setAttribute("id", QString::number(m_arts));
    result.appendChild(nkoArts);
    QDomElement mutualiteit;
    mutualiteit.setTagName("mutualiteit");
    mutualiteit.setAttribute("id", QString::number(m_mutualiteit));
    mutualiteit.setAttribute("aansluitingsnummer", m_aansluitingsnummer);
    result.appendChild(mutualiteit);
    QDomElement audiometrie = m_meetgegevens.toDomElement();
    audiometrie.appendChild(audiometrie);
    result.setTagName("dossier");
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

QDate *Dossier::getOnderzoekDatum() const
{
    return m_onderzoekDatum;
}

QDate *Dossier::getProefDatum() const
{
    return m_proefDatum;
}

QDate *Dossier::getNKORapportDatum() const
{
    return m_nkoRapportDatum;
}

QDate *Dossier::getDokterAdviesDatum() const
{
    return m_dokterAdviesDatum;
}

QDate *Dossier::getAkkoordMutualiteitDatum() const
{
    return m_akkoordMutualiteitDatum;
}

QDate *Dossier::getBetalingDatum() const
{
    return m_betalingDatum;
}

QDate *Dossier::getAfleveringDatum() const
{
    return m_afleveringDatum;
}

QDate *Dossier::getWisselDatum() const
{
    return m_wisselDatum;
}

QDate *Dossier::getOHKDatum() const
{
    return m_ohkDatum;
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

void Dossier::setOnderzoekDatum(QDate *value)
{
    m_onderzoekDatum = value;
}

void Dossier::setProefDatum(QDate *value)
{
    m_proefDatum = value;
}

void Dossier::setNKORapportDatum(QDate *value)
{
    m_nkoRapportDatum = value;
}

void Dossier::setDokterAdviesDatum(QDate *value)
{
    m_dokterAdviesDatum = value;
}

void Dossier::setAkkoordMutualiteitDatum(QDate *value)
{
    m_akkoordMutualiteitDatum = value;
}

void Dossier::setBetalingDatum(QDate *value)
{
    m_betalingDatum = value;
}

void Dossier::setAfleveringDatum(QDate *value)
{
    m_afleveringDatum = value;
}

void Dossier::setWisselDatum(QDate *value)
{
    m_wisselDatum = value;
}

void Dossier::setOHKDatum(QDate *value)
{
    m_ohkDatum = value;
}
