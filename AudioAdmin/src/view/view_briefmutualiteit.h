#ifndef _VIEW_BRIEFMUTUALITEIT_H
#define _VIEW_BRIEFMUTUALITEIT_H

#include <QDialog>
#include "ui_briefmutualiteit.h"

namespace View
{
	class BriefMutualiteit : public QDialog, public Ui::BriefMutualiteit
	{
	Q_OBJECT
	public:
		BriefMutualiteit(QWidget *parent = 0);
		virtual ~BriefMutualiteit();
	};
}

#endif // _VIEW_BRIEFMUTUALITEIT_H
