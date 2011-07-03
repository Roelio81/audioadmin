#ifndef VIEW_CUSTOMER_H
#define VIEW_CUSTOMER_H

class QDate;
class QString;

namespace Ui
{
    class Universe;
}

namespace View
{
    class File;

    class Customer
    {
    public:
        explicit Customer(File &file);
        virtual ~Customer();

        void clearTitles();
        void addTitle(const QString &value);

        // --- Getters ---
        QString getTitle() const;
        QString getName() const;
        QString getFirstName() const;
        QString getStreet() const;
        int getPostalCode() const;
        QString getCity() const;
        QString getTelephone() const;
        QDate getDateOfBirth() const;
        QString getComments() const;

        // --- Setters ---
        void setTitle(const QString &value);
        void setName(const QString &value);
        void setFirstName(const QString &value);
        void setStreet(const QString &value);
        void setPostalCode(int value);
        void setCity(const QString &value);
        void setTelephone(const QString &value);
        void setDateOfBirth(const QDate &value);
        void setComments(const QString &value);

    private:
        Ui::Universe &m_ui;
    };

}

#endif // VIEW_CUSTOMER_H
