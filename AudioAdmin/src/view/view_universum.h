#ifndef _VIEW_UNIVERSUM_H
#define _VIEW_UNIVERSUM_H

#include <QMainWindow>
#include "ui_universum.h"
#include "view_arts.h"
#include "view_dossier.h"
#include "view_mutualiteit.h"
#include "view_instellingen.h"

namespace View
{
	class Universum : public ::QMainWindow, public Ui::Universum
	{
	Q_OBJECT
	public:
		Universum(::QWidget *parent = 0, Qt::WFlags f = 0);
		virtual ~Universum();

		Arts &getArts();
		Dossier &getDossier();
		Mutualiteit &getMutualiteit();
		Instellingen &getInstellingen();

		void leegArtsenLijst();
		void toevoegenArts(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
		void leegKlantenLijst();
		void toevoegenKlant(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);
		void leegMutualiteitenLijst();
		void toevoegenMutualiteit(int id, const QString &naam, const QString &straat, int postcode, const QString &gemeente);

		int artsIndexToId(int index) const;
		int artsIdToIndex(int id) const;
		int mutualiteitIndexToId(int index) const;
		int mutualiteitIdToIndex(int id) const;

	private slots:
		void instellingen();
		void meetgegevens();
		void printLabels();
		void backup();
		void restore();
		void omtrent();
		void selecteerArts(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void selecteerKlant(int currentRow, int currentColumn, int previousRow, int previousColumn);
		void selecteerMutualiteit(int currentRow, int currentColumn, int previousRow, int previousColumn);

	signals:
		void backupSignal(const QString &bestandsNaam);
		void restoreSignal(const QString &bestandsNaam);
		void instellingenSignal();
		void meetgegevensSignal();
		void artsSelectieSignal(int id);
		void klantSelectieSignal(int id);
		void mutualiteitSelectieSignal(int id);

	private:
		QMap<int, int> m_artsIdToIndex;
		QMap<int, int> m_artsIndexToId;
		QMap<int, int> m_klantIdToIndex;
		QMap<int, int> m_klantIndexToId;
		QMap<int, int> m_mutualiteitIdToIndex;
		QMap<int, int> m_mutualiteitIndexToId;

		Arts m_arts;
		Dossier m_dossier;
		Mutualiteit m_mutualiteit;
		Instellingen m_instellingen;
	};
}

#endif // _VIEW_UNIVERSUM_H
