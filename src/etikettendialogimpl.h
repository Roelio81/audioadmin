#ifndef __ETIKETTENDIALOG_H__
#define __ETIKETTENDIALOG_H__

#include <QDialog>
#include "ui_etikettendialog.h"

class EtikettenDialogImpl : public QDialog, public Ui::EtikettenDialog
{
Q_OBJECT
public:
	EtikettenDialogImpl( QWidget * parent = 0 );
};

#endif // __ETIKETTENDIALOG_H__
