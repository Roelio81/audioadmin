#ifndef _PRESENTER_ARTS_H
#define _PRESENTER_ARTS_H

#include <QObject>

namespace View
{
    class Arts;
}

namespace Model
{
    class Arts;
}

namespace Presenter
{
    class Arts : public QObject
    {
    public:
        Arts(View::Arts &view, Model::Arts &model);
        virtual ~Arts();

    void setup();

    private:
        View::Arts &m_view;
        Model::Arts &m_model;
    };
}

#endif // _PRESENTER_ARTS_H
