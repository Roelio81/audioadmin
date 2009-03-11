#include "view_briefklant.h"

using namespace View;

BriefKlant::BriefKlant(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefKlant()));
}

BriefKlant::~BriefKlant()
{
}

void BriefKlant::sluitBriefKlant()
{
    emit briefKlantSluiten();
}

void BriefKlant::setAudioloogNaam(const QString &value)
{
    l_audioloogNaam->setText(value);
    l_audioloogNaam_2->setText(value);
}

void BriefKlant::setAudioloogStraat(const QString &value)
{
    l_audioloogStraat->setText(value);
}

void BriefKlant::setAudioloogGemeente(const QString &value)
{
    l_audioloogGemeente->setText(value);
}

void BriefKlant::setAudioloogTelefoon(const QString &value)
{
    l_audioloogTelefoon->setText(value);
}

void BriefKlant::setAudioloogGSM(const QString &value)
{
    l_audioloogGSM->setText(value);
}

void BriefKlant::setKlantNaam(const QString &value)
{
    l_klantNaam->setText(value);
}

void BriefKlant::setKlantStraat(const QString &value)
{
    l_klantStraat->setText(value);
}

void BriefKlant::setKlantGemeente(const QString &value)
{
    l_klantGemeente->setText(value);
}

void BriefKlant::setAanspreking(const QString &value)
{
    l_aanspreking->setText(value);
}

void BriefKlant::setPostdatum(const QString &value)
{
    m_postdatum->setText(value);
}

void BriefKlant::setTekst(const QString &value)
{
    m_tekst->setPlainText(value);
}
