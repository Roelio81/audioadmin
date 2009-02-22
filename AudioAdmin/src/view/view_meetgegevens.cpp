#include "view_meetgegevens.h"

using namespace View;

Meetgegevens::Meetgegevens(::QWidget *parent) 
: ::QDialog(parent)
{
	setupUi(this);
        m_tonaleAudiometrieLinks->setKant(TonaleAudiometrieWidget::LINKS);
        m_tonaleAudiometrieRechts->setKant(TonaleAudiometrieWidget::RECHTS);
}

Meetgegevens::~Meetgegevens()
{
}
