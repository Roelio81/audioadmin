#ifndef _VIEW_UNIVERSUM_H
#define _VIEW_UNIVERSUM_H

#include "ui_universum.h"
#include "view_arts.h"
#include "view_dossier.h"
#include "view_mutualiteit.h"
#include "view_etiketten.h"
#include "view_instellingen.h"
#include <QMainWindow>
#include <QMap>
#include <QSet>

namespace View
{
    class Universum : public QMainWindow, public Ui::Universum
    {
    Q_OBJECT
    public:
        explicit Universum(QWidget *parent = 0, Qt::WFlags f = 0);
        virtual ~Universum();

        Arts &getArts();
        Dossier &getDossier();
        Mutualiteit &getMutualiteit();
        Etiketten &getEtiketten();
        Instellingen &getInstellingen();

        void bewarenBijAfsluiten();
        void markeerArtsenLijstStatus(bool wijzigingen);
        void leegArtsenLijst();
        void toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void leegHoorapparatenLijst();
        void toevoegenHoorapparaat(const QString &merk, const QString &type, double prijs, const QDate &datumPrijs);
        void markeerKlantenLijstStatus(bool wijzigingen);
        void leegKlantenLijst();
        void toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void markeerMutualiteitenLijstStatus(bool wijzigingen);
        void leegMutualiteitenLijst();
        void toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
        void wijzigenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);

        int artsIndexToId(int index) const;
        int artsIdToIndex(int id) const;
        int klantIndexToId(int index) const;
        int klantIdToIndex(int id) const;
        int mutualiteitIndexToId(int index) const;
        int mutualiteitIdToIndex(int id) const;

        QSet<QString> getMerkHoorapparaten() const;
        QSet<QString> getTypeHoorapparaten(const QString &merk) const;

        void selecteerArts(int id);
        void selecteerKlant(int id);
        void selecteerMutualiteit(int id);

    private slots:
        void tabVeranderd(int nieuweTab);
        void instellingen();
        void bewaren();
        void etikettenAfdrukken();
        void omtrent();
        void selecteerArts(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selecteerKlant(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void selecteerMutualiteit(int currentRow, int currentColumn, int previousRow, int previousColumn);
        void toevoegenArts();
        void verwijderenArts();
        void zoekenArts();
        void toevoegenDossier();
        void verwijderenDossier();
        void zoekenDossier();
        void toevoegenMutualiteit();
        void verwijderenMutualiteit();
        void zoekenMutualiteit();

    signals:
        void afsluitenSignal();
        void bewarenSignal();
        void instellingenSignal();
        void artsSelectieSignal(int id);
        void artsVerwijderenSignal(int id);
        void artsToevoegenSignal(QString voornaam, QString naam);
        void klantSelectieSignal(int id);
        void klantVerwijderenSignal(int id);
        void klantToevoegenSignal(QString voornaam, QString naam);
        void mutualiteitSelectieSignal(int id);
        void mutualiteitVerwijderenSignal(int id);
        void mutualiteitToevoegenSignal(QString naam);
        void etikettenSignal();
        void sluitDossierTab();
        void sluitArtsTab();
        void sluitMutualiteitTab();
        void openDossierTab();
        void openArtsTab();
        void openMutualiteitTab();

    private:
        void closeEvent(QCloseEvent *event);

        // --- Type definitions ---
        typedef QPair<double, QDate> PrijsDatumInfo;
        typedef QMap<QString, PrijsDatumInfo> HaarApparaatTypeMap;
        typedef QMap<QString, HaarApparaatTypeMap> HoorApparaatMap;

        // --- Data members ---
        HoorApparaatMap m_hoorapparaatMerkToTypes;
        Arts m_arts;
        Dossier m_dossier;
        Mutualiteit m_mutualiteit;
        Etiketten m_etiketten;
        Instellingen m_instellingen;
        int m_huidigeTab;
    };
}

#endif // _VIEW_UNIVERSUM_H
