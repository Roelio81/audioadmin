#include "model_measurements.h"

#include <QDomElement>

using namespace Model;

Measurements::Measurements()
: m_acDataRight(11, -30)
, m_bcDataRight(11, -30)
, m_uclDataRight(11, -30)
, m_acDataLeft(11, -30)
, m_bcDataLeft(11, -30)
, m_uclDataLeft(11, -30)
, m_reDataWithout(23, -30)
, m_leDataWithout(23, -30)
, m_releDataWithout(23, -30)
, m_reDataWith(23, -30)
, m_leDataWith(23, -30)
, m_releDataWith(23, -30)
, m_localizationWithout(-10)
, m_localizationRight(-10)
, m_localizationLeft(-10)
, m_localizationBoth(-10)
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
        if (element.tagName() == "pureTone")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                QString plaats = ee.attribute("place");
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "measurement");
                    int db = eee.attribute("db").toInt();
                    int hz = eee.attribute("freq").toInt();
                    int index = m_hzValuesToIndex[hz];
                    if (type == "ac" && plaats == "right") m_acDataRight[index] = db;
                    else if (type == "bc" && plaats == "right") m_bcDataRight[index] = db;
                    else if (type == "ucl" && plaats == "right") m_uclDataRight[index] = db;
                    else if (type == "ac" && plaats == "left") m_acDataLeft[index] = db;
                    else if (type == "bc" && plaats == "left") m_bcDataLeft[index] = db;
                    else if (type == "ucl" && plaats == "left") m_uclDataLeft[index] = db;
                }
            }
        }
        else if (element.tagName() == "speech")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                QString place = ee.attribute("place");
                for (QDomElement eee = ee.firstChildElement(); !eee.isNull(); eee = eee.nextSiblingElement())
                {
                    Q_ASSERT(eee.nodeName() == "measurement");
                    int db = eee.attribute("db").toInt();
                    int percentage = eee.attribute("percentage").toInt();
                    int index = m_dbValuesToIndex[db];
                    if (type == "without" && place == "right") m_reDataWithout[index] = percentage;
                    else if (type == "without" && place == "left") m_leDataWithout[index] = percentage;
                    else if (type == "without" && place == "both") m_releDataWithout[index] = percentage;
                    else if (type == "with" && place == "right") m_reDataWith[index] = percentage;
                    else if (type == "with" && place == "left") m_leDataWith[index] = percentage;
                    else if (type == "with" && place == "both") m_releDataWith[index] = percentage;
                }
            }
        }
        else if (element.tagName() == "localization")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QString type = ee.nodeName();
                int db = ee.attribute("db").toInt();
                if (type == "withoutHA")
                {
                    m_localizationWithout = db;
                }
                else if (type == "withHA")
                {
                    QString plaats = ee.attribute("place");
                    if (plaats == "right") m_localizationRight = db;
                    else if (plaats == "left") m_localizationLeft = db;
                    else if (plaats == "both") m_localizationBoth = db;
                }
            }
        }
    }
}

QDomElement Measurements::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("audiometry");

    QDomElement pureTone = d.createElement("pureTone");
    int HzValues[] = {125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000};
    QString namesPureTone[] = { "ac", "bc", "ucl", "ac", "bc", "ucl"};
    QString placesPureTone[] = { "right", "right", "right", "left", "left", "left" };
    const QVector<int> *measurementsPureTone[] = { &m_acDataRight, &m_bcDataRight, &m_uclDataRight,
                                                   &m_acDataLeft, &m_bcDataLeft, &m_uclDataLeft };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element = d.createElement(namesPureTone[i]);
        element.setAttribute("place", placesPureTone[i]);
        for (int j = 0; j < 11; ++j)
        {
            QDomElement measurement = d.createElement("measurement");
            measurement.setAttribute("freq", QString::number(HzValues[j]));
            measurement.setAttribute("db", QString::number((*(measurementsPureTone[i]))[j]));
            element.appendChild(measurement);
        }
        pureTone.appendChild(element);
    }
    result.appendChild(pureTone);

    QDomElement speech = d.createElement("speech");
    QString namesSpeech[] = { "without", "without", "without", "with", "with", "with"};
    QString placesSpeech[] = { "right", "left", "both", "right", "left", "both" };
    const QVector<int> *measurementsSpeech[] = { &m_reDataWithout, &m_leDataWithout, &m_releDataWithout,
                                                 &m_reDataWith, &m_leDataWith, &m_releDataWith };
    for (int i = 0; i < 6; ++i)
    {
        QDomElement element = d.createElement(namesSpeech[i]);
        element.setAttribute("place", placesSpeech[i]);
        for (int j = 0; j < 22; ++j)
        {
            QDomElement measurment = d.createElement("measurement");
            measurment.setAttribute("db", QString::number(5*j));
            measurment.setAttribute("percentage", QString::number((*(measurementsSpeech[i]))[j]));
            element.appendChild(measurment);
        }
        speech.appendChild(element);
    }
    result.appendChild(speech);

    QDomElement localization = d.createElement("localization");
    QDomElement localizationWidthout = d.createElement("withoutHA");
    localizationWidthout.setAttribute("db", QString::number(m_localizationWithout));
    localization.appendChild(localizationWidthout);
    QDomElement localizationRight = d.createElement("withHA");
    localizationRight.setAttribute("db", QString::number(m_localizationRight));
    localizationRight.setAttribute("place", "right");
    localization.appendChild(localizationRight);
    QDomElement localizationLeft = d.createElement("withHA");
    localizationLeft.setAttribute("db", QString::number(m_localizationLeft));
    localizationLeft.setAttribute("place", "left");
    localization.appendChild(localizationLeft);
    QDomElement localizationBoth = d.createElement("withHA");
    localizationBoth.setAttribute("db", QString::number(m_localizationBoth));
    localizationBoth.setAttribute("place", "both");
    localization.appendChild(localizationBoth);
    result.appendChild(localization);

    return result;
}

int Measurements::getACRightData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_acDataRight[m_hzValuesToIndex[Hz]];
}

int Measurements::getBCRightData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bcDataRight[m_hzValuesToIndex[Hz]];
}

int Measurements::getUCLRightData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataRight[m_hzValuesToIndex[Hz]];
}

int Measurements::getACLeftData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_acDataLeft[m_hzValuesToIndex[Hz]];
}

int Measurements::getBCLeftData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_bcDataLeft[m_hzValuesToIndex[Hz]];
}

int Measurements::getUCLLeftData(int Hz)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    return m_uclDataLeft[m_hzValuesToIndex[Hz]];
}

int Measurements::getREWithoutData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_reDataWithout[m_dbValuesToIndex[dB]];
}

int Measurements::getLEWithoutData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_leDataWithout[m_dbValuesToIndex[dB]];
}

int Measurements::getRELEWithoutData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_releDataWithout[m_dbValuesToIndex[dB]];
}

int Measurements::getREWithData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_reDataWith[m_dbValuesToIndex[dB]];
}

int Measurements::getLEWithData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_leDataWith[m_dbValuesToIndex[dB]];
}

int Measurements::getRELEWithData(int dB)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    return m_releDataWith[m_dbValuesToIndex[dB]];
}

void Measurements::setACRightData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_acDataRight[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setBCRightData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bcDataRight[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setUCLRightData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataRight[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setACLeftData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_acDataLeft[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setBCLeftData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_bcDataLeft[m_hzValuesToIndex[Hz]] = dB;
}

void Measurements::setUCLLeftData(int Hz, int dB)
{
    Q_ASSERT(m_hzValuesToIndex.find(Hz) != m_hzValuesToIndex.end());
    m_uclDataLeft[m_hzValuesToIndex[Hz]] = dB;
}

void  Measurements::setREWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_reDataWithout[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setLEWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_leDataWithout[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setRELEWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_releDataWithout[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setREWithData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_reDataWith[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setLEWithData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_leDataWith[m_dbValuesToIndex[dB]] = percentage;
}

void  Measurements::setRELEWithData(int dB, int percentage)
{
    Q_ASSERT(m_dbValuesToIndex.find(dB) != m_dbValuesToIndex.end());
    m_releDataWith[m_dbValuesToIndex[dB]] = percentage;
}
