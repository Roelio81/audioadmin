#ifndef _VIEW_FACTUUR_H
#define _VIEW_FACTUUR_H

#include <QDialog>
#include "ui_factuur.h"

namespace View
{
	class Factuur : public QDialog, public Ui::Factuur
	{
	Q_OBJECT
	public:
		Factuur(QWidget *parent = 0);
		virtual ~Factuur();
	};
}

#endif // _VIEW_FACTUUR_H
