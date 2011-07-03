#ifndef PRESENTER_LETTERCUSTOMER_H
#define PRESENTER_LETTERCUSTOMER_H

#include "presenter_letter.h"

namespace Presenter
{
    class LetterCustomer : public Letter
    {
    Q_OBJECT
    public:
        explicit LetterCustomer(View::Letter &view, Model::Letter &model);
        virtual ~LetterCustomer();

    protected:
        // --- Letter ---
        virtual QString getGreeting() const;
        virtual QString getAddresseeName() const;
        virtual QString getAddresseeStreet() const;
        virtual QString getAddresseeCity() const;
        virtual QString getDefaultText() const;
    };
}

#endif // PRESENTER_LETTERCUSTOMER_H
