#ifndef __PRINTLABELDIALOG_H__
#define __PRINTLABELDIALOG_H__

#include <QDialog>
#include "ui_printlabeldialog.h"

class PrintLabelDialogImpl : public QDialog, public Ui::PrintLabelDialog
{
Q_OBJECT
public:
	PrintLabelDialogImpl( QWidget * parent = 0 );
};

#endif // __PRINTLABELDIALOG_H__
