#include "view_etiketten.h"
#include <QList>
#include <QPrinterInfo>

using namespace View;

Etiketten::Etiketten(::QWidget *parent) 
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setupUi(this);
    Q_ASSERT(m_plaats);
    m_plaats->setInsertPolicy(QComboBox::InsertAlphabetically);
    m_plaats->setDuplicatesEnabled(false);

    QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
    for (QList<QPrinterInfo>::const_iterator itPrinter = printers.begin(); itPrinter != printers.end(); ++itPrinter)
    {
        QPrinterInfo printer = *itPrinter;
        m_printer->addItem(printer.printerName());
        if (printer.isDefault())
            m_printer->setCurrentIndex(m_printer->findText(printer.printerName()));
    }
}

Etiketten::~Etiketten()
{
}

void Etiketten::leegPlaatsenAanpassing()
{
    m_plaatsenAanpassing.clear();
    m_plaats->clear();
}

void Etiketten::toevoegenPlaatsAanpassing(const QString &value)
{
    if (! m_plaatsenAanpassing.contains(value, Qt::CaseInsensitive))
    {
        m_plaatsenAanpassing.push_back(value);
        m_plaatsenAanpassing.sort();
        m_plaats->clear();
        for (QStringList::const_iterator itString = m_plaatsenAanpassing.begin(); itString != m_plaatsenAanpassing.end(); ++itString)
            m_plaats->addItem(*itString);
    }
}

void Etiketten::setDatumOnderzoek(const QDate &value)
{
    m_onderzoekNa->setDate(value);
}

void Etiketten::afdrukken()
{
    // Start printing
}
