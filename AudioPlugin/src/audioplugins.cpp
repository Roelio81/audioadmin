#include "audioplugins.h"
#include "tonaleaudiometrieplugin.h"
#include "vocaleaudiometrieplugin.h"

AudioPlugins::AudioPlugins(QObject *parent)
: QObject(parent)
{
	m_plugins.append(new VocaleAudiometriePlugin(this));
	m_plugins.append(new TonaleAudiometriePlugin(this));
}

QList<QDesignerCustomWidgetInterface*> AudioPlugins::customWidgets() const
{
	return m_plugins;
}

Q_EXPORT_PLUGIN2(audioplugins, AudioPlugins)
