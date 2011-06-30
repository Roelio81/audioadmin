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
    m_postalDate = e.attribute("date");
    QDomElement text = e.firstChildElement("text");
    if (!text.isNull())
        m_text = text.text().replace("\r\n", "\n");
    if (m_hasConclusion)
    {
        QDomElement conclusie = e.firstChildElement("conclusion");
        if (!conclusie.isNull())
            m_conclusion = conclusie.text().replace("\r\n", "\n");
    }
}

QDomElement Letter::toDomElement(QDomDocument &d) const
{
    QDomElement letter = d.createElement("letter");
    letter.setAttribute("date", m_postalDate);
    QDomElement text = d.createElement("text");
    text.appendChild(d.createTextNode(m_text));
    letter.appendChild(text);
    if (m_hasConclusion)
    {
        QDomElement conclusion = d.createElement("conclusion");
        conclusion.appendChild(d.createTextNode(m_conclusion));
        letter.appendChild(conclusion);
    }
    return letter;
}

