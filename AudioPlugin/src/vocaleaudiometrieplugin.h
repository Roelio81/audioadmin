#ifndef __VOCALEAUDIOMETRIEPLUGIN_H__
#define __VOCALEAUDIOMETRIEPLUGIN_H__

#include <QDesignerCustomWidgetInterface>

class QIcon;
class QWidget;

class VocaleAudiometriePlugin : public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	VocaleAudiometriePlugin(QObject *parent = 0);

	QString name() const;
	QString group() const;
	QString toolTip() const;
	QString whatsThis() const;
	QString includeFile() const;
	QIcon icon() const;
	bool isContainer() const;
	QWidget *createWidget(QWidget *parent);
	bool isInitialized() const;
	void initialize(QDesignerFormEditorInterface *formEditor);

private:
	bool initialized;
 };

 #endif // __VOCALEAUDIOMETRIEPLUGIN_H__
