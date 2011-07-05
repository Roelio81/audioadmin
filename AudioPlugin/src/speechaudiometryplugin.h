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
        virtual QString name() const;
        virtual QString group() const;
        virtual QString toolTip() const;
        virtual QString whatsThis() const;
        virtual QString includeFile() const;
        virtual QIcon icon() const;
        virtual bool isContainer() const;
        virtual QWidget *createWidget(QWidget *parent);
        virtual bool isInitialized() const;
        virtual void initialize(QDesignerFormEditorInterface *formEditor);

    private:
        // --- Data members ---
        bool m_initialized;
    };

 #endif // _SPEECHAUDIOMETRYPLUGIN_H
