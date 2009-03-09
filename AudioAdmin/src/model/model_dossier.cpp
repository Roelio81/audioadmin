#include "model_dossier.h"

#include <QDomElement>

using namespace Model;

Dossier::Dossier(int id)
: m_id(id)
, m_klant()
, m_arts(-1)
{
}

Dossier::~Dossier()
{
}

void Dossier::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "nkoArts")
        {
            m_arts = element.attributeNode("id").value().toInt();
        }
        else if (element.tagName() == "audiometrie")
        {
            m_meetgegevens.fromDomElement(element);
        }
    }

    m_klant.fromDomElement(e);
}

QDomElement Dossier::toDomElement() const
{
    QDomElement result = m_klant.toDomElement();
    QDomElement nkoArts;
    nkoArts.setTagName("nkoArts");
    nkoArts.setAttribute("id", QString::number(m_arts));
    result.appendChild(nkoArts);
    QDomElement audiometrie = m_meetgegevens.toDomElement();
    audiometrie.appendChild(audiometrie);
    result.setTagName("dossier");
    return result;
}

Klant &Dossier::getKlant()
{
    return m_klant;
}

Meetgegevens &Dossier::getMeetgegevens()
{
    return m_meetgegevens;
}

int Dossier::getId() const
{
    return m_id;
}

int Dossier::getArts() const
{
    return m_arts;
}

QString Dossier::getBriefArtsPostdatum() const
{
    return m_briefArtsPostdatum;
}

QString Dossier::getBriefArtsTekstblok() const
{
    return m_briefArtsTekstblok;
}

QString Dossier::getBriefArtsConclusie() const
{
    return m_briefArtsConclusie;
}

QString Dossier::getBriefKlantPostdatum() const
{
    return m_briefKlantPostdatum;
}

QString Dossier::getBriefKlantTekstblok() const
{
    return m_briefKlantTekstblok;
}

QString Dossier::getBriefMutualiteitPostdatum() const
{
    return m_briefMutualiteitPostdatum;
}

QString Dossier::getBriefMutualiteitTekstblok() const
{
    return m_briefMutualiteitTekstblok;
}

QString Dossier::getBriefMutualiteitConclusie() const
{
    return m_briefMutualiteitConclusie;
}

void Dossier::setArts(int value)
{
    m_arts = value;
}

void Dossier::setBriefArtsPostdatum(const QString &value)
{
    m_briefArtsPostdatum = value;
}

void Dossier::setBriefArtsTekstblok(const QString &value)
{
    m_briefArtsTekstblok = value;
}

void Dossier::setBriefArtsConclusie(const QString &value)
{
    m_briefArtsConclusie = value;
}

void Dossier::setBriefKlantPostdatum(const QString &value)
{
    m_briefKlantPostdatum = value;
}

void Dossier::setBriefKlantTekstblok(const QString &value)
{
    m_briefKlantTekstblok = value;
}

void Dossier::setBriefMutualiteitPostdatum(const QString &value)
{
    m_briefMutualiteitPostdatum = value;
}

void Dossier::setBriefMutualiteitTekstblok(const QString &value)
{
    m_briefMutualiteitTekstblok = value;
}

void Dossier::setBriefMutualiteitConclusie(const QString &value)
{
    m_briefMutualiteitConclusie = value;
}
