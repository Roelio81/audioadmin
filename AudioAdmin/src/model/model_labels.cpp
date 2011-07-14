#include "model_labels.h"

using namespace Model;

Labels::Labels(const Universe &universe)
    : m_universe(universe)
    , m_placeAdjustment("")
    , m_testDate(QDate::currentDate().addYears(-2))
{
}

Labels::~Labels()
{
}
