#include "instellingendialogimpl.h"

InstellingenDialogImpl::InstellingenDialogImpl( QWidget * parent) 
	: QDialog(parent)
{
	setupUi(this);
	setModal(true);
}
