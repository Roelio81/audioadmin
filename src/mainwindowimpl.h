#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
public slots:
	void showMeetgegevens();
private slots:
	void printLabels();
	void backup();
	void restore();
	void settings();
	void about();
signals:
	void backupSignal(QString bestandsNaam);
	void restoreSignal(QString bestandsNaam);
	void showMeetgegevensSignal();
};
#endif
