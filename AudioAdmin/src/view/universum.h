#ifndef _VIEW_UNIVERSUM_H
#define _VIEW_UNIVERSUM_H

#include <QMainWindow>
#include "../ui_mainwindow.h"

namespace View
{
	class Universum : public QMainWindow, public Ui::MainWindow
	{
	Q_OBJECT
	public:
		Universum(::QWidget *parent = 0, Qt::WFlags f = 0);
		virtual ~Universum();
	public slots:
		void toonMeetgegevens();
	private slots:
		void printLabels();
		void backup();
		void restore();
		void instellingen();
		void omtrent();
	signals:
		void backupSignal(::QString bestandsNaam);
		void restoreSignal(::QString bestandsNaam);
		void toonMeetgegevensSignal();
	};
}

#endif // _VIEW_UNIVERSUM_H
