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
					int index = db/5;
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
		}
	}
}

QDomElement Meetgegevens::toDomElement() const
{
	return QDomElement();
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
