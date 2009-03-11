#ifndef _VIEW_BRIEFMUTUALITEIT_H
#define _VIEW_BRIEFMUTUALITEIT_H

#include <QDialog>
#include "ui_briefmutualiteit.h"

namespace View
{
    class BriefMutualiteit : public QDialog, public Ui::BriefMutualiteit
    {
    Q_OBJECT
    public:
        BriefMutualiteit(QWidget *parent = 0);
        virtual ~BriefMutualiteit();

        void setAudioloogNaam(const QString &value);
        void setAudioloogStraat(const QString &value);
        void setAudioloogGemeente(const QString &value);
        void setAudioloogTelefoon(const QString &value);
        void setAudioloogGSM(const QString &value);
        void setMutualiteitNaam(const QString &value);
        void setMutualiteitStraat(const QString &value);
        void setMutualiteitGemeente(const QString &value);
        void setPostdatum(const QString &value);
        void setTekst(const QString &value);
        void setBesluit(const QString &value);

    signals:
        void briefMutualiteitSluiten();

    private slots:
        void sluitBriefMutualiteit();
    };
}

#endif // _VIEW_BRIEFMUTUALITEIT_H
