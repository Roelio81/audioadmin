#include "presenter_measurements.h"
#include "../model/model_measurements.h"
#include "../view/view_measurements.h"

using namespace Presenter;

Measurements::Measurements(View::Measurements &view, Model::Measurements &model)
    : m_view(view)
    , m_model(model)
{
}

Measurements::~Measurements()
{
}

void Measurements::setup()
{
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        m_view.setACRightData(Hz[i], m_model.getACRightData(Hz[i]));
        m_view.setBCRightData(Hz[i], m_model.getBCRightData(Hz[i]));
        m_view.setUCLRightData(Hz[i], m_model.getUCLRightData(Hz[i]));
        m_view.setACLeftData(Hz[i], m_model.getACLeftData(Hz[i]));
        m_view.setBCLeftData(Hz[i], m_model.getBCLeftData(Hz[i]));
        m_view.setUCLLeftData(Hz[i], m_model.getUCLLeftData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        m_view.setREWithoutData(5*i, m_model.getREWithoutData(5*i));
        m_view.setLEWithoutData(5*i, m_model.getLEWithoutData(5*i));
        m_view.setRELEWithoutData(5*i, m_model.getRELEWithoutData(5*i));
        m_view.setROWithData(5*i, m_model.getREWithData(5*i));
        m_view.setLOWithData(5*i, m_model.getLEWithData(5*i));
        m_view.setROLOWithData(5*i, m_model.getRELEWithData(5*i));
    }
    m_view.setLocalizationWithout(m_model.getLocalizationWithout());
    m_view.setLocalizationWithRight(m_model.getLocalizationRight());
    m_view.setLocalizationWithLeft(m_model.getLocalizationLeft());
    m_view.setLocalizationWithBoth(m_model.getLocalizationBoth());
}

void Measurements::teardown()
{
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        m_model.setACRightData(Hz[i], m_view.getACRightData(Hz[i]));
        m_model.setBCRightData(Hz[i], m_view.getBCRightData(Hz[i]));
        m_model.setUCLRightData(Hz[i], m_view.getUCLRightData(Hz[i]));
        m_model.setACLeftData(Hz[i], m_view.getACLeftData(Hz[i]));
        m_model.setBCLeftData(Hz[i], m_view.getBCLeftData(Hz[i]));
        m_model.setUCLLeftData(Hz[i], m_view.getUCLLeftData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        m_model.setREWithoutData(5*i, m_view.getREWithoutData(5*i));
        m_model.setLEWithoutData(5*i, m_view.getLEWithoutData(5*i));
        m_model.setRELEWithoutData(5*i, m_view.getRELEWithoutData(5*i));
        m_model.setREWithData(5*i, m_view.getREWithData(5*i));
        m_model.setLEWithData(5*i, m_view.getLEWithData(5*i));
        m_model.setRELEWithData(5*i, m_view.getRELEWithData(5*i));
    }
    m_model.setLocalizationWithout(m_view.getLocalizationWithout());
    m_model.setLocalizationRight(m_view.getLocalizationRight());
    m_model.setLocalizationLeft(m_view.getLocalizationLeft());
    m_model.setLocalizationBoth(m_view.getLocalizationBoth());
}
