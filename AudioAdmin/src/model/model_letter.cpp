#include "model_letter.h"

#include <QDomDocument>
#include <QDomElement>

using namespace Model;

Letter::Letter(const File &file, bool hasConclusion)
    : m_file(file)
    , m_hasConclusion(hasConclusion)
{
}

Letter::~Letter()
{
}

void Letter::fromDomElement(const QDomElement &e)
{
    m_postalDate = e.attribute("datum");
    QDomElement text = e.firstChildElement("tekst");
    if (!text.isNull())
        m_text = text.text().replace("\r\n", "\n");
    if (m_hasConclusion)
    {
        QDomElement conclusie = e.firstChildElement("besluit");
        if (!conclusie.isNull())
            m_conclusion = conclusie.text().replace("\r\n", "\n");
    }
}

QDomElement Letter::toDomElement(QDomDocument &d) const
{
    QDomElement brief = d.createElement("brief");
    brief.setAttribute("datum", m_postalDate);
    QDomElement text = d.createElement("tekst");
    text.appendChild(d.createTextNode(m_text));
    brief.appendChild(text);
    if (m_hasConclusion)
    {
        QDomElement conclusion = d.createElement("conclusie");
        conclusion.appendChild(d.createTextNode(m_conclusion));
        brief.appendChild(conclusion);
    }
    return brief;
}

