#ifndef MODEL_LABELS_H
#define MODEL_LABELS_H

#include <QDate>
#include <QString>

namespace Model
{
    class Universe;

    class Labels
    {
    public:
        explicit Labels(const Universe &universe);
        virtual ~Labels();

        // --- Getters ---
        const Universe &getUniverse() const { return m_universe; }
        QString getPlaceAdjustment() const { return m_placeAdjustment; }
        QDate getTestDate() const { return m_testDate; }

        // --- Setters ---
        void setPlaceAdjustment(const QString &value) { m_placeAdjustment = value; }
        void setTestDate(const QDate &value) { m_testDate = value; }

    private:
        // --- Data members ---
        const Universe &m_universe;
        QString m_placeAdjustment;
        QDate m_testDate;
    };
}

#endif // MODEL_LABELS_H
