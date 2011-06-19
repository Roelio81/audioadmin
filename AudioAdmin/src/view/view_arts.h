#ifndef _VIEW_ARTS_H
#define _VIEW_ARTS_H

#include <QObject>
#include <QDate>

namespace View
{
    class Universum;

    class Arts : QObject
    {
    Q_OBJECT
    public:
        explicit Arts(Universum &universum);
        virtual ~Arts();

        // --- Getters ---
        QString getNaam() const;
        QString getVoornaam() const;
        QString getStraat() const;
        int getPostcode() const;
        QString getGemeente() const;
        QString getTelefoon() const;
        QString getOpmerkingen() const;

        // --- Setters ---
        void setNaam(const QString &value);
        void setVoornaam(const QString &value);
        void setStraat(const QString &value);
        void setPostcode(int value);
        void setGemeente(const QString &value);
        void setTelefoon(const QString &value);
        void setOpmerkingen(const QString &value);

    private:
        // --- Data members ---
        Universum &m_universum;
    };
}

#endif // _VIEW_ARTS_H
