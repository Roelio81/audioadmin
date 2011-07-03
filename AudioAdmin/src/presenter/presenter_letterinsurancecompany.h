#ifndef _PRESENTER_LETTERINSURANCECOMPANY_H
#define _PRESENTER_LETTERINSURANCECOMPANY_H

#include "presenter_letter.h"

namespace Presenter
{
    class LetterInsuranceCompany : public Letter
    {
    Q_OBJECT
    public:
        explicit LetterInsuranceCompany(View::Letter &view, Model::Letter &model);
        virtual ~LetterInsuranceCompany();

    protected:
        // --- Letter ---
        virtual QString getGreeting() const;
        virtual QString getAddresseeName() const;
        virtual QString getAddresseeStreet() const;
        virtual QString getAddresseeCity() const;
        virtual QString getDefaultText() const;
    };
}

#endif // _PRESENTER_LETTERINSURANCECOMPANY_H
