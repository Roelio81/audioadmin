#include "vocaleaudiometrieplugin.h"
#include "vocaleaudiometriewidget.h"

#include <QtDesigner>
#include <QtGui>
#include <QtPlugin>

VocaleAudiometriePlugin::VocaleAudiometriePlugin(QObject *parent)
: QObject(parent)
{
	initialized = false;
}

QString VocaleAudiometriePlugin::name() const
{
	return "VocaleAudiometrieWidget";
}

QString VocaleAudiometriePlugin::group() const
{
	return "AudioAdmin Widgets";
}

QString VocaleAudiometriePlugin::toolTip() const
{
	return "";
}

QString VocaleAudiometriePlugin::whatsThis() const
{
	return "";
}

QString VocaleAudiometriePlugin::includeFile() const
{
	return "../../AudioPlugin/src/vocaleaudiometriewidget.h";
}

QIcon VocaleAudiometriePlugin::icon() const
{
	return QIcon();
}

bool VocaleAudiometriePlugin::isContainer() const
{
	return false;
}

QWidget *VocaleAudiometriePlugin::createWidget(QWidget *parent)
{
	VocaleAudiometrieWidget *vocaleAudiometrieWidget = new VocaleAudiometrieWidget(parent);
	return vocaleAudiometrieWidget;
}

bool VocaleAudiometriePlugin::isInitialized() const
{
	return initialized;
}

void VocaleAudiometriePlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
	initialized = true;
}
