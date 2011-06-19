#include "presenter_meetgegevens.h"
#include "../model/model_meetgegevens.h"
#include "../view/view_meetgegevens.h"

using namespace Presenter;

Meetgegevens::Meetgegevens(View::Meetgegevens &view, Model::Meetgegevens &model)
    : m_view(view)
    , m_model(model)
{
}

Meetgegevens::~Meetgegevens()
{
}

void Meetgegevens::setup()
{
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        m_view.setLGRechtsData(Hz[i], m_model.getLGRechtsData(Hz[i]));
        m_view.setBGRechtsData(Hz[i], m_model.getBGRechtsData(Hz[i]));
        m_view.setUCLRechtsData(Hz[i], m_model.getUCLRechtsData(Hz[i]));
        m_view.setLGLinksData(Hz[i], m_model.getLGLinksData(Hz[i]));
        m_view.setBGLinksData(Hz[i], m_model.getBGLinksData(Hz[i]));
        m_view.setUCLLinksData(Hz[i], m_model.getUCLLinksData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        m_view.setROZonderData(5*i, m_model.getROZonderData(5*i));
        m_view.setLOZonderData(5*i, m_model.getLOZonderData(5*i));
        m_view.setROLOZonderData(5*i, m_model.getROLOZonderData(5*i));
        m_view.setROMetData(5*i, m_model.getROMetData(5*i));
        m_view.setLOMetData(5*i, m_model.getLOMetData(5*i));
        m_view.setROLOMetData(5*i, m_model.getROLOMetData(5*i));
    }
    m_view.setLocalisatieZonder(m_model.getLocalisatieZonder());
    m_view.setLocalisatieRechts(m_model.getLocalisatieRechts());
    m_view.setLocalisatieLinks(m_model.getLocalisatieLinks());
    m_view.setLocalisatieBeide(m_model.getLocalisatieBeide());

    connect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    connect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
}

void Meetgegevens::teardown()
{
    int Hz[] = { 125, 250, 500, 750, 1000, 1500, 2000, 3000, 4000, 6000, 8000 };
    for (int i = 0; i < 11; ++i)
    {
        m_model.setLGRechtsData(Hz[i], m_view.getLGRechtsData(Hz[i]));
        m_model.setBGRechtsData(Hz[i], m_view.getBGRechtsData(Hz[i]));
        m_model.setUCLRechtsData(Hz[i], m_view.getUCLRechtsData(Hz[i]));
        m_model.setLGLinksData(Hz[i], m_view.getLGLinksData(Hz[i]));
        m_model.setBGLinksData(Hz[i], m_view.getBGLinksData(Hz[i]));
        m_model.setUCLLinksData(Hz[i], m_view.getUCLLinksData(Hz[i]));
    }
    for (int i = 0; i < 23; ++i)
    {
        m_model.setROZonderData(5*i, m_view.getROZonderData(5*i));
        m_model.setLOZonderData(5*i, m_view.getLOZonderData(5*i));
        m_model.setROLOZonderData(5*i, m_view.getROLOZonderData(5*i));
        m_model.setROMetData(5*i, m_view.getROMetData(5*i));
        m_model.setLOMetData(5*i, m_view.getLOMetData(5*i));
        m_model.setROLOMetData(5*i, m_view.getROLOMetData(5*i));
    }
    m_model.setLocalisatieZonder(m_view.getLocalisatieZonder());
    m_model.setLocalisatieRechts(m_view.getLocalisatieRechts());
    m_model.setLocalisatieLinks(m_view.getLocalisatieLinks());
    m_model.setLocalisatieBeide(m_view.getLocalisatieBeide());

    disconnect(m_view.b_ok, SIGNAL(clicked()), &m_view, SLOT(accept()));
    disconnect(m_view.b_annuleren, SIGNAL(clicked()), &m_view, SLOT(reject()));
}
