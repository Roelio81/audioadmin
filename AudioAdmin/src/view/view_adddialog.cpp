#include "view_adddialog.h"

using namespace View;

AddDialog::AddDialog(bool showFirstName, QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
    if (!showFirstName)
    {
        m_ui.m_firstName->setVisible(false);
        m_ui.l_firstName->setVisible(false);
    }
}

AddDialog::~AddDialog()
{
}

QString AddDialog::getFirstName() const
{
    return m_ui.m_firstName->text();
}

QString AddDialog::getName() const
{
    return m_ui.m_name->text();
}
