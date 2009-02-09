#include <qtdesigner>
#include <qplugin.h>

class AudioPlugins : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

	public:
		AudioPlugins(QObject *parent = 0);
		virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

	private:
		QList<QDesignerCustomWidgetInterface*> m_plugins;
};
