#ifndef __ETIKETTENDIALOGIMPL_H__
#define __ETIKETTENDIALOGIMPL_H__

#include <QDialog>
#include "ui_etikettendialog.h"

class EtikettenDialogImpl : public QDialog, public Ui::EtikettenDialog
{
Q_OBJECT
public:
	EtikettenDialogImpl( QWidget * parent = 0 );
};

#endif // __ETIKETTENDIALOGIMPL_H__
