#ifndef __BRIEFARTSDIALOGIMPL_H__
#define __BRIEFARTSDIALOGIMPL_H__

#include <QDialog>
#include "ui_briefartsdialog.h"

class BriefArtsDialogImpl : public QDialog, public Ui::BriefArtsDialog
{
Q_OBJECT
public:
	BriefArtsDialogImpl( QWidget * parent = 0 );
};

#endif // __BRIEFARTSDIALOGIMPL_H__
