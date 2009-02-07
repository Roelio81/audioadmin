#ifndef __MEETGEGEVENSDIALOGIMPL_H__
#define __MEETGEGEVENSDIALOGIMPL_H__

#include <QDialog>
#include "ui_meetgegevensdialog.h"

class MeetgegevensDialogImpl : public QDialog, public Ui::MeetgegevensDialog
{
Q_OBJECT
public:
	MeetgegevensDialogImpl( QWidget * parent = 0 );
};

#endif // __MEETGEGEVENSDIALOGIMPL_H__
