#ifndef __BRIEFMUTUALITEITDIALOGIMPL_H__
#define __BRIEFMUTUALITEITDIALOGIMPL_H__

#include <QDialog>
#include "ui_briefmutualiteitdialog.h"

class BriefMutualiteitDialogImpl : public QDialog, public Ui::BriefMutualiteitDialog
{
Q_OBJECT
public:
	BriefMutualiteitDialogImpl( QWidget * parent = 0 );
};

#endif // __BRIEFMUTUALITEITDIALOGIMPL_H__
