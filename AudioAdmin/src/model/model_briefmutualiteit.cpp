#include "model_briefmutualiteit.h"

#include <QDomDocument>
#include <QDomElement>

using namespace Model;

BriefMutualiteit::BriefMutualiteit(const Dossier &dossier)
    : m_dossier(dossier)
{
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::fromDomElement(const QDomElement &e)
{
    m_postdatum = e.attribute("datum");
    QDomElement tekst = e.firstChildElement("tekst");
    if (!tekst.isNull())
        m_tekstblok = tekst.text().replace("\r\n", "\n");
    QDomElement conclusie = e.firstChildElement("besluit");
    if (!conclusie.isNull())
        m_conclusie = conclusie.text().replace("\r\n", "\n");
}

QDomElement BriefMutualiteit::toDomElement(QDomDocument &d) const
{
    QDomElement brief = d.createElement("brief");
    brief.setAttribute("datum", m_postdatum);
    QDomElement tekst = d.createElement("tekst");
    tekst.appendChild(d.createTextNode(m_tekstblok));
    brief.appendChild(tekst);
    QDomElement conclusie = d.createElement("conclusie");
    conclusie.appendChild(d.createTextNode(m_conclusie));
    brief.appendChild(conclusie);
    return brief;
}
