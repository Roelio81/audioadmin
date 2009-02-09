#ifndef _VIEW_BRIEFMUTUALITEIT_H
#define _VIEW_BRIEFMUTUALITEIT_H

#include <QDialog>
#include "../ui_briefmutualiteitdialog.h"

namespace View
{
	class BriefMutualiteit : public ::QDialog, public Ui::BriefMutualiteitDialog
	{
	Q_OBJECT
	public:
		BriefMutualiteit(QWidget *parent = 0);
		virtual ~BriefMutualiteit();
	};
}

#endif // _VIEW_BRIEFMUTUALITEIT_H
