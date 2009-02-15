#ifndef _VIEW_BRIEFARTS_H
#define _VIEW_BRIEFARTS_H

#include <QDialog>
#include "ui_briefarts.h"

namespace View
{
	class BriefArts : public QDialog, public Ui::BriefArts
	{
	Q_OBJECT
	public:
		BriefArts(QWidget *parent = 0);
		virtual ~BriefArts();
	};
}

#endif // _VIEW_BRIEFARTS_H
