#ifndef _MODEL_MEETGEGEVENS_H
#define _MODEL_MEETGEGEVENS_H

#include <QMap>
#include <QVector>

class QDomDocument;
class QDomElement;

namespace Model
{
    class Measurements
    {
    public:
        explicit Measurements();
        virtual ~Measurements();

        // --- ISerializable ---
        virtual void fromDomElement(const QDomElement &e);
        virtual QDomElement toDomElement(QDomDocument &d) const;

        // --- Getters ---
        int getLGRechtsData(int Hz);
        int getBGRechtsData(int Hz);
        int getUCLRechtsData(int Hz);
        int getLGLinksData(int Hz);
        int getBGLinksData(int Hz);
        int getUCLLinksData(int Hz);
        int getROZonderData(int dB);
        int getLOZonderData(int dB);
        int getROLOZonderData(int dB);
        int getROMetData(int dB);
        int getLOMetData(int dB);
        int getROLOMetData(int dB);
        int getLocalisatieZonder() { return m_localisatieZonder; }
        int getLocalisatieRechts() { return m_localisatieRechts; }
        int getLocalisatieLinks() { return m_localisatieLinks; }
        int getLocalisatieBeide() { return m_localisatieBeide; }

        // --- Setters ---
        void setLGRechtsData(int Hz, int dB);
        void setBGRechtsData(int Hz, int dB);
        void setUCLRechtsData(int Hz, int dB);
        void setLGLinksData(int Hz, int dB);
        void setBGLinksData(int Hz, int dB);
        void setUCLLinksData(int Hz, int dB);
        void setROZonderData(int dB, int percentage);
        void setLOZonderData(int dB, int percentage);
        void setROLOZonderData(int dB, int percentage);
        void setROMetData(int dB, int percentage);
        void setLOMetData(int dB, int percentage);
        void setROLOMetData(int dB, int percentage);
        void setLocalisatieZonder(int dB) { m_localisatieZonder = dB; }
        void setLocalisatieRechts(int dB) { m_localisatieRechts = dB; }
        void setLocalisatieLinks(int dB) { m_localisatieLinks = dB; }
        void setLocalisatieBeide(int dB) {m_localisatieBeide = dB; }

    private:
        // --- Data members ---
        QVector<int> m_lgDataRechts;
        QVector<int> m_bgDataRechts;
        QVector<int> m_uclDataRechts;
        QVector<int> m_lgDataLinks;
        QVector<int> m_bgDataLinks;
        QVector<int> m_uclDataLinks;
        QVector<int> m_roDataZonder;
        QVector<int> m_loDataZonder;
        QVector<int> m_roloDataZonder;
        QVector<int> m_roDataMet;
        QVector<int> m_loDataMet;
        QVector<int> m_roloDataMet;
        QMap<int, int> m_hzValuesToIndex;
        QMap<int, int> m_dbValuesToIndex;
        int m_localisatieZonder;
        int m_localisatieRechts;
        int m_localisatieLinks;
        int m_localisatieBeide;
    };
}

#endif // _MODEL_MEETGEGEVENS_H