#ifndef _VIEW_ETIKETTEN_H
#define _VIEW_ETIKETTEN_H

#include <QDialog>
#include "../ui_etikettendialog.h"

namespace View
{
	class Etiketten : public ::QDialog, public Ui::EtikettenDialog
	{
	Q_OBJECT
	public:
		Etiketten(QWidget *parent = 0);
		virtual ~Etiketten();
	};
}

#endif // _VIEW_ETIKETTEN_H
