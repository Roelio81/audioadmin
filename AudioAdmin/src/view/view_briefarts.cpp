#include "view_briefarts.h"

using namespace View;

BriefArts::BriefArts(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefArts()));
}

BriefArts::~BriefArts()
{
}

void BriefArts::sluitBriefArts()
{
    emit briefArtsSluiten();
}

void BriefArts::setAudioloogNaam(const QString &value)
{
    l_audioloogNaam->setText(value);
    l_audioloogNaam_2->setText(value);
}

void BriefArts::setAudioloogStraat(const QString &value)
{
    l_audioloogStraat->setText(value);
}

void BriefArts::setAudioloogGemeente(const QString &value)
{
    l_audioloogGemeente->setText(value);
}

void BriefArts::setAudioloogTelefoon(const QString &value)
{
    l_audioloogTelefoon->setText(value);
}

void BriefArts::setAudioloogGSM(const QString &value)
{
    l_audioloogGSM->setText(value);
}

void BriefArts::setArtsNaam(const QString &value)
{
    l_artsNaam->setText(value);
}

void BriefArts::setArtsStraat(const QString &value)
{
    l_artsStraat->setText(value);
}

void BriefArts::setArtsGemeente(const QString &value)
{
    l_artsGemeente->setText(value);
}
