#include "view_toevoegenmutualiteit.h"

using namespace View;

ToevoegenMutualiteit::ToevoegenMutualiteit(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
}

ToevoegenMutualiteit::~ToevoegenMutualiteit()
{
}

QString ToevoegenMutualiteit::getNaam() const
{
    return m_naam->text();
}

