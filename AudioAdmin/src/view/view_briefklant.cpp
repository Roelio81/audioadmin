#include "view_briefklant.h"

using namespace View;

BriefKlant::BriefKlant(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefKlant()));
}

BriefKlant::~BriefKlant()
{
}

void BriefKlant::sluitBriefKlant()
{
    emit briefKlantSluiten();
}
