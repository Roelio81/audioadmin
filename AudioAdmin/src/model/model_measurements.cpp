#include "model_measurements.h"

#include <QDomElement>

using namespace Model;

Measurements::Measurements()
: m_lgDataRechts(11, -30)
, m_bgDataRechts(11, -30)
, m_uclDataRechts(11, -30)
, m_lgDataLinks(11, -30)
, m_bgDataLinks(11, -30)
, m_uclDataLinks(11, -30)
, m_roDataZonder(23, -30)
, m_loDataZonder(23, -30)
, m_roloDataZonder(23, -30)
, m_roDataMet(23, -30)
, m_loDataMet(23, -30)
, m_roloDataMet(23, -30)
, m_localisatieZonder(-10)
, m_localisatieRechts(-10)
, m_localisatieLinks(-10)
, m_localisatieBeide(-10)
{
    m_hzValuesToIndex[125] = 0;
    m_hzValuesToIndex[250] = 1;
    m_hzValuesToIndex[500] = 2;
    m_hzValuesToIndex[750] = 3;
    m_hzValuesToIndex[1000] = 4;
    m_hzValuesToIndex[1500] = 5;
    m_hzValuesToIndex[2000] = 6;
    m_hzValuesToIndex[3000] = 7;
    m_hzValuesToIndex[4000] = 8;
    m_hzValuesToIndex[6000] = 9;
    m_hzValuesToIndex[8000] = 10;
    for (int i = 0; i < 23; ++i)
        m_dbValuesToIndex[5*i] = i;
}

Measurements::~Measurements()
{
}

void Measurements::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "tonale")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                QString plaats = ee.attribute("plaats");
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "meting");
                    int db = eee.attribute("db").toInt();
                    int hz = eee.attribute("freq").toInt();
                    int index = m_hzValuesToIndex[hz];
                    if (type == "lg" && plaats == "rechts") m_lgDataRechts[index] = db;
                    else if (type == "bg" && plaats == "rechts") m_bgDataRechts[index] = db;
                    else if (type == "ucl" && plaats == "rechts") m_uclDataRechts[index] = db;
                    else if (type == "lg" && plaats == "links") m_lgDataLinks[index] = db;
                    else if (type == "bg" && plaats == "links") m_bgDataLinks[index] = db;
                    else if (type == "ucl" && plaats == "links") m_uclDataLinks[index] = db;
                }
            }
        }
        else if (element.tagName() == "vocale")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                QString plaats = ee.attribute("plaats");
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "meting");
                    int db = eee.attribute("db").toInt();
                    int percentage = eee.attribute("percentage").toInt();
                    int index = m_dbValuesToIndex[db];
                    if (type == "zonder" && plaats == "rechts") m_roDataZonder[index] = percentage;
                    else if (type == "zonder" && plaats == "links") m_loDataZonder[index] = percentage;
                    else if (type == "zonder" && plaats == "beide") m_roloDataZonder[index] = percentage;
                    else if (type == "met" && plaats == "rechts") m_roDataMet[index] = percentage;
                    else if (type == "met" && plaats == "links") m_loDataMet[index] = percentage;
                    else if (type == "met" && plaats == "beide") m_roloDataMet[index] = percentage;
                }
            }
        }
        else if (element.tagName() == "localisatie")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                int db = ee.attribute("db").toInt();
                if (type == "zonderHA")
                {
                    m_localisatieZonder = db;
                }
                else if (type == "metHA")
                {
                    QString plaats = ee.attribute("plaats");
                    if (plaats == "rechts") m_localisatieRechts = db;
                    else if (plaats == "links") m_localisatieLinks = db;
                    else if (plaats == "beide") m_localisatieBeide = db;
                }
            }
        }
    }
}

QDomElement Measurements::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("audiometrie");

    QDomElement tonale = d.createElement("tonale");
    int HzValues[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
    QString tonaleNamen[] = { "lg", "bg", "ucl", "lg", "bg", "ucl"};
    QString tonalePlaatsen[] = { "rechts", "rechts", "rechts", "links", "links", "links" };
    const QVector<int> *tonaleMetingen[] = { &m_lgDataRechts, &m_bgDataRechts, &m_uclDataRechts,
                                             &m_lgDataLinks, &m_bgDataLinks, &m_uclDataLinks };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element = d.createElement(tonaleNamen[i]);
        element.setAttribute("plaats", tonalePlaatsen[i]);
        for (int j = 0; j < 11; ++j)
        {
            QDomElement meting = d.createElement("meting");
            meting.setAttribute("freq", QString::number(HzValues[j]));
            meting.setAttribute("db", QString::number((*(tonaleMetingen[i]))[j]));
            element.appendChild(meting);
        }
        tonale.appendChild(element);
    }
    result.appendChild(tonale);

    QDomElement vocale = d.createElement("vocale");
    QString vocaleNamen[] = { "zonder", "zonder", "zonder", "met", "met", "met"};
    QString vocalePlaatsen[] = { "rechts", "links", "beide", "rechts", "links", "beide" };
    const QVector<int> *vocaleMetingen[] = { &m_roDataZonder, &m_loDataZonder, &m_roloDataZonder,
                                             &m_roDataMet, &m_loDataMet, &m_roloDataMet };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element = d.createElement(vocaleNamen[i]);
        element.setAttribute("plaats", vocalePlaatsen[i]);
        for (int j = 0; j < 22; ++j)
        {
            QDomElement meting = d.createElement("meting");
            meting.setAttribute("db", QString::number(5*j));
            meting.setAttribute("percentage", QString::number((*(vocaleMetingen[i]))[j]));
            element.appendChild(meting);
        }
        vocale.appendChild(element);
    }
    result.appendChild(vocale);

    QDomElement localisatie = d.createElement("localisatie");
    QDomElement localisatieZonder = d.createElement("zonderHA");
    localisatieZonder.setAttribute("db", QString::number(m_localisatieZonder));
    localisatie.appendChild(localisatieZonder);
    QDomElement localisatieRechts = d.createElement("metHA");
    localisatieRechts.setAttribute("db", QString::number(m_localisatieRechts));
    localisatieRechts.setAttribute("plaats", "rechts");
    localisatie.appendChild(localisatieRechts);
    QDomElement localisatieLinks = d.createElement("metHA");
    localisatieLinks.setAttribute("db", QString::number(m_localisatieLinks));
    localisatieLinks.setAttribute("plaats", "links");
    localisatie.appendChild(localisatieLinks);
    QDomElement localisatieBeide = d.createElement("metHA");
    localisatieBeide.setAttribute("db", QString::number(m_localisatieBeide));
    localisatieBeide.setAttribute("plaats", "beide");
    localisatie.appendChild(localisatieBeide);
    result.appendChild(localisatie);

    return result;
}

int Measurements::getLGRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_lgDataRechts[m_hzValuesToIndex[Hz]];
}

int Measurements::getBGRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bgDataRechts[m_hzValuesToIndex[Hz]];
}

int Measurements::getUCLRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataRechts[m_hzValuesToIndex[Hz]];
}

int Measurements::getLGLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_lgDataLinks[m_hzValuesToIndex[Hz]];
}

int Measurements::getBGLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bgDataLinks[m_hzValuesToIndex[Hz]];
}

int Measurements::getUCLLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataLinks[m_hzValuesToIndex[Hz]];
}

int Measurements::getROZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roDataZonder[m_dbValuesToIndex[dB]];
}

int Measurements::getLOZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_loDataZonder[m_dbValuesToIndex[dB]];
}

int Measurements::getROLOZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roloDataZonder[m_dbValuesToIndex[dB]];
}

int Measurements::getROMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roDataMet[m_dbValuesToIndex[dB]];
}

int Measurements::getLOMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_loDataMet[m_dbValuesToIndex[dB]];
}

int Measurements::getROLOMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roloDataMet[m_dbValuesToIndex[dB]];
}

void Measurements::setLGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_lgDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setBGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bgDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setUCLRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setLGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_lgDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setBGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bgDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setUCLLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void  Measurements::setROZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_loDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setROLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roloDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setROMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roDataMet[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_loDataMet[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setROLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roloDataMet[m_dbValuesToIndex[dB]] = percentage;
}
