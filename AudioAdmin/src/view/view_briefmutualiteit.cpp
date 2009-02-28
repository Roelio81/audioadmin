#include "view_briefmutualiteit.h"

using namespace View;

BriefMutualiteit::BriefMutualiteit(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefMutualiteit()));
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::sluitBriefMutualiteit()
{
    emit briefMutualiteitSluiten();
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
