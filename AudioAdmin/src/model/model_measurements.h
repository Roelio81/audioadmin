#ifndef _MODEL_MEASUREMENTS_H
#define _MODEL_MEASUREMENTS_H

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
        int getACRightData(int Hz);
        int getBCRightData(int Hz);
        int getUCLRightData(int Hz);
        int getACLeftData(int Hz);
        int getBCLeftData(int Hz);
        int getUCLLeftData(int Hz);
        int getREWithoutData(int dB);
        int getLEWithoutData(int dB);
        int getRELEWithoutData(int dB);
        int getREWithData(int dB);
        int getLEWithData(int dB);
        int getRELEWithData(int dB);
        int getLocalizationWithout() { return m_localizationWithout; }
        int getLocalizationRight() { return m_localizationRight; }
        int getLocalizationLeft() { return m_localizationLeft; }
        int getLocalizationBoth() { return m_localizationBoth; }

        // --- Setters ---
        void setACRightData(int Hz, int dB);
        void setBCRightData(int Hz, int dB);
        void setUCLRightData(int Hz, int dB);
        void setACLeftData(int Hz, int dB);
        void setBCLeftData(int Hz, int dB);
        void setUCLLeftData(int Hz, int dB);
        void setREWithoutData(int dB, int percentage);
        void setLEWithoutData(int dB, int percentage);
        void setRELEWithoutData(int dB, int percentage);
        void setREWithData(int dB, int percentage);
        void setLEWithData(int dB, int percentage);
        void setRELEWithData(int dB, int percentage);
        void setLocalizationWithout(int dB) { m_localizationWithout = dB; }
        void setLocalizationRight(int dB) { m_localizationRight = dB; }
        void setLocalizationLeft(int dB) { m_localizationLeft = dB; }
        void setLocalizationBoth(int dB) {m_localizationBoth = dB; }

    private:
        // --- Data members ---
        QVector<int> m_acDataRight;
        QVector<int> m_bcDataRight;
        QVector<int> m_uclDataRight;
        QVector<int> m_acDataLeft;
        QVector<int> m_bcDataLeft;
        QVector<int> m_uclDataLeft;
        QVector<int> m_reDataWithout;
        QVector<int> m_leDataWithout;
        QVector<int> m_releDataWithout;
        QVector<int> m_reDataWith;
        QVector<int> m_leDataWith;
        QVector<int> m_releDataWith;
        QMap<int, int> m_hzValuesToIndex;
        QMap<int, int> m_dbValuesToIndex;
        int m_localizationWithout;
        int m_localizationRight;
        int m_localizationLeft;
        int m_localizationBoth;
    };
}

#endif // _MODEL_MEASUREMENTS_H
