#ifndef _VIEW_BRIEFARTS_H
#define _VIEW_BRIEFARTS_H

#include <QDialog>
#include "ui_briefartsdialog.h"

namespace View
{
	class BriefArts : public ::QDialog, public Ui::BriefArtsDialog
	{
	Q_OBJECT
	public:
		BriefArts(QWidget *parent = 0);
		virtual ~BriefArts();
	};
}

#endif // _VIEW_BRIEFARTS_H
