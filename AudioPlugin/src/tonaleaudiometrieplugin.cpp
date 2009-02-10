#include "tonaleaudiometrieplugin.h"
#include "tonaleaudiometriewidget.h"

#include <QtDesigner>
#include <QtGui>
#include <QtPlugin>

TonaleAudiometriePlugin::TonaleAudiometriePlugin(QObject *parent)
: QObject(parent)
{
	initialized = false;
}

QString TonaleAudiometriePlugin::name() const
{
	return "TonaleAudiometrieWidget";
}

QString TonaleAudiometriePlugin::group() const
{
	return "AudioAdmin Widgets";
}

QString TonaleAudiometriePlugin::toolTip() const
{
	return "";
}

QString TonaleAudiometriePlugin::whatsThis() const
{
	return "";
}

QString TonaleAudiometriePlugin::includeFile() const
{
	return "../../AudioPlugin/src/tonaleaudiometriewidget.h";
}

QIcon TonaleAudiometriePlugin::icon() const
{
	return QIcon();
}

bool TonaleAudiometriePlugin::isContainer() const
{
	return false;
}

QWidget *TonaleAudiometriePlugin::createWidget(QWidget *parent)
{
	TonaleAudiometrieWidget *tonaleAudiometrieWidget = new TonaleAudiometrieWidget(parent);
	return tonaleAudiometrieWidget;
}

bool TonaleAudiometriePlugin::isInitialized() const
{
	return initialized;
}

void TonaleAudiometriePlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
	initialized = true;
}
