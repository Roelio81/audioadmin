#include "model_file.h"
#include "model_universe.h"

#include <QDomElement>

using namespace Model;

File::File(int id, const Universe &universe)
: m_id(id)
, m_universum(universe)
, m_arts(-1)
, m_mutualiteit(-1)
, m_rechterHoorapparaatPrijs(0.0)
, m_linkerHoorapparaatPrijs(0.0)
, m_onderzoekDatum(universe.getInvalidDate())
, m_proefDatum(universe.getInvalidDate())
, m_nkoRapportDatum(universe.getInvalidDate())
, m_dokterAdviesDatum(universe.getInvalidDate())
, m_akkoordMutualiteitDatum(universe.getInvalidDate())
, m_betalingDatum(universe.getInvalidDate())
, m_afleveringDatum(universe.getInvalidDate())
, m_wisselDatum(universe.getInvalidDate())
, m_onderhoudsContractDatum(universe.getInvalidDate())
, m_letterPhysician(*this, true)
, m_letterCustomer(*this, false)
, m_briefMutualiteit(*this, true)
, m_invoice(universe)
, m_customer(universe)
{
}

File::~File()
{
}

void File::fromDomElement(const QDomElement &e)
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
            m_letterCustomer.fromDomElement(element);
        }
        else if (element.tagName() == "nkoArts")
        {
            m_arts = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            QDomElement brief = element.firstChildElement("brief");
            if (!brief.isNull())
                m_letterPhysician.fromDomElement(brief);
        }
        else if (element.tagName() == "mutualiteit")
        {
            m_mutualiteit = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            m_aansluitingsnummer = element.attribute("aansluitingsnummer");
            QDomElement brief = element.firstChildElement("brief");
            if (!brief.isNull())
                m_briefMutualiteit.fromDomElement(brief);
        }
        else if (element.tagName() == "audiometrie")
        {
            m_meetgegevens.fromDomElement(element);
        }
        else if (element.tagName() == "factuur")
        {
            m_invoice.fromDomElement(element);
        }
    }

    m_customer.fromDomElement(e);
}

QDomElement File::toDomElement(QDomDocument &d) const
{
    QDomElement result = m_customer.toDomElement(d);
    QDomElement aanpassing = d.createElement("aanpassing");
    aanpassing.appendChild(d.createTextNode(m_plaatsAanpassing));
    result.appendChild(aanpassing);
    QDomElement data = d.createElement("data");
    if (m_onderzoekDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("onderzoek");
        datum.appendChild(d.createTextNode(m_onderzoekDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_proefDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("proef");
        datum.appendChild(d.createTextNode(m_proefDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_nkoRapportDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("nkoRapport");
        datum.appendChild(d.createTextNode(m_nkoRapportDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_dokterAdviesDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("dokterAdv");
        datum.appendChild(d.createTextNode(m_dokterAdviesDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_akkoordMutualiteitDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("akkoordMut");
        datum.appendChild(d.createTextNode(m_akkoordMutualiteitDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_betalingDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("betaling");
        datum.appendChild(d.createTextNode(m_betalingDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_afleveringDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("aflevering");
        datum.appendChild(d.createTextNode(m_afleveringDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_wisselDatum != m_universum.getInvalidDate())
    {
        QDomElement datum = d.createElement("wissel");
        datum.appendChild(d.createTextNode(m_wisselDatum.toString("yyyy-MM-dd")));
        data.appendChild(datum);
    }
    if (m_onderhoudsContractDatum != m_universum.getInvalidDate())
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
    if (!m_letterCustomer.getText().isEmpty())
    {
        QDomElement brief = m_letterCustomer.toDomElement(d);
        result.appendChild(brief);
    }
    QDomElement nkoArts = d.createElement("nkoArts");
    nkoArts.setAttribute("id", (m_arts >= 0) ? QString::number(m_arts) : "");
    if (!m_letterPhysician.getText().isEmpty())
    {
        QDomElement brief = m_letterPhysician.toDomElement(d);
        nkoArts.appendChild(brief);
    }
    result.appendChild(nkoArts);
    QDomElement mutualiteit = d.createElement("mutualiteit");
    mutualiteit.setAttribute("id", (m_mutualiteit >= 0) ? QString::number(m_mutualiteit) : "");
    mutualiteit.setAttribute("aansluitingsnummer", m_aansluitingsnummer);
    if (!m_briefMutualiteit.getText().isEmpty())
    {
        QDomElement brief = m_briefMutualiteit.toDomElement(d);
        mutualiteit.appendChild(brief);
    }
    result.appendChild(mutualiteit);
    QDomElement audiometrie = m_meetgegevens.toDomElement(d);
    result.appendChild(audiometrie);
    result.setTagName("dossier");
    result.setAttribute("id", m_id);
    return result;
}

int File::getAantalHoorapparaten() const
{
    int aantal = 0;
    if (!m_rechterHoorapparaatMerk.isEmpty() || !m_rechterHoorapparaatType.isEmpty())
        ++aantal;
    if (!m_linkerHoorapparaatMerk.isEmpty() || !m_linkerHoorapparaatType.isEmpty())
        ++aantal;
    return aantal;
}
