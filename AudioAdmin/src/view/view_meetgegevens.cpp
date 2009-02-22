#include "view_meetgegevens.h"

using namespace View;

Meetgegevens::Meetgegevens(::QWidget *parent) 
: ::QDialog(parent)
{
	setupUi(this);
        m_tonaleAudiometrieLinks->setColor(Qt::blue);
        m_tonaleAudiometrieRechts->setColor(Qt::red);
}

Meetgegevens::~Meetgegevens()
{
}
