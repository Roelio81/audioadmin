#ifndef _VIEW_UNIVERSUM_H
#define _VIEW_UNIVERSUM_H

#include <QMainWindow>
#include "ui_universum.h"
#include "view_instellingen.h"

namespace View
{
	class Universum : public ::QMainWindow, public Ui::Universum
	{
	Q_OBJECT
	public:
		Universum(::QWidget *parent = 0, Qt::WFlags f = 0);
		virtual ~Universum();
		
		Instellingen &getInstellingen();

		void leegArtsenLijst();
		void toevoegenArts(const QString &naam, const QString &Straat, int postcode, const QString &gemeente);
		void leegKlantenLijst();
		void toevoegenKlant(const QString &naam, const QString &Straat, int postcode, const QString &gemeente);
		void leegMutualiteitenLijst();
		void toevoegenMutualiteit(const QString &naam, const QString &Straat, int postcode, const QString &gemeente);

	public slots:
		void instellingen();
		void meetgegevens();

	private slots:
		void printLabels();
		void backup();
		void restore();
		void omtrent();

	signals:
		void backupSignal(const QString &bestandsNaam);
		void restoreSignal(const QString &bestandsNaam);
		void instellingenSignal();
		void meetgegevensSignal();

	private:
		Instellingen m_instellingen;
	};
}

#endif // _VIEW_UNIVERSUM_H
