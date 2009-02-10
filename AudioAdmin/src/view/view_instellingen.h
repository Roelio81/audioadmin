#ifndef _VIEW_INSTELLINGEN_H
#define _VIEW_INSTELLINGEN_H

#include <QDialog>
#include <QString>
#include "ui_instellingendialog.h"

namespace View
{
	class Instellingen : public QDialog, public Ui::InstellingenDialog
	{
	Q_OBJECT
	public:
		Instellingen(QWidget *parent = 0);
		virtual ~Instellingen();
		
		void setNaam(const QString &naam);
		QString getNaam() const;
	};
}

#endif // _VIEW_INSTELLINGEN_H
