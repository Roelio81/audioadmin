#include "view_meetgegevens.h"

using namespace View;

Meetgegevens::Meetgegevens(::QWidget *parent) 
: ::QDialog(parent)
{
	setupUi(this);
        m_tonaleAudiometrieLinks->setKant(TonaleAudiometrieWidget::LINKS);
        m_tonaleAudiometrieRechts->setKant(TonaleAudiometrieWidget::RECHTS);
}

Meetgegevens::~Meetgegevens()
{
}

int Meetgegevens::getLGRechtsData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getLGdata(Hz);
}

int Meetgegevens::getBGRechtsData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getBGdata(Hz);
}

int Meetgegevens::getUCLRechtsData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getUCLdata(Hz);
}

int Meetgegevens::getLGLinksData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getLGdata(Hz);
}

int Meetgegevens::getBGLinksData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getBGdata(Hz);
}

int Meetgegevens::getUCLLinksData(int Hz)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getUCLdata(Hz);
}

int Meetgegevens::getROZonderData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getROdata(dB);
}

int Meetgegevens::getLOZonderData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getLOdata(dB);
}

int Meetgegevens::getROLOZonderData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getROLOdata(dB);
}

int Meetgegevens::getROMetData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getROdata(dB);
}

int Meetgegevens::getLOMetData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getLOdata(dB);
}

int Meetgegevens::getROLOMetData(int dB)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getROLOdata(dB);
}

void Meetgegevens::setLGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    m_tonaleAudiometrieRechts->setLGdata(Hz, dB);
}

void Meetgegevens::setBGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    m_tonaleAudiometrieRechts->setBGdata(Hz, dB);
}

void Meetgegevens::setUCLRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    m_tonaleAudiometrieRechts->setUCLdata(Hz, dB);
}

void Meetgegevens::setLGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    m_tonaleAudiometrieLinks->setLGdata(Hz, dB);
}

void Meetgegevens::setBGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    m_tonaleAudiometrieLinks->setBGdata(Hz, dB);
}

void Meetgegevens::setUCLLinksData(int Hz, int dB)
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    m_tonaleAudiometrieLinks->setUCLdata(Hz, dB);
}

void Meetgegevens::setROZonderData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    m_vocaleAudiometrieZonder->setROdata(dB, percentage);
}

void Meetgegevens::setLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    m_vocaleAudiometrieZonder->setLOdata(dB, percentage);
}

void Meetgegevens::setROLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    m_vocaleAudiometrieZonder->setROLOdata(dB, percentage);
}

void Meetgegevens::setROMetData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    m_vocaleAudiometrieMet->setROdata(dB, percentage);
}

void Meetgegevens::setLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    m_vocaleAudiometrieMet->setLOdata(dB, percentage);
}

void Meetgegevens::setROLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    m_vocaleAudiometrieMet->setROLOdata(dB, percentage);
}
