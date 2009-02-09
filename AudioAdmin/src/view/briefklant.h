#ifndef _VIEW_BRIEFKLANT_H
#define _VIEW_BRIEFKLANT_H

#include <QDialog>
#include "../ui_briefklantdialog.h"

namespace View
{
	class BriefKlant : public ::QDialog, public Ui::BriefKlantDialog
	{
	Q_OBJECT
	public:
		BriefKlant(QWidget *parent = 0);
		virtual ~BriefKlant();
	};
}

#endif // _VIEW_BRIEFKLANT_H
