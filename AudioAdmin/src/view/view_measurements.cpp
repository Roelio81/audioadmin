#include "view_measurements.h"

#include <QPainter>

using namespace View;

Measurements::Measurements(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
    connect(m_ui.m_pureToneAudiometryRight, SIGNAL(changedACvalue()), this, SLOT(recalculateAverageLossRight()));
    connect(m_ui.m_pureToneAudiometryLeft, SIGNAL(changedACvalue()), this, SLOT(recalculateAverageLossLeft()));
    connect(m_ui.m_speechAudiometryWithoutAid, SIGNAL(changedREvalue()), this, SLOT(recalculateREWithoutAid()));
    connect(m_ui.m_speechAudiometryWithoutAid, SIGNAL(changedLEvalue()), this, SLOT(recalculateLEWithoutAid()));
    connect(m_ui.m_speechAudiometryWithoutAid, SIGNAL(changedRELEvalue()), this, SLOT(recalculateRELEWithoutAid()));
    connect(m_ui.m_speechAudiometryWithAid, SIGNAL(changedREvalue()), this, SLOT(recalculateREWithAid()));
    connect(m_ui.m_speechAudiometryWithAid, SIGNAL(changedLEvalue()), this, SLOT(recalculateLEWithAid()));
    connect(m_ui.m_speechAudiometryWithAid, SIGNAL(changedRELEvalue()), this, SLOT(recalculateRELEWithAid()));
    m_ui.m_pureToneAudiometryLeft->setSide(PureToneAudiometryWidget::LEFT);
    m_ui.m_pureToneAudiometryRight->setSide(PureToneAudiometryWidget::RIGHT);
    m_ui.m_speechAudiometryWithoutAid->setKind(SpeechAudiometryWidget::WITHOUT);
    m_ui.m_speechAudiometryWithAid->setKind(SpeechAudiometryWidget::WITH);
}

Measurements::~Measurements()
{
}

int Measurements::getACRightData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    return m_ui.m_pureToneAudiometryRight->getACdata(Hz);
}

int Measurements::getBCRightData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    return m_ui.m_pureToneAudiometryRight->getBCdata(Hz);
}

int Measurements::getUCLRightData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    return m_ui.m_pureToneAudiometryRight->getUCLdata(Hz);
}

int Measurements::getACLeftData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    return m_ui.m_pureToneAudiometryLeft->getACdata(Hz);
}

int Measurements::getBCLeftData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    return m_ui.m_pureToneAudiometryLeft->getBCdata(Hz);
}

int Measurements::getUCLLeftData(int Hz) const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    return m_ui.m_pureToneAudiometryLeft->getUCLdata(Hz);
}

int Measurements::getREWithoutData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    return m_ui.m_speechAudiometryWithoutAid->getREdata(dB);
}

int Measurements::getLEWithoutData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    return m_ui.m_speechAudiometryWithoutAid->getLEdata(dB);
}

int Measurements::getRELEWithoutData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    return m_ui.m_speechAudiometryWithoutAid->getRELEdata(dB);
}

int Measurements::getREWithData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    return m_ui.m_speechAudiometryWithAid->getREdata(dB);
}

int Measurements::getLEWithData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    return m_ui.m_speechAudiometryWithAid->getLEdata(dB);
}

int Measurements::getRELEWithData(int dB) const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    return m_ui.m_speechAudiometryWithAid->getRELEdata(dB);
}

int Measurements::getLocalizationWithout() const
{
    Q_ASSERT(m_ui.m_localizationWithout);
    return m_ui.m_localizationWithout->text().isEmpty() ? -10 : m_ui.m_localizationWithout->text().toInt();
}

int Measurements::getLocalizationRight() const
{
    Q_ASSERT(m_ui.m_localizationWithRight);
    return m_ui.m_localizationWithRight->text().isEmpty() ? -10 : m_ui.m_localizationWithRight->text().toInt();
}

int Measurements::getLocalizationLeft() const
{
    Q_ASSERT(m_ui.m_localizationWithLeft);
    return m_ui.m_localizationWithLeft->text().isEmpty() ? -10 : m_ui.m_localizationWithLeft->text().toInt();
}

int Measurements::getLocalizationBoth() const
{
    Q_ASSERT(m_ui.m_localizationWithBoth);
    return m_ui.m_localizationWithBoth->text().isEmpty() ? -10 : m_ui.m_localizationWithBoth->text().toInt();
}

QPixmap Measurements::getPureToneAudiometryLeft() const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_pureToneAudiometryLeft->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getPureToneAudiometryRight() const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    QPixmap result(320, 320);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_pureToneAudiometryRight->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getSpeechAudiometryWithoutAid() const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_speechAudiometryWithoutAid->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QPixmap Measurements::getSpeechAudiometryWithAid() const
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    QPixmap result(560, 200);
    QPainter painter(&result);
    painter.fillRect(result.rect(), Qt::white);
    m_ui.m_speechAudiometryWithAid->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);
    return result;
}

QString Measurements::getAverageLossRight() const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    int m1 = m_ui.m_pureToneAudiometryRight->getACdata(1000);
    int m2 = m_ui.m_pureToneAudiometryRight->getACdata(2000);
    int m3 = m_ui.m_pureToneAudiometryRight->getACdata(4000);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        return QString::number((m1+m2+m3) / 3) + " dB";
    else
        return tr("N/A");

}

QString Measurements::getAverageLossLeft() const
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    int m1 = m_ui.m_pureToneAudiometryLeft->getACdata(1000);
    int m2 = m_ui.m_pureToneAudiometryLeft->getACdata(2000);
    int m3 = m_ui.m_pureToneAudiometryLeft->getACdata(4000);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        return QString::number((m1+m2+m3) / 3) + " dB";
    else
        return tr("N/A");
}

QString Measurements::getREWithout() const
{
    Q_ASSERT(m_ui.m_withoutAidRE);
    return m_ui.m_withoutAidRE->text();
}

QString Measurements::getLEWithout() const
{
    Q_ASSERT(m_ui.m_withoutAidLE);
    return m_ui.m_withoutAidLE->text();
}

QString Measurements::getRELEWithout() const
{
    Q_ASSERT(m_ui.m_withoutAidRELE);
    return m_ui.m_withoutAidRELE->text();
}

QString Measurements::getREWith() const
{
    Q_ASSERT(m_ui.m_withAidRE);
    return m_ui.m_withAidRE->text();
}

QString Measurements::getLEWith() const
{
    Q_ASSERT(m_ui.m_withAidLE);
    return m_ui.m_withAidLE->text();
}

QString Measurements::getRELEWith() const
{
    Q_ASSERT(m_ui.m_withAidRELE);
    return m_ui.m_withAidRELE->text();
}

QString Measurements::getREGain() const
{
    Q_ASSERT(m_ui.m_gainRE);
    return m_ui.m_gainRE->text();
}

QString Measurements::getLEGain() const
{
    Q_ASSERT(m_ui.m_gainLE);
    return m_ui.m_gainLE->text();
}

QString Measurements::getRELEGain() const
{
    Q_ASSERT(m_ui.m_gainRELE);
    return m_ui.m_gainRELE->text();
}

void Measurements::setACRightData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    m_ui.m_pureToneAudiometryRight->setACdata(Hz, dB);
}

void Measurements::setBCRightData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    m_ui.m_pureToneAudiometryRight->setBCdata(Hz, dB);
}

void Measurements::setUCLRightData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryRight);
    m_ui.m_pureToneAudiometryRight->setUCLdata(Hz, dB);
}

void Measurements::setACLeftData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    m_ui.m_pureToneAudiometryLeft->setACdata(Hz, dB);
}

void Measurements::setBCLeftData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    m_ui.m_pureToneAudiometryLeft->setBCdata(Hz, dB);
}

void Measurements::setUCLLeftData(int Hz, int dB)
{
    Q_ASSERT(m_ui.m_pureToneAudiometryLeft);
    m_ui.m_pureToneAudiometryLeft->setUCLdata(Hz, dB);
}

void Measurements::setREWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    m_ui.m_speechAudiometryWithoutAid->setREData(dB, percentage);
}

void Measurements::setLEWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    m_ui.m_speechAudiometryWithoutAid->setLEData(dB, percentage);
}

void Measurements::setRELEWithoutData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    m_ui.m_speechAudiometryWithoutAid->setRELEData(dB, percentage);
}

void Measurements::setROWithData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    m_ui.m_speechAudiometryWithAid->setREData(dB, percentage);
}

void Measurements::setLOWithData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    m_ui.m_speechAudiometryWithAid->setLEData(dB, percentage);
}

void Measurements::setROLOWithData(int dB, int percentage)
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    m_ui.m_speechAudiometryWithAid->setRELEData(dB, percentage);
}

void Measurements::setLocalizationWithout(int dB)
{
    Q_ASSERT(m_ui.m_localizationWithout);
    m_ui.m_localizationWithout->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalizationWithRight(int dB)
{
    Q_ASSERT(m_ui.m_localizationWithRight);
    m_ui.m_localizationWithRight->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalizationWithLeft(int dB)
{
    Q_ASSERT(m_ui.m_localizationWithLeft);
    m_ui.m_localizationWithLeft->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::setLocalizationWithBoth(int dB)
{
    Q_ASSERT(m_ui.m_localizationWithBoth);
    m_ui.m_localizationWithBoth->setText(dB > 0 ? QString::number(dB) : "");
}

void Measurements::recalculateAverageLossRight()
{
    Q_ASSERT(m_ui.m_lossRight);
    m_ui.m_lossRight->setText(getAverageLossRight());
}

void Measurements::recalculateAverageLossLeft()
{
    Q_ASSERT(m_ui.m_lossLeft);
    m_ui.m_lossLeft->setText(getAverageLossLeft());
}

void Measurements::recalculateREWithoutAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    int m1 = m_ui.m_speechAudiometryWithoutAid->getREdata(40);
    int m2 = m_ui.m_speechAudiometryWithoutAid->getREdata(55);
    int m3 = m_ui.m_speechAudiometryWithoutAid->getREdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withoutAidRE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withoutAidRE->setText(tr("N/A"));
    recalculateREGain();
}

void Measurements::recalculateLEWithoutAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    int m1 = m_ui.m_speechAudiometryWithoutAid->getLEdata(40);
    int m2 = m_ui.m_speechAudiometryWithoutAid->getLEdata(55);
    int m3 = m_ui.m_speechAudiometryWithoutAid->getLEdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withoutAidLE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withoutAidLE->setText(tr("N/A"));
    recalculateLEGain();
}

void Measurements::recalculateRELEWithoutAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithoutAid);
    int m1 = m_ui.m_speechAudiometryWithoutAid->getRELEdata(40);
    int m2 = m_ui.m_speechAudiometryWithoutAid->getRELEdata(55);
    int m3 = m_ui.m_speechAudiometryWithoutAid->getRELEdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withoutAidRELE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withoutAidRELE->setText(tr("N/A"));
    recalculateRELEGain();
}

void Measurements::recalculateREWithAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    int m1 = m_ui.m_speechAudiometryWithAid->getREdata(40);
    int m2 = m_ui.m_speechAudiometryWithAid->getREdata(55);
    int m3 = m_ui.m_speechAudiometryWithAid->getREdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withAidRE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withAidRE->setText(tr("N/A"));
    recalculateREGain();
}

void Measurements::recalculateLEWithAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    int m1 = m_ui.m_speechAudiometryWithAid->getLEdata(40);
    int m2 = m_ui.m_speechAudiometryWithAid->getLEdata(55);
    int m3 = m_ui.m_speechAudiometryWithAid->getLEdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withAidLE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withAidLE->setText(tr("N/A"));
    recalculateLEGain();
}

void Measurements::recalculateRELEWithAid()
{
    Q_ASSERT(m_ui.m_speechAudiometryWithAid);
    int m1 = m_ui.m_speechAudiometryWithAid->getRELEdata(40);
    int m2 = m_ui.m_speechAudiometryWithAid->getRELEdata(55);
    int m3 = m_ui.m_speechAudiometryWithAid->getRELEdata(70);
    if (m1 >= 0 && m2 >= 0 && m3 >= 0)
        m_ui.m_withAidRELE->setText(QString::number((m1+m2+m3) / 3) + " %");
    else
        m_ui.m_withAidRELE->setText(tr("N/A"));
    recalculateRELEGain();
}

void Measurements::recalculateREGain()
{
    Q_ASSERT(m_ui.m_withoutAidRE && m_ui.m_withAidRE);
    if ((m_ui.m_withoutAidRE->text() != tr("N/A")) && (m_ui.m_withAidRE->text() != tr("N/A")))
    {
        int withAid = QString(m_ui.m_withAidRE->text()).remove(" %").toInt();
        int withoutAid = QString(m_ui.m_withoutAidRE->text()).remove(" %").toInt();
        m_ui.m_gainRE->setText(QString::number(withAid - withoutAid));
    }
    else
    {
        m_ui.m_gainRE->setText(tr("N/A"));
    }
}

void Measurements::recalculateLEGain()
{
    Q_ASSERT(m_ui.m_withoutAidLE && m_ui.m_withAidLE);
    if ((m_ui.m_withoutAidLE->text() != tr("N/A")) && (m_ui.m_withAidLE->text() != tr("N/A")))
    {
        int withAid = QString(m_ui.m_withAidLE->text()).remove(" %").toInt();
        int withoutAid = QString(m_ui.m_withoutAidLE->text()).remove(" %").toInt();
        m_ui.m_gainLE->setText(QString::number(withAid - withoutAid));
    }
    else
    {
        m_ui.m_gainLE->setText(tr("N/A"));
    }
}

void Measurements::recalculateRELEGain()
{
    Q_ASSERT(m_ui.m_withoutAidRELE && m_ui.m_withAidRELE);
    if ((m_ui.m_withoutAidRELE->text() != tr("N/A")) && (m_ui.m_withAidRELE->text() != tr("N/A")))
{
    int withAid = QString(m_ui.m_withAidRELE->text()).remove(" %").toInt();
    int withoutAid = QString(m_ui.m_withoutAidRELE->text()).remove(" %").toInt();
    m_ui.m_gainRELE->setText(QString::number(withAid - withoutAid));
}
    else
    {
        m_ui.m_gainRELE->setText(tr("N/A"));
    }
}
