#include "view_letter.h"

using namespace View;

Letter::Letter(bool showConclusion, QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
    connect(m_ui.b_print, SIGNAL(clicked()), this, SIGNAL(print()));
    connect(m_ui.buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_ui.buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
    if (!showConclusion)
    {
        m_ui.l_conclusion->setVisible(false);
        m_ui.m_conclusion->setVisible(false);
    }
}

Letter::~Letter()
{
}

void Letter::setSenderName(const QString &value)
{
    m_ui.l_senderName->setText(value);
    m_ui.l_senderName_2->setText(value);
}

void Letter::setSenderStreet(const QString &value)
{
    m_ui.l_senderStreet->setText(value);
}

void Letter::setSenderCity(const QString &value)
{
    m_ui.l_senderCity->setText(value);
}

void Letter::setSenderTelephone(const QString &value)
{
    m_ui.l_senderTelephone->setText(value);
}

void Letter::setSenderMobilePhone(const QString &value)
{
    m_ui.l_senderMobile->setText(value);
}

void Letter::setAddresseeName(const QString &value)
{
    m_ui.l_addresseeName->setText(value);
}

void Letter::setAddresseeStreet(const QString &value)
{
    m_ui.l_addresseeStreet->setText(value);
}

void Letter::setAddresseeCity(const QString &value)
{
    m_ui.l_addresseeCity->setText(value);
}

void Letter::setPostalDate(const QString &value)
{
    m_ui.m_postalDate->setText(value);
}

void Letter::setGreeting(const QString &value)
{
    m_ui.l_greeting->setText(value);
}

void Letter::setText(const QString &value)
{
    m_ui.m_text->setPlainText(value);
}

void Letter::setConclusion(const QString &value)
{
    m_ui.m_conclusion->setPlainText(value);
}

QString Letter::getPostalDate() const
{
    return m_ui.m_postalDate->text();
}

QString Letter::getText() const
{
    return m_ui.m_text->toPlainText();
}

QString Letter::getConclusion() const
{
    return m_ui.m_conclusion->toPlainText();
}
