#include "view_briefarts.h"

using namespace View;

BriefArts::BriefArts(QWidget *parent) 
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
    connect(b_ok, SIGNAL(clicked()), this, SLOT(okBriefArts()));
    connect(b_annuleren, SIGNAL(clicked()), this, SLOT(annuleerBriefArts()));
}

BriefArts::~BriefArts()
{
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

void BriefArts::setPostdatum(const QString &value)
{
    m_postdatum->setText(value);
}

void BriefArts::setTekst(const QString &value)
{
    m_tekst->setPlainText(value);
}

void BriefArts::setBesluit(const QString &value)
{
    m_besluit->setPlainText(value);
}

QString BriefArts::getPostdatum() const
{
    return m_postdatum->text();
}

QString BriefArts::getTekst() const
{
    return m_tekst->toPlainText();
}

QString BriefArts::getBesluit() const
{
    return m_besluit->toPlainText();
}

void BriefArts::okBriefArts()
{
    emit briefArtsBewaren();
    emit briefArtsSluiten();
}

void BriefArts::annuleerBriefArts()
{
    emit briefArtsSluiten();
}
