#ifndef _VIEW_MEETGEGEVENS_H
#define _VIEW_MEETGEGEVENS_H

#include <QDialog>
#include "../ui_meetgegevensdialog.h"

namespace View
{
	class Meetgegevens : public ::QDialog, public Ui::MeetgegevensDialog
	{
	Q_OBJECT
	public:
		Meetgegevens(QWidget *parent = 0);
		virtual ~Meetgegevens();
	};
}

#endif // _VIEW_MEETGEGEVENS_H
