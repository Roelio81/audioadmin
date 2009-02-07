#ifndef __BRIEFKLANTDIALOGIMPL_H__
#define __BRIEFKLANTDIALOGIMPL_H__

#include <QDialog>
#include "ui_briefklantdialog.h"

class BriefKlantDialogImpl : public QDialog, public Ui::BriefKlantDialog
{
Q_OBJECT
public:
	BriefKlantDialogImpl( QWidget * parent = 0 );
};

#endif // __BRIEFKLANTDIALOGIMPL_H__
