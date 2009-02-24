#include "view_briefarts.h"

using namespace View;

BriefArts::BriefArts(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefArts()));
}

BriefArts::~BriefArts()
{
}

void BriefArts::sluitBriefArts()
{
    emit briefArtsSluiten();
}
