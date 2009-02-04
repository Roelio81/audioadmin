#include "printlabeldialogimpl.h"

PrintLabelDialogImpl::PrintLabelDialogImpl( QWidget * parent) 
	: QDialog(parent)
{
	setupUi(this);
	setModal(true);
}
