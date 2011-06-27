#ifndef _VIEW_INSURANCECOMPANY_H
#define _VIEW_INSURANCECOMPANY_H

#include <QObject>
#include <QDate>

namespace Ui
{
    class Universe;
}

namespace View
{

    class InsuranceCompany : QObject
    {
    Q_OBJECT
    public:
        explicit InsuranceCompany(Ui::Universe &universum);
        virtual ~InsuranceCompany();

        // --- Getters ---
        QString getName() const;
        QString getStreet() const;
        int getPostalCode() const;
        QString getCity() const;
        QString getTelephone() const;
        QString getComments() const;

        // --- Setters ---
        void setName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(int value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setComments(const QString &value);

    private:
        // --- Data members ---
        Ui::Universe &m_universum;
    };
}

#endif // _VIEW_INSURANCECOMPANY_H
