#include "audioplugins.h"
#include "puretoneaudiometryplugin.h"
#include "speechaudiometryplugin.h"

AudioPlugins::AudioPlugins(QObject *parent)
: QObject(parent)
{
        m_plugins.append(new SpeechAudiometryPlugin(this));
        m_plugins.append(new PureToneAudiometryPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> AudioPlugins::customWidgets() const
{
	return m_plugins;
}

Q_EXPORT_PLUGIN2(audioplugins, AudioPlugins)
