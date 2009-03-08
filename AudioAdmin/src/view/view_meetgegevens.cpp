#include "view_meetgegevens.h"

using namespace View;

Meetgegevens::Meetgegevens(::QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitMeetgegevens()));
    connect(m_tonaleAudiometrieLinks, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesLinks()));
    connect(m_tonaleAudiometrieRechts, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesRechts()));
    m_tonaleAudiometrieLinks->setKant(TonaleAudiometrieWidget::LINKS);
    m_tonaleAudiometrieRechts->setKant(TonaleAudiometrieWidget::RECHTS);
    m_vocaleAudiometrieZonder->setSoort(VocaleAudiometrieWidget::ZONDER);
    m_vocaleAudiometrieMet->setSoort(VocaleAudiometrieWidget::MET);
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

int Meetgegevens::getLocalisatieZonder()
{
    Q_ASSERT(m_localisatieZonder);
    return m_localisatieZonder->text().isEmpty() ? -10 : m_localisatieZonder->text().toInt();
}

int Meetgegevens::getLocalisatieRechts()
{
    Q_ASSERT(m_localisatieMetRechts);
    return m_localisatieMetRechts->text().isEmpty() ? -10 : m_localisatieMetRechts->text().toInt();
}

int Meetgegevens::getLocalisatieLinks()
{
    Q_ASSERT(m_localisatieMetLinks);
    return m_localisatieMetLinks->text().isEmpty() ? -10 : m_localisatieMetLinks->text().toInt();
}

int Meetgegevens::getLocalisatieBeide()
{
    Q_ASSERT(m_localisatieMetTwee);
    return m_localisatieMetTwee->text().isEmpty() ? -10 : m_localisatieMetTwee->text().toInt();
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

void Meetgegevens::setLocalisatieZonder(int dB)
{
    Q_ASSERT(m_localisatieZonder);
    m_localisatieZonder->setText(dB > 0 ? QString::number(dB) : "");
}

void Meetgegevens::setLocalisatieRechts(int dB)
{
    Q_ASSERT(m_localisatieMetRechts);
    m_localisatieMetRechts->setText(dB > 0 ? QString::number(dB) : "");
}

void Meetgegevens::setLocalisatieLinks(int dB)
{
    Q_ASSERT(m_localisatieMetLinks);
    m_localisatieMetLinks->setText(dB > 0 ? QString::number(dB) : "");
}

void Meetgegevens::setLocalisatieBeide(int dB)
{
    Q_ASSERT(m_localisatieMetTwee);
    m_localisatieMetTwee->setText(dB > 0 ? QString::number(dB) : "");
}


void Meetgegevens::herberekenGemiddeldVerliesLinks()
{
    Q_ASSERT(m_tonaleAudiometrieLinks && m_verliesLinks);
    int meting1 = m_tonaleAudiometrieLinks->getLGdata(1000);
    int meting2 = m_tonaleAudiometrieLinks->getLGdata(2000);
    int meting3 = m_tonaleAudiometrieLinks->getLGdata(4000);
    if (meting1 > 0 && meting2 > 0 && meting3 > 0)
        m_verliesLinks->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_verliesLinks->setText("N/A");
}

void Meetgegevens::herberekenGemiddeldVerliesRechts()
{
    Q_ASSERT(m_tonaleAudiometrieRechts && m_verliesRechts);
    int meting1 = m_tonaleAudiometrieRechts->getLGdata(1000);
    int meting2 = m_tonaleAudiometrieRechts->getLGdata(2000);
    int meting3 = m_tonaleAudiometrieRechts->getLGdata(4000);
    if (meting1 > 0 && meting2 > 0 && meting3 > 0)
        m_verliesRechts->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_verliesRechts->setText("N/A");
}

void Meetgegevens::sluitMeetgegevens()
{
    emit meetgegevensSluiten();
}
