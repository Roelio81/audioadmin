#include "view_meetgegevens.h"

using namespace View;

Meetgegevens::Meetgegevens(::QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitMeetgegevens()));
    connect(b_bewaren, SIGNAL(clicked()), this, SLOT(bewaarMeetgegevens()));
    connect(m_tonaleAudiometrieLinks, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesLinks()));
    connect(m_tonaleAudiometrieRechts, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesRechts()));
    connect(m_vocaleAudiometrieZonder, SIGNAL(wijzigingROwaarde()), this, SLOT(herberekenROZonder()));
    connect(m_vocaleAudiometrieZonder, SIGNAL(wijzigingLOwaarde()), this, SLOT(herberekenLOZonder()));
    connect(m_vocaleAudiometrieZonder, SIGNAL(wijzigingROLOwaarde()), this, SLOT(herberekenROLOZonder()));
    connect(m_vocaleAudiometrieMet, SIGNAL(wijzigingROwaarde()), this, SLOT(herberekenROMet()));
    connect(m_vocaleAudiometrieMet, SIGNAL(wijzigingLOwaarde()), this, SLOT(herberekenLOMet()));
    connect(m_vocaleAudiometrieMet, SIGNAL(wijzigingROLOwaarde()), this, SLOT(herberekenROLOMet()));
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
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
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
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_verliesRechts->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_verliesRechts->setText("N/A");
}

void Meetgegevens::herberekenROZonder()
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    int meting1 = m_vocaleAudiometrieZonder->getROdata(40);
    int meting2 = m_vocaleAudiometrieZonder->getROdata(55);
    int meting3 = m_vocaleAudiometrieZonder->getROdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_zonderApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_zonderApparaatRO->setText("N/A");
    herberekenROWinst();
}

void Meetgegevens::herberekenLOZonder()
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    int meting1 = m_vocaleAudiometrieZonder->getLOdata(40);
    int meting2 = m_vocaleAudiometrieZonder->getLOdata(55);
    int meting3 = m_vocaleAudiometrieZonder->getLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_zonderApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_zonderApparaatLO->setText("N/A");
    herberekenLOWinst();
}

void Meetgegevens::herberekenROLOZonder()
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    int meting1 = m_vocaleAudiometrieZonder->getROLOdata(40);
    int meting2 = m_vocaleAudiometrieZonder->getROLOdata(55);
    int meting3 = m_vocaleAudiometrieZonder->getROLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_zonderApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_zonderApparaatROLO->setText("N/A");
    herberekenROLOWinst();
}

void Meetgegevens::herberekenROMet()
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    int meting1 = m_vocaleAudiometrieMet->getROdata(40);
    int meting2 = m_vocaleAudiometrieMet->getROdata(55);
    int meting3 = m_vocaleAudiometrieMet->getROdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_metApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_metApparaatRO->setText("N/A");
    herberekenROWinst();
}

void Meetgegevens::herberekenLOMet()
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    int meting1 = m_vocaleAudiometrieMet->getLOdata(40);
    int meting2 = m_vocaleAudiometrieMet->getLOdata(55);
    int meting3 = m_vocaleAudiometrieMet->getLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_metApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_metApparaatLO->setText("N/A");
    herberekenLOWinst();
}

void Meetgegevens::herberekenROLOMet()
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    int meting1 = m_vocaleAudiometrieMet->getROLOdata(40);
    int meting2 = m_vocaleAudiometrieMet->getROLOdata(55);
    int meting3 = m_vocaleAudiometrieMet->getROLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_metApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3));
    else
        m_metApparaatROLO->setText("N/A");
    herberekenROLOWinst();
}

void Meetgegevens::herberekenROWinst()
{
    Q_ASSERT(m_zonderApparaatRO && m_metApparaatRO);
    if ((m_zonderApparaatRO->text() != "N/A") && (m_metApparaatRO->text() != "N/A"))
        m_winstRO->setText(QString::number(m_metApparaatRO->text().toInt() - m_zonderApparaatRO->text().toInt()));
    else
        m_winstRO->setText("N/A");
}

void Meetgegevens::herberekenLOWinst()
{
    Q_ASSERT(m_zonderApparaatLO && m_metApparaatLO);
    if ((m_zonderApparaatLO->text() != "N/A") && (m_metApparaatLO->text() != "N/A"))
        m_winstLO->setText(QString::number(m_metApparaatLO->text().toInt() - m_zonderApparaatLO->text().toInt()));
    else
        m_winstLO->setText("N/A");
}

void Meetgegevens::herberekenROLOWinst()
{
    Q_ASSERT(m_zonderApparaatROLO && m_metApparaatROLO);
    if ((m_zonderApparaatROLO->text() != "N/A") && (m_metApparaatROLO->text() != "N/A"))
        m_winstROLO->setText(QString::number(m_metApparaatROLO->text().toInt() - m_zonderApparaatROLO->text().toInt()));
    else
        m_winstROLO->setText("N/A");
}

void Meetgegevens::sluitMeetgegevens()
{
    emit meetgegevensSluiten();
}

void Meetgegevens::bewaarMeetgegevens()
{
    emit meetgegevensBewaren();
}
