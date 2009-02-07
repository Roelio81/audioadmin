#ifndef __ABOUTDIALOGIMPL_H__
#define __ABOUTDIALOGIMPL_H__

#include <QDialog>
#include "ui_aboutdialog.h"

class AboutDialogImpl : public QDialog, public Ui::AboutDialog
{
Q_OBJECT
public:
	AboutDialogImpl( QWidget * parent = 0 );
};

#endif // __ABOUTDIALOGIMPL_H__
