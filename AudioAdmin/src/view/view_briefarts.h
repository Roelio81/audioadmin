#ifndef _VIEW_BRIEFARTS_H
#define _VIEW_BRIEFARTS_H

#include <QDialog>
#include "ui_briefarts.h"

namespace View
{
    class BriefArts : public QDialog, public Ui::BriefArts
    {
    Q_OBJECT
    public:
        BriefArts(QWidget *parent = 0);
        virtual ~BriefArts();

        void setAudioloogNaam(const QString &value);
        void setAudioloogStraat(const QString &value);
        void setAudioloogGemeente(const QString &value);
        void setAudioloogTelefoon(const QString &value);
        void setAudioloogGSM(const QString &value);
        void setArtsNaam(const QString &value);
        void setArtsStraat(const QString &value);
        void setArtsGemeente(const QString &value);
        void setPostdatum(const QString &value);
        void setTekst(const QString &value);
        void setBesluit(const QString &value);

        QString getPostdatum() const;
        QString getTekst() const;
        QString getBesluit() const;

    signals:
        void briefArtsSluiten();
        void briefArtsBewaren();

    private slots:
        void sluitBriefArts();
        void bewaarBriefArts();
    };
}

#endif // _VIEW_BRIEFARTS_H
