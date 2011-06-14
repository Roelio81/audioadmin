#include "model_briefklant.h"

#include <QDomDocument>
#include <QDomElement>

using namespace Model;

BriefKlant::BriefKlant(const Dossier &dossier)
    : m_dossier(dossier)
{
}

BriefKlant::~BriefKlant()
{
}

void BriefKlant::fromDomElement(const QDomElement &e)
{
    m_postdatum = e.attribute("datum");
    QDomElement tekst = e.firstChildElement("tekst");
    if (!tekst.isNull())
        m_tekstblok = tekst.text().replace("\r\n", "\n");
}

QDomElement BriefKlant::toDomElement(QDomDocument &d) const
{
    QDomElement result = d.createElement("brief");
    result.setAttribute("datum", m_postdatum);
    QDomElement tekst = d.createElement("tekst");
    tekst.appendChild(d.createTextNode(m_tekstblok));
    result.appendChild(tekst);
    return result;
}
