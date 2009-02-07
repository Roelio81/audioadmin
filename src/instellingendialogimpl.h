#ifndef __INSTELLINGENDIALOGIMPL_H__
#define __INSTELLINGENDIALOGIMPL_H__

#include <QDialog>
#include "ui_instellingendialog.h"

class InstellingenDialogImpl : public QDialog, public Ui::InstellingenDialog
{
Q_OBJECT
public:
	InstellingenDialogImpl( QWidget * parent = 0 );
};

#endif // __INSTELLINGENDIALOGIMPL_H__
