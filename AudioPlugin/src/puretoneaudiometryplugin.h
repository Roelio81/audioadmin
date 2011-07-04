#ifndef _PURETONEAUDIOMETRYPLUGIN_H
#define _PURETONEAUDIOMETRYPLUGIN_H

#include <QDesignerCustomWidgetInterface>

class QIcon;
class QWidget;

class PureToneAudiometryPlugin : public QObject, public QDesignerCustomWidgetInterface
    {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

    public:
        explicit PureToneAudiometryPlugin(QObject *parent = 0);

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

 #endif // _PURETONEAUDIOMETRYPLUGIN_H
