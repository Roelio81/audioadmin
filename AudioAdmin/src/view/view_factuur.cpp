#include "view_factuur.h"

using namespace View;

Factuur::Factuur(QWidget *parent) 
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitFactuur()));
}

Factuur::~Factuur()
{
}

void Factuur::sluitFactuur()
{
    emit factuurSluiten();
}
