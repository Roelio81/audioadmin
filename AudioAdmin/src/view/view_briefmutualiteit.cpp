#include "view_briefmutualiteit.h"

using namespace View;

BriefMutualiteit::BriefMutualiteit(QWidget *parent) 
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefMutualiteit()));
    connect(b_bewaren, SIGNAL(clicked()), this, SLOT(bewaarBriefMutualiteit()));
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::setAudioloogNaam(const QString &value)
{
    l_audioloogNaam->setText(value);
    l_audioloogNaam_2->setText(value);
}

void BriefMutualiteit::setAudioloogStraat(const QString &value)
{
    l_audioloogStraat->setText(value);
}

void BriefMutualiteit::setAudioloogGemeente(const QString &value)
{
    l_audioloogGemeente->setText(value);
}

void BriefMutualiteit::setAudioloogTelefoon(const QString &value)
{
    l_audioloogTelefoon->setText(value);
}

void BriefMutualiteit::setAudioloogGSM(const QString &value)
{
    l_audioloogGSM->setText(value);
}

void BriefMutualiteit::setMutualiteitNaam(const QString &value)
{
    l_mutualiteitNaam->setText(value);
}

void BriefMutualiteit::setMutualiteitStraat(const QString &value)
{
    l_mutualiteitStraat->setText(value);
}

void BriefMutualiteit::setMutualiteitGemeente(const QString &value)
{
    l_mutualiteitGemeente->setText(value);
}

void BriefMutualiteit::setPostdatum(const QString &value)
{
    m_postdatum->setText(value);
}

void BriefMutualiteit::setTekst(const QString &value)
{
    m_tekst->setPlainText(value);
}

void BriefMutualiteit::setBesluit(const QString &value)
{
    m_besluit->setPlainText(value);
}

QString BriefMutualiteit::getPostdatum() const
{
    return m_postdatum->text();
}

QString BriefMutualiteit::getTekst() const
{
    return m_tekst->toPlainText();
}

QString BriefMutualiteit::getBesluit() const
{
    return m_besluit->toPlainText();
}

void BriefMutualiteit::sluitBriefMutualiteit()
{
    emit briefMutualiteitSluiten();
}

void BriefMutualiteit::bewaarBriefMutualiteit()
{
    emit briefMutualiteitBewaren();
}
