#include "speechaudiometryplugin.h"
#include "speechaudiometrywidget.h"

#include <QtDesigner>
#include <QtGui>
#include <QtPlugin>

SpeechAudiometryPlugin::SpeechAudiometryPlugin(QObject *parent)
: QObject(parent)
{
	m_initialized = false;
}

QString SpeechAudiometryPlugin::name() const
{
        return "SpeechAudiometryWidget";
}

QString SpeechAudiometryPlugin::group() const
{
	return "AudioAdmin Widgets";
}

QString SpeechAudiometryPlugin::toolTip() const
{
	return "";
}

QString SpeechAudiometryPlugin::whatsThis() const
{
	return "";
}

QString SpeechAudiometryPlugin::includeFile() const
{
        return "../../AudioPlugin/src/speechaudiometrywidget.h";
}

QIcon SpeechAudiometryPlugin::icon() const
{
	return QIcon();
}

bool SpeechAudiometryPlugin::isContainer() const
{
	return false;
}

QWidget *SpeechAudiometryPlugin::createWidget(QWidget *parent)
{
        return new SpeechAudiometryWidget(parent);
}

bool SpeechAudiometryPlugin::isInitialized() const
{
	return m_initialized;
}

void SpeechAudiometryPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
	m_initialized = true;
}
