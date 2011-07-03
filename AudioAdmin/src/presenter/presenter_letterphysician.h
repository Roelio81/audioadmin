#ifndef PRESENTER_LETTERPHYSICIAN_H
#define PRESENTER_LETTERPHYSICIAN_H

#include "presenter_letter.h"

namespace Presenter
{
    class LetterPhysician : public Letter
    {
    Q_OBJECT
    public:
        explicit LetterPhysician(View::Letter &view, Model::Letter &model);
        virtual ~LetterPhysician();

    protected:
        // --- Letter ---
        virtual QString getGreeting() const;
        virtual QString getAddresseeName() const;
        virtual QString getAddresseeStreet() const;
        virtual QString getAddresseeCity() const;
        virtual QString getDefaultText() const;

    };
}

#endif // PRESENTER_LETTERPHYSICIAN_H
