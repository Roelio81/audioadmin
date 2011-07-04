#ifndef _SPEECHAUDIOMETRYPLUGIN_H
#define _SPEECHAUDIOMETRYPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QIcon;
class QWidget;

class SpeechAudiometryPlugin : public QObject, public QDesignerCustomWidgetInterface
    {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

    public:
        explicit SpeechAudiometryPlugin(QObject *parent = 0);

        // --- QDesignerCustomWidgetInterface ---
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
        // --- Data members ---
        bool m_initialized;
    };

 #endif // _SPEECHAUDIOMETRYPLUGIN_H
