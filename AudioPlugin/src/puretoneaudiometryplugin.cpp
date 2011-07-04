#include "puretoneaudiometryplugin.h"
#include "puretoneaudiometrywidget.h"

#include <QtDesigner>
#include <QtGui>
#include <QtPlugin>

PureToneAudiometryPlugin::PureToneAudiometryPlugin(QObject *parent)
: QObject(parent)
{
        m_initialized = false;
}

QString PureToneAudiometryPlugin::name() const
{
        return "PureToneAudiometryWidget";
}

QString PureToneAudiometryPlugin::group() const
{
	return "AudioAdmin Widgets";
}

QString PureToneAudiometryPlugin::toolTip() const
{
	return "";
}

QString PureToneAudiometryPlugin::whatsThis() const
{
	return "";
}

QString PureToneAudiometryPlugin::includeFile() const
{
        return "../../AudioPlugin/src/puretoneaudiometrywidget.h";
}

QIcon PureToneAudiometryPlugin::icon() const
{
	return QIcon();
}

bool PureToneAudiometryPlugin::isContainer() const
{
	return false;
}

QWidget *PureToneAudiometryPlugin::createWidget(QWidget *parent)
{
        return new PureToneAudiometryWidget(parent);
}

bool PureToneAudiometryPlugin::isInitialized() const
{
        return m_initialized;
}

void PureToneAudiometryPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
        m_initialized = true;
}
