#include "view_toevoegenklant.h"

using namespace View;

ToevoegenKlant::ToevoegenKlant(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
}

ToevoegenKlant::~ToevoegenKlant()
{
}

QString ToevoegenKlant::getVoornaam() const
{
    return m_voornaam->text();
}

QString ToevoegenKlant::getNaam() const
{
    return m_naam->text();
}
