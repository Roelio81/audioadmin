#include "view_briefmutualiteit.h"

using namespace View;

BriefMutualiteit::BriefMutualiteit(QWidget *parent) 
: QDialog(parent)
{
    setupUi(this);
    connect(b_sluiten, SIGNAL(clicked()), this, SLOT(sluitBriefMutualiteit()));
}

BriefMutualiteit::~BriefMutualiteit()
{
}

void BriefMutualiteit::sluitBriefMutualiteit()
{
    emit briefMutualiteitSluiten();
}
