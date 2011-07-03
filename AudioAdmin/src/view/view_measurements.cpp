#include "view_measurements.h"

#include <QPainter>

using namespace View;

Measurements::Measurements(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
    connect(m_ui.m_tonaleAudiometrieLinks, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesLinks()));
    connect(m_ui.m_tonaleAudiometrieRechts, SIGNAL(wijzigingLGwaarde()), this, SLOT(herberekenGemiddeldVerliesRechts()));
    connect(m_ui.m_vocaleAudiometrieZonder, SIGNAL(wijzigingROwaarde()), this, SLOT(herberekenROZonder()));
    connect(m_ui.m_vocaleAudiometrieZonder, SIGNAL(wijzigingLOwaarde()), this, SLOT(herberekenLOZonder()));
    connect(m_ui.m_vocaleAudiometrieZonder, SIGNAL(wijzigingROLOwaarde()), this, SLOT(herberekenROLOZonder()));
    connect(m_ui.m_vocaleAudiometrieMet, SIGNAL(wijzigingROwaarde()), this, SLOT(herberekenROMet()));
    connect(m_ui.m_vocaleAudiometrieMet, SIGNAL(wijzigingLOwaarde()), this, SLOT(herberekenLOMet()));
    connect(m_ui.m_vocaleAudiometrieMet, SIGNAL(wijzigingROLOwaarde()), this, SLOT(herberekenROLOMet()));
    m_ui.m_tonaleAudiometrieLinks->setKant(TonaleAudiometrieWidget::LINKS);
    m_ui.m_tonaleAudiometrieRechts->setKant(TonaleAudiometrieWidget::RECHTS);
    m_ui.m_vocaleAudiometrieZonder->setSoort(VocaleAudiometrieWidget::ZONDER);
    m_ui.m_vocaleAudiometrieMet->setSoort(VocaleAudiometrieWidget::MET);
}

Measurements::~Measurements()
{
}

int Measurements::getLGRechtsData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    return m_ui.m_tonaleAudiometrieRechts->getLGdata(Hz);
}

int Measurements::getBGRechtsData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    return m_ui.m_tonaleAudiometrieRechts->getBGdata(Hz);
}

int Measurements::getUCLRechtsData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    return m_ui.m_tonaleAudiometrieRechts->getUCLdata(Hz);
}

int Measurements::getLGLinksData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    return m_ui.m_tonaleAudiometrieLinks->getLGdata(Hz);
}

int Measurements::getBGLinksData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    return m_ui.m_tonaleAudiometrieLinks->getBGdata(Hz);
}

int Measurements::getUCLLinksData(int Hz) const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    return m_ui.m_tonaleAudiometrieLinks->getUCLdata(Hz);
}

int Measurements::getROZonderData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    return m_ui.m_vocaleAudiometrieZonder->getROdata(dB);
}

int Measurements::getLOZonderData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    return m_ui.m_vocaleAudiometrieZonder->getLOdata(dB);
}

int Measurements::getROLOZonderData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    return m_ui.m_vocaleAudiometrieZonder->getROLOdata(dB);
}

int Measurements::getROMetData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    return m_ui.m_vocaleAudiometrieMet->getROdata(dB);
}

int Measurements::getLOMetData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    return m_ui.m_vocaleAudiometrieMet->getLOdata(dB);
}

int Measurements::getROLOMetData(int dB) const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    return m_ui.m_vocaleAudiometrieMet->getROLOdata(dB);
}

int Measurements::getLocalisatieZonder() const
{
    Q_ASSERT(m_ui.m_localisatieZonder);
    return m_ui.m_localisatieZonder->text().isEmpty() ? -10 : m_ui.m_localisatieZonder->text().toInt();
}

int Measurements::getLocalisatieRechts() const
{
    Q_ASSERT(m_ui.m_localisatieMetRechts);
    return m_ui.m_localisatieMetRechts->text().isEmpty() ? -10 : m_ui.m_localisatieMetRechts->text().toInt();
}

int Measurements::getLocalisatieLinks() const
{
    Q_ASSERT(m_ui.m_localisatieMetLinks);
    return m_ui.m_localisatieMetLinks->text().isEmpty() ? -10 : m_ui.m_localisatieMetLinks->text().toInt();
}

int Measurements::getLocalisatieBeide() const
{
    Q_ASSERT(m_ui.m_localisatieMetTwee);
    return m_ui.m_localisatieMetTwee->text().isEmpty() ? -10 : m_ui.m_localisatieMetTwee->text().toInt();
}

QPixmap Measurements::getTonaleLinks() const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_tonaleAudiometrieLinks->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getTonaleRechts() const
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_tonaleAudiometrieRechts->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getVocaleZonderApparaat() const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_vocaleAudiometrieZonder->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getVocaleMetApparaat() const
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_vocaleAudiometrieMet->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QString Measurements::getROZonder() const
{
    Q_ASSERT(m_ui.m_zonderApparaatRO);
    return m_ui.m_zonderApparaatRO->text();
}

QString Measurements::getLOZonder() const
{
    Q_ASSERT(m_ui.m_zonderApparaatLO);
    return m_ui.m_zonderApparaatLO->text();
}

QString Measurements::getROLOZonder() const
{
    Q_ASSERT(m_ui.m_zonderApparaatROLO);
    return m_ui.m_zonderApparaatROLO->text();
}

QString Measurements::getROMet() const
{
    Q_ASSERT(m_ui.m_metApparaatRO);
    return m_ui.m_metApparaatRO->text();
}

QString Measurements::getLOMet() const
{
    Q_ASSERT(m_ui.m_metApparaatLO);
    return m_ui.m_metApparaatLO->text();
}

QString Measurements::getROLOMet() const
{
    Q_ASSERT(m_ui.m_metApparaatROLO);
    return m_ui.m_metApparaatROLO->text();
}

QString Measurements::getROWinst() const
{
    Q_ASSERT(m_ui.m_winstRO);
    return m_ui.m_winstRO->text();
}

QString Measurements::getLOWinst() const
{
    Q_ASSERT(m_ui.m_winstLO);
    return m_ui.m_winstLO->text();
}

QString Measurements::getROLOWinst() const
{
    Q_ASSERT(m_ui.m_winstROLO);
    return m_ui.m_winstROLO->text();
}

void Measurements::setLGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    m_ui.m_tonaleAudiometrieRechts->setLGdata(Hz, dB);
}

void Measurements::setBGRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    m_ui.m_tonaleAudiometrieRechts->setBGdata(Hz, dB);
}

void Measurements::setUCLRechtsData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts);
    m_ui.m_tonaleAudiometrieRechts->setUCLdata(Hz, dB);
}

void Measurements::setLGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    m_ui.m_tonaleAudiometrieLinks->setLGdata(Hz, dB);
}

void Measurements::setBGLinksData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    m_ui.m_tonaleAudiometrieLinks->setBGdata(Hz, dB);
}

void Measurements::setUCLLinksData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks);
    m_ui.m_tonaleAudiometrieLinks->setUCLdata(Hz, dB);
}

void Measurements::setROZonderData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    m_ui.m_vocaleAudiometrieZonder->setROdata(dB, percentage);
}

void Measurements::setLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    m_ui.m_vocaleAudiometrieZonder->setLOdata(dB, percentage);
}

void Measurements::setROLOZonderData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    m_ui.m_vocaleAudiometrieZonder->setROLOdata(dB, percentage);
}

void Measurements::setROMetData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    m_ui.m_vocaleAudiometrieMet->setROdata(dB, percentage);
}

void Measurements::setLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    m_ui.m_vocaleAudiometrieMet->setLOdata(dB, percentage);
}

void Measurements::setROLOMetData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    m_ui.m_vocaleAudiometrieMet->setROLOdata(dB, percentage);
}

void Measurements::setLocalisatieZonder(int dB)
{
    Q_ASSERT(m_ui.m_localisatieZonder);
    m_ui.m_localisatieZonder->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalisatieRechts(int dB)
{
    Q_ASSERT(m_ui.m_localisatieMetRechts);
    m_ui.m_localisatieMetRechts->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalisatieLinks(int dB)
{
    Q_ASSERT(m_ui.m_localisatieMetLinks);
    m_ui.m_localisatieMetLinks->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalisatieBeide(int dB)
{
    Q_ASSERT(m_ui.m_localisatieMetTwee);
    m_ui.m_localisatieMetTwee->setText(dB > 0 ? QString::number(dB) : "");
}


void Measurements::herberekenGemiddeldVerliesLinks()
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieLinks && m_ui.m_verliesLinks);
    int meting1 = m_ui.m_tonaleAudiometrieLinks->getLGdata(1000);
    int meting2 = m_ui.m_tonaleAudiometrieLinks->getLGdata(2000);
    int meting3 = m_ui.m_tonaleAudiometrieLinks->getLGdata(4000);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_verliesLinks->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_verliesLinks->setText("N/A");
}

void Measurements::herberekenGemiddeldVerliesRechts()
{
    Q_ASSERT(m_ui.m_tonaleAudiometrieRechts && m_ui.m_verliesRechts);
    int meting1 = m_ui.m_tonaleAudiometrieRechts->getLGdata(1000);
    int meting2 = m_ui.m_tonaleAudiometrieRechts->getLGdata(2000);
    int meting3 = m_ui.m_tonaleAudiometrieRechts->getLGdata(4000);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_verliesRechts->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_verliesRechts->setText("N/A");
}

void Measurements::herberekenROZonder()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    int meting1 = m_ui.m_vocaleAudiometrieZonder->getROdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieZonder->getROdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieZonder->getROdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_zonderApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_zonderApparaatRO->setText("N/A");
    herberekenROWinst();
}

void Measurements::herberekenLOZonder()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    int meting1 = m_ui.m_vocaleAudiometrieZonder->getLOdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieZonder->getLOdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieZonder->getLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_zonderApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_zonderApparaatLO->setText("N/A");
    herberekenLOWinst();
}

void Measurements::herberekenROLOZonder()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieZonder);
    int meting1 = m_ui.m_vocaleAudiometrieZonder->getROLOdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieZonder->getROLOdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieZonder->getROLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_zonderApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_zonderApparaatROLO->setText("N/A");
    herberekenROLOWinst();
}

void Measurements::herberekenROMet()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    int meting1 = m_ui.m_vocaleAudiometrieMet->getROdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieMet->getROdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieMet->getROdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_metApparaatRO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_metApparaatRO->setText("N/A");
    herberekenROWinst();
}

void Measurements::herberekenLOMet()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    int meting1 = m_ui.m_vocaleAudiometrieMet->getLOdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieMet->getLOdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieMet->getLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_metApparaatLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_metApparaatLO->setText("N/A");
    herberekenLOWinst();
}

void Measurements::herberekenROLOMet()
{
    Q_ASSERT(m_ui.m_vocaleAudiometrieMet);
    int meting1 = m_ui.m_vocaleAudiometrieMet->getROLOdata(40);
    int meting2 = m_ui.m_vocaleAudiometrieMet->getROLOdata(55);
    int meting3 = m_ui.m_vocaleAudiometrieMet->getROLOdata(70);
    if (meting1 >= 0 && meting2 >= 0 && meting3 >= 0)
        m_ui.m_metApparaatROLO->setText(QString::number((meting1+meting2+meting3) / 3) + " %");
    else
        m_ui.m_metApparaatROLO->setText("N/A");
    herberekenROLOWinst();
}

void Measurements::herberekenROWinst()
{
    Q_ASSERT(m_ui.m_zonderApparaatRO && m_ui.m_metApparaatRO);
    if ((m_ui.m_zonderApparaatRO->text() != "N/A") && (m_ui.m_metApparaatRO->text() != "N/A"))
    {
        int metApparaat = QString(m_ui.m_metApparaatRO->text()).remove(" %").toInt();
        int zonderApparaat = QString(m_ui.m_zonderApparaatRO->text()).remove(" %").toInt();
        m_ui.m_winstRO->setText(QString::number(metApparaat - zonderApparaat));
    }
    else
    {
        m_ui.m_winstRO->setText("N/A");
    }
}

void Measurements::herberekenLOWinst()
{
    Q_ASSERT(m_ui.m_zonderApparaatLO && m_ui.m_metApparaatLO);
    if ((m_ui.m_zonderApparaatLO->text() != "N/A") && (m_ui.m_metApparaatLO->text() != "N/A"))
    {
        int metApparaat = QString(m_ui.m_metApparaatLO->text()).remove(" %").toInt();
        int zonderApparaat = QString(m_ui.m_zonderApparaatLO->text()).remove(" %").toInt();
        m_ui.m_winstLO->setText(QString::number(metApparaat - zonderApparaat));
    }
    else
    {
        m_ui.m_winstLO->setText("N/A");
    }
}

void Measurements::herberekenROLOWinst()
{
    Q_ASSERT(m_ui.m_zonderApparaatROLO && m_ui.m_metApparaatROLO);
    if ((m_ui.m_zonderApparaatROLO->text() != "N/A") && (m_ui.m_metApparaatROLO->text() != "N/A"))
{
    int metApparaat = QString(m_ui.m_metApparaatROLO->text()).remove(" %").toInt();
    int zonderApparaat = QString(m_ui.m_zonderApparaatROLO->text()).remove(" %").toInt();
    m_ui.m_winstROLO->setText(QString::number(metApparaat - zonderApparaat));
}
    else
    {
        m_ui.m_winstROLO->setText("N/A");
    }
}
