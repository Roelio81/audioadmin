#include "view_instellingen.h"
#include <QLineEdit>

using namespace View;

Instellingen::Instellingen(::QWidget *parent) 
: ::QDialog(parent)
{
	setupUi(this);
}

Instellingen::~Instellingen()
{
}

void Instellingen::setNaam(const QString &naam)
{
	m_naam->setText(naam);
}

QString Instellingen::getNaam() const
{
	return m_naam->text();
}
