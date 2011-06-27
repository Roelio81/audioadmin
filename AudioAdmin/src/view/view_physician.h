#ifndef _VIEW_ARTS_H
#define _VIEW_ARTS_H

#include <QObject>
#include <QDate>

namespace Ui
{
    class Universe;
}

namespace View
{
    class Physician : QObject
    {
    Q_OBJECT
    public:
        explicit Physician(Ui::Universe &universum);
        virtual ~Physician();

        // --- Getters ---
        QString getName() const;
        QString getFirstName() const;
        QString getStreet() const;
        int getPostalCode() const;
        QString getCity() const;
        QString getTelephone() const;
        QString getComments() const;

        // --- Setters ---
        void setName(const QString &value);
        void setFirstName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(int value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setComments(const QString &value);

    private:
        // --- Data members ---
        Ui::Universe &m_universe;
    };
}

#endif // _VIEW_ARTS_H
