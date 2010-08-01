#include "view_toevoegenarts.h"

using namespace View;

ToevoegenArts::ToevoegenArts(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
}

ToevoegenArts::~ToevoegenArts()
{
}

QString ToevoegenArts::getVoornaam() const
{
    return m_voornaam->text();
}

QString ToevoegenArts::getNaam() const
{
    return m_naam->text();
}
