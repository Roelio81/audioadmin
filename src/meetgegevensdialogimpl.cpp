#include "meetgegevensdialogimpl.h"

MeetgegevensDialogImpl::MeetgegevensDialogImpl( QWidget * parent) 
	: QDialog(parent)
{
	setupUi(this);
	setModal(true);
}
