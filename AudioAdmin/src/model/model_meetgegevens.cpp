#include "model_meetgegevens.h"

#include <QDomElement>

using namespace Model;

Meetgegevens::Meetgegevens()
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

Meetgegevens::~Meetgegevens()
{
}

void Meetgegevens::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "tonale")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                QString plaats = ee.attributeNode("plaats").value();
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "meting");
                    int db = eee.attributeNode("db").value().toInt();
                    int hz = eee.attributeNode("freq").value().toInt();
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
                QString plaats = ee.attributeNode("plaats").value();
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "meting");
                    int db = eee.attributeNode("db").value().toInt();
                    int percentage = eee.attributeNode("percentage").value().toInt();
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
                int db = ee.attributeNode("db").value().toInt();
                if (type == "zonderHA")
                {
                    m_localisatieZonder = db;
                }
                else if (type == "metHA")
                {
                    QString plaats = ee.attributeNode("plaats").value();
                    if (plaats == "rechts") m_localisatieRechts = db;
                    else if (plaats == "links") m_localisatieLinks = db;
                    else if (plaats == "beide") m_localisatieBeide = db;
                }
            }
        }
    }
}

QDomElement Meetgegevens::toDomElement() const
{
    QDomElement result;

    QDomElement tonale;
    tonale.setTagName("tonale");
    int HzValues[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
    QString tonaleNamen[] = { "lg", "bg", "ucl", "lg", "bg", "ucl"};
    QString tonalePlaatsen[] = { "rechts", "rechts", "rechts", "links", "links", "links" };
    const QVector<int> *tonaleMetingen[] = { &m_lgDataRechts, &m_bgDataRechts, &m_uclDataRechts,
                                             &m_lgDataLinks, &m_bgDataLinks, &m_uclDataLinks };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element;
        element.setTagName(tonaleNamen[i]);
        element.setAttribute("plaats", tonalePlaatsen[i]);
        for (int j = 0; j < 11; ++j)
        {
            QDomElement meting;
            meting.setTagName("meting");
            meting.setAttribute("freq", QString::number(HzValues[j]));
            meting.setAttribute("db", QString::number((*(tonaleMetingen[i]))[j]));
            element.appendChild(meting);
        }
        tonale.appendChild(element);
    }
    result.appendChild(tonale);

    QDomElement vocale;
    vocale.setTagName("vocale");
    QString vocaleNamen[] = { "zonder", "zonder", "zonder", "met", "met", "met"};
    QString vocalePlaatsen[] = { "rechts", "links", "beide", "rechts", "links", "beide" };
    const QVector<int> *vocaleMetingen[] = { &m_roDataZonder, &m_loDataZonder, &m_roloDataZonder,
                                             &m_roDataMet, &m_loDataMet, &m_roloDataMet };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element;
        element.setTagName(vocaleNamen[i]);
        element.setAttribute("plaats", vocalePlaatsen[i]);
        for (int j = 0; j < 11; ++j)
        {
            QDomElement meting;
            meting.setTagName("meting");
            meting.setAttribute("db", QString::number(5*j));
            meting.setAttribute("percentage", QString::number((*(vocaleMetingen[i]))[j]));
            element.appendChild(meting);
        }
        vocale.appendChild(element);
    }
    result.appendChild(vocale);

    QDomElement localisatie;
    localisatie.setTagName("localisatie");
    QDomElement localisatieZonder;
    localisatieZonder.setTagName("zonderHA");
    localisatieZonder.setAttribute("db", QString::number(m_localisatieZonder));
    localisatie.appendChild(localisatieZonder);
    QDomElement localisatieRechts;
    localisatieRechts.setTagName("metHA");
    localisatieRechts.setAttribute("db", QString::number(m_localisatieRechts));
    localisatieRechts.setAttribute("plaats", "rechts");
    localisatie.appendChild(localisatieRechts);
    QDomElement localisatieLinks;
    localisatieLinks.setTagName("metHA");
    localisatieLinks.setAttribute("db", QString::number(m_localisatieLinks));
    localisatieLinks.setAttribute("plaats", "links");
    localisatie.appendChild(localisatieLinks);
    QDomElement localisatieBeide;
    localisatieBeide.setTagName("metHA");
    localisatieBeide.setAttribute("db", QString::number(m_localisatieBeide));
    localisatieBeide.setAttribute("plaats", "beide");
    localisatie.appendChild(localisatieBeide);
    result.appendChild(localisatie);

    result.setTagName("audiometrie");
    return result;
}

int Meetgegevens::getLGRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_lgDataRechts[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getBGRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bgDataRechts[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getUCLRechtsData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataRechts[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getLGLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_lgDataLinks[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getBGLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bgDataLinks[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getUCLLinksData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataLinks[m_hzValuesToIndex[Hz]];
}

int Meetgegevens::getROZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roDataZonder[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getLOZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_loDataZonder[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getROLOZonderData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roloDataZonder[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getROMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roDataMet[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getLOMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_loDataMet[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getROLOMetData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_roloDataMet[m_dbValuesToIndex[dB]];
}

int Meetgegevens::getLocalisatieZonder()
{
    return m_localisatieZonder;
}

int Meetgegevens::getLocalisatieRechts()
{
    return m_localisatieRechts;
}

int Meetgegevens::getLocalisatieLinks()
{
    return m_localisatieLinks;
}

int Meetgegevens::getLocalisatieBeide()
{
    return m_localisatieBeide;
}

void Meetgegevens::setLGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_lgDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Meetgegevens::setBGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bgDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Meetgegevens::setUCLRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataRechts[m_hzValuesToIndex[Hz]] = dB;
}

void Meetgegevens::setLGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_lgDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void Meetgegevens::setBGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bgDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void Meetgegevens::setUCLLinksData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataLinks[m_hzValuesToIndex[Hz]] = dB;
}

void  Meetgegevens::setROZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Meetgegevens::setLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_loDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Meetgegevens::setROLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roloDataZonder[m_dbValuesToIndex[dB]] = percentage;
}

void  Meetgegevens::setROMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roDataMet[m_dbValuesToIndex[dB]] = percentage;
}

void  Meetgegevens::setLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_loDataMet[m_dbValuesToIndex[dB]] = percentage;
}

void  Meetgegevens::setROLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_roDataMet[m_dbValuesToIndex[dB]] = percentage;
}

void Meetgegevens::setLocalisatieZonder(int dB)
{
    m_localisatieZonder = dB;
}

void Meetgegevens::setLocalisatieRechts(int dB)
{
    m_localisatieRechts = dB;
}

void Meetgegevens::setLocalisatieLinks(int dB)
{
    m_localisatieLinks = dB;
}

void Meetgegevens::setLocalisatieBeide(int dB)
{
    m_localisatieBeide = dB;
}
