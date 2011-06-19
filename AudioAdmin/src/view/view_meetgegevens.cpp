#include "view_meetgegevens.h"

#include <QPainter>

using namespace View;

Meetgegevens::Meetgegevens(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
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

int Meetgegevens::getLGRechtsData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getLGdata(Hz);
}

int Meetgegevens::getBGRechtsData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getBGdata(Hz);
}

int Meetgegevens::getUCLRechtsData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    return m_tonaleAudiometrieRechts->getUCLdata(Hz);
}

int Meetgegevens::getLGLinksData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getLGdata(Hz);
}

int Meetgegevens::getBGLinksData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getBGdata(Hz);
}

int Meetgegevens::getUCLLinksData(int Hz) const
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    return m_tonaleAudiometrieLinks->getUCLdata(Hz);
}

int Meetgegevens::getROZonderData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getROdata(dB);
}

int Meetgegevens::getLOZonderData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getLOdata(dB);
}

int Meetgegevens::getROLOZonderData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    return m_vocaleAudiometrieZonder->getROLOdata(dB);
}

int Meetgegevens::getROMetData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getROdata(dB);
}

int Meetgegevens::getLOMetData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getLOdata(dB);
}

int Meetgegevens::getROLOMetData(int dB) const
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    return m_vocaleAudiometrieMet->getROLOdata(dB);
}

int Meetgegevens::getLocalisatieZonder() const
{
    Q_ASSERT(m_localisatieZonder);
    return m_localisatieZonder->text().isEmpty() ? -10 : m_localisatieZonder->text().toInt();
}

int Meetgegevens::getLocalisatieRechts() const
{
    Q_ASSERT(m_localisatieMetRechts);
    return m_localisatieMetRechts->text().isEmpty() ? -10 : m_localisatieMetRechts->text().toInt();
}

int Meetgegevens::getLocalisatieLinks() const
{
    Q_ASSERT(m_localisatieMetLinks);
    return m_localisatieMetLinks->text().isEmpty() ? -10 : m_localisatieMetLinks->text().toInt();
}

int Meetgegevens::getLocalisatieBeide() const
{
    Q_ASSERT(m_localisatieMetTwee);
    return m_localisatieMetTwee->text().isEmpty() ? -10 : m_localisatieMetTwee->text().toInt();
}

QPixmap Meetgegevens::getTonaleLinks() const
{
    Q_ASSERT(m_tonaleAudiometrieLinks);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_tonaleAudiometrieLinks->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Meetgegevens::getTonaleRechts() const
{
    Q_ASSERT(m_tonaleAudiometrieRechts);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_tonaleAudiometrieRechts->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Meetgegevens::getVocaleZonderApparaat() const
{
    Q_ASSERT(m_vocaleAudiometrieZonder);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_vocaleAudiometrieZonder->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Meetgegevens::getVocaleMetApparaat() const
{
    Q_ASSERT(m_vocaleAudiometrieMet);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_vocaleAudiometrieMet->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QString Meetgegevens::getROZonder() const
{
    Q_ASSERT(m_zonderApparaatRO);
    return m_zonderApparaatRO->text();
}

QString Meetgegevens::getLOZonder() const
{
    Q_ASSERT(m_zonderApparaatLO);
    return m_zonderApparaatLO->text();
}

QString Meetgegevens::getROLOZonder() const
{
    Q_ASSERT(m_zonderApparaatROLO);
    return m_zonderApparaatROLO->text();
}

QString Meetgegevens::getROMet() const
{
    Q_ASSERT(m_metApparaatRO);
    return m_metApparaatRO->text();
}

QString Meetgegevens::getLOMet() const
{
    Q_ASSERT(m_metApparaatLO);
    return m_metApparaatLO->text();
}

QString Meetgegevens::getROLOMet() const
{
    Q_ASSERT(m_metApparaatROLO);
    return m_metApparaatROLO->text();
}

QString Meetgegevens::getROWinst() const
{
    Q_ASSERT(m_winstRO);
    return m_winstRO->text();
}

QString Meetgegevens::getLOWinst() const
{
    Q_ASSERT(m_winstLO);
    return m_winstLO->text();
}

QString Meetgegevens::getROLOWinst() const
{
    Q_ASSERT(m_winstROLO);
    return m_winstROLO->text();
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
        m_verliesLinks->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_verliesRechts->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_zonderApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_zonderApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_zonderApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_metApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_metApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
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
        m_metApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_metApparaatROLO->setText("N/A");
    herberekenROLOWinst();
}

void Meetgegevens::herberekenROWinst()
{
    Q_ASSERT(m_zonderApparaatRO && m_metApparaatRO);
    if ((m_zonderApparaatRO->text() != "N/A") && (m_metApparaatRO->text() != "N/A"))
    {
        int metApparaat = QString(m_metApparaatRO->text()).remove(" %").toInt();
        int zonderApparaat = QString(m_zonderApparaatRO->text()).remove(" %").toInt();
        m_winstRO->setText(QString::number(metApparaat - zonderApparaat));
    }
    else
    {
        m_winstRO->setText("N/A");
    }
}

void Meetgegevens::herberekenLOWinst()
{
    Q_ASSERT(m_zonderApparaatLO && m_metApparaatLO);
    if ((m_zonderApparaatLO->text() != "N/A") && (m_metApparaatLO->text() != "N/A"))
    {
        int metApparaat = QString(m_metApparaatLO->text()).remove(" %").toInt();
        int zonderApparaat = QString(m_zonderApparaatLO->text()).remove(" %").toInt();
        m_winstLO->setText(QString::number(metApparaat - zonderApparaat));
    }
    else
    {
        m_winstLO->setText("N/A");
    }
}

void Meetgegevens::herberekenROLOWinst()
{
    Q_ASSERT(m_zonderApparaatROLO && m_metApparaatROLO);
    if ((m_zonderApparaatROLO->text() != "N/A") && (m_metApparaatROLO->text() != "N/A"))
{
    int metApparaat = QString(m_metApparaatROLO->text()).remove(" %").toInt();
    int zonderApparaat = QString(m_zonderApparaatROLO->text()).remove(" %").toInt();
    m_winstROLO->setText(QString::number(metApparaat - zonderApparaat));
}
    else
    {
        m_winstROLO->setText("N/A");
    }
}
