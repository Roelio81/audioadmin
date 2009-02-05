#include "etikettendialogimpl.h"

EtikettenDialogImpl::EtikettenDialogImpl( QWidget * parent) 
	: QDialog(parent)
{
	setupUi(this);
	setModal(true);
}
