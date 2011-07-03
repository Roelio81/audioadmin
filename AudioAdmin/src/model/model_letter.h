#ifndef MODEL_LETTER_H
#define MODEL_LETTER_H

#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class File;

    class Letter
    {
    public:
        explicit Letter(const File &file, bool hasConclusion);
        virtual ~Letter();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        const File &getFile() const { return m_file; }
        QString getPostalDate() const { return m_postalDate; }
        QString getText() const { return m_text; }
        QString getConclusion() const { return m_conclusion; }
        bool hasConclusion() const { return m_hasConclusion; }

        // --- Setters ---
        void setPostalDate(const QString &value) { m_postalDate = value; }
        void setText(const QString &value) { m_text = value; }
        void setConclusion(const QString &value) { m_conclusion = value; }

    private:
        // --- Data members ---
        const File &m_file;
        QString m_postalDate;
        QString m_text;
        QString m_conclusion;
        bool m_hasConclusion;
    };
}

#endif // MODEL_LETTER_H
