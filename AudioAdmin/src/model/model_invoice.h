#ifndef _MODEL_INVOICE_H
#define _MODEL_INVOICE_H

#include <QDate>
#include <QString>

class QDomDocument;
class QDomElement;

namespace Model
{
    class File;

    class Invoice
    {
    public:
        explicit Invoice(const File &file);
        virtual ~Invoice();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        const File &getFile() const { return m_file; }
        QString getNumber() const { return m_number; }
        QDate getDate() const { return m_date; }
        QDate getExpirationDate() const { return m_expirationDate; }
        double getReductionPercentage() const { return m_reductionPercentage; }
        double getVATPercentage() const { return m_vatPercentage; }
        QString getConditions() const { return m_conditions; }
        QString getText() const { return m_text; }

        // --- Setters ---
        void setNumber(const QString &value) { m_number = value; }
        void setDate(const QDate &value) { m_date = value; }
        void setExpirationDate(const QDate &value) { m_expirationDate = value; }
        void setReductionPercentage(double value) { m_reductionPercentage = value; }
        void setVATPercentage(double value) { m_vatPercentage = value; }
        void setConditions(const QString &value) { m_conditions = value; }
        void setText(const QString &value) { m_text = value; }

    private:
        // --- Data members ---
        const File &m_file;
        QString m_number;
        QDate m_date;
        QDate m_expirationDate;
        double m_reductionPercentage;
        double m_vatPercentage;
        QString m_conditions;
        QString m_text;
    };
}

#endif // _MODEL_INVOICE_H
