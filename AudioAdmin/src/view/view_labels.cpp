#include "view_labels.h"

#include <QList>
#include <QPrinterInfo>

using namespace View;

Labels::Labels(QWidget *parent)
: QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    m_ui.setupUi(this);
    Q_ASSERT(m_ui.m_placeAdjustment);
    m_ui.m_placeAdjustment->setInsertPolicy(QComboBox::InsertAlphabetically);
    m_ui.m_placeAdjustment->setDuplicatesEnabled(false);
}

Labels::~Labels()
{
}

void Labels::clearPlacesAdjustment()
{
    m_placesAdjustment.clear();
    m_ui.m_placeAdjustment->clear();
}

void Labels::addPlaceAdjustment(const QString &value)
{
    if (! m_placesAdjustment.contains(value, Qt::CaseInsensitive))
    {
        m_placesAdjustment.push_back(value);
        m_placesAdjustment.sort();
        m_ui.m_placeAdjustment->clear();
        for (QStringList::const_iterator itString = m_placesAdjustment.begin(); itString != m_placesAdjustment.end(); ++itString)
            m_ui.m_placeAdjustment->addItem(*itString);
    }
}

void Labels::setTestDate(const QDate &value)
{
    m_ui.m_testsAfter->setDate(value);
}

void Labels::print()
{
    // Start printing
}
