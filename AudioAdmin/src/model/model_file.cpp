#include "model_file.h"
#include "model_universe.h"

#include <QDomElement>

using namespace Model;

File::File(int id, const Universe &universe)
: m_id(id)
, m_universe(universe)
, m_physician(-1)
, m_insuranceCompany(-1)
, m_rightHearingAidPrice(0.0)
, m_leftHearingAidPrice(0.0)
, m_testDate(universe.getInvalidDate())
, m_trialDate(universe.getInvalidDate())
, m_physicianReportDate(universe.getInvalidDate())
, m_physicianAdviceDate(universe.getInvalidDate())
, m_insuranceAgreementDate(universe.getInvalidDate())
, m_paymentDate(universe.getInvalidDate())
, m_deliveryDate(universe.getInvalidDate())
, m_exchangeDate(universe.getInvalidDate())
, m_maintenanceContractDate(universe.getInvalidDate())
, m_letterPhysician(*this, true)
, m_letterCustomer(*this, false)
, m_letterInsuranceCompany(*this, true)
, m_invoice(*this)
, m_customer(universe)
{
}

File::~File()
{
}

void File::fromDomElement(const QDomElement &e)
{
    for (QDomElement element = e.firstChildElement(); !element.isNull(); element = element.nextSiblingElement())
    {
        if (element.tagName() == "adjustment")
        {
            m_placeAdjustment = element.text();
        }
        else if (element.tagName() == "dates")
        {
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                QDate date = QDate::fromString(ee.text(), "yyyy-MM-dd");
                if (ee.tagName() == "test")
                    m_testDate = date;
                else if (ee.tagName() == "trial")
                    m_trialDate = date;
                else if (ee.tagName() == "physReport")
                    m_physicianReportDate = date;
                else if (ee.tagName() == "physAdvice")
                    m_physicianAdviceDate = date;
                else if (ee.tagName() == "insAgree")
                    m_insuranceAgreementDate = date;
                else if (ee.tagName() == "payment")
                    m_paymentDate = date;
                else if (ee.tagName() == "delivery")
                    m_deliveryDate = date;
                else if (ee.tagName() == "exchange")
                    m_exchangeDate = date;
                else if (ee.tagName() == "maintenanceContract")
                    m_maintenanceContractDate = date;
            }
        }
        else if (element.tagName() == "hearingAids")
        {
            m_rightHearingAidBrand = "";
            m_rightHearingAidType = "";
            m_leftHearingAidBrand = "";
            m_leftHearingAidType = "";
            for (QDomElement ee = element.firstChildElement(); !ee.isNull(); ee = ee.nextSiblingElement())
            {
                Q_ASSERT(ee.tagName() == "hearingAid");
                QString place = ee.attribute("place");
                QString brand = ee.attribute("brand");
                QString type = ee.attribute("type");
                QString serialNumber = ee.firstChildElement("serialNumber").text();
                double price = ee.firstChildElement("price").text().toDouble();
                if (place == "right")
                {
                    m_rightHearingAidBrand = brand;
                    m_rightHearingAidType = type;
                    m_rightHearingAidSerialNumber = serialNumber;
                    m_rightHearingAidPrice = price;
                }
                else if (place == "left")
                {
                    m_leftHearingAidBrand = brand;
                    m_leftHearingAidType = type;
                    m_leftHearingAidSerialNumber = serialNumber;
                    m_leftHearingAidPrice = price;
                }
            }
        }
        else if (element.tagName() == "letter")
        {
            m_letterCustomer.fromDomElement(element);
        }
        else if (element.tagName() == "physician")
        {
            m_physician = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            QDomElement letter = element.firstChildElement("letter");
            if (!letter.isNull())
                m_letterPhysician.fromDomElement(letter);
        }
        else if (element.tagName() == "insuranceCompany")
        {
            m_insuranceCompany = element.attribute("id").isEmpty() ? -1 : element.attribute("id").toInt();
            m_memberNumber = element.attribute("memberNr");
            QDomElement letter = element.firstChildElement("letter");
            if (!letter.isNull())
                m_letterInsuranceCompany.fromDomElement(letter);
        }
        else if (element.tagName() == "audiometry")
        {
            m_measurements.fromDomElement(element);
        }
        else if (element.tagName() == "invoice")
        {
            m_invoice.fromDomElement(element);
        }
    }

    m_customer.fromDomElement(e);
}

QDomElement File::toDomElement(QDomDocument &d) const
{
    QDomElement result = m_customer.toDomElement(d);
    QDomElement adjustment = d.createElement("adjustment");
    adjustment.appendChild(d.createTextNode(m_placeAdjustment));
    result.appendChild(adjustment);
    QDomElement dates = d.createElement("dates");
    if (m_testDate != m_universe.getInvalidDate())
    {
        QDomElement datum = d.createElement("test");
        datum.appendChild(d.createTextNode(m_testDate.toString("yyyy-MM-dd")));
        dates.appendChild(datum);
    }
    if (m_trialDate != m_universe.getInvalidDate())
    {
        QDomElement datum = d.createElement("trial");
        datum.appendChild(d.createTextNode(m_trialDate.toString("yyyy-MM-dd")));
        dates.appendChild(datum);
    }
    if (m_physicianReportDate != m_universe.getInvalidDate())
    {
        QDomElement datum = d.createElement("physReport");
        datum.appendChild(d.createTextNode(m_physicianReportDate.toString("yyyy-MM-dd")));
        dates.appendChild(datum);
    }
    if (m_physicianAdviceDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("physAdvice");
        date.appendChild(d.createTextNode(m_physicianAdviceDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    if (m_insuranceAgreementDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("insAgree");
        date.appendChild(d.createTextNode(m_insuranceAgreementDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    if (m_paymentDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("payment");
        date.appendChild(d.createTextNode(m_paymentDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    if (m_deliveryDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("delivery");
        date.appendChild(d.createTextNode(m_deliveryDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    if (m_exchangeDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("exchange");
        date.appendChild(d.createTextNode(m_exchangeDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    if (m_maintenanceContractDate != m_universe.getInvalidDate())
    {
        QDomElement date = d.createElement("maintenanceContract");
        date.appendChild(d.createTextNode(m_maintenanceContractDate.toString("yyyy-MM-dd")));
        dates.appendChild(date);
    }
    result.appendChild(dates);
    QDomElement hearingAids = d.createElement("hearingAids");
    if (!m_leftHearingAidType.isEmpty() || !m_leftHearingAidBrand.isEmpty())
    {
        QDomElement hearingAid = d.createElement("hearingAid");
        hearingAid.setAttribute("brand", m_leftHearingAidBrand);
        hearingAid.setAttribute("type", m_leftHearingAidType);
        hearingAid.setAttribute("place", "left");
        if (!m_leftHearingAidSerialNumber.isEmpty())
        {
            QDomElement serialNumber = d.createElement("serialNumber");
            serialNumber.appendChild(d.createTextNode(m_leftHearingAidSerialNumber));
            hearingAid.appendChild(serialNumber);
        }
        if (m_leftHearingAidPrice != 0.0)
        {
            QDomElement price = d.createElement("price");
            price.appendChild(d.createTextNode(QString::number(m_leftHearingAidPrice, 'f', 0)));
            hearingAid.appendChild(price);
        }
        hearingAids.appendChild(hearingAid);
    }
    if (!m_rightHearingAidType.isEmpty() || !m_rightHearingAidBrand.isEmpty())
    {
        QDomElement hearingAid = d.createElement("hearingAids");
        hearingAid.setAttribute("brand", m_rightHearingAidBrand);
        hearingAid.setAttribute("type", m_rightHearingAidType);
        hearingAid.setAttribute("place", "right");
        if (!m_rightHearingAidSerialNumber.isEmpty())
        {
            QDomElement serialNumber = d.createElement("serialNumber");
            serialNumber.appendChild(d.createTextNode(m_rightHearingAidSerialNumber));
            hearingAid.appendChild(serialNumber);
        }
        if (m_rightHearingAidPrice != 0.0)
        {
            QDomElement price = d.createElement("price");
            price.appendChild(d.createTextNode(QString::number(m_rightHearingAidPrice, 'f', 0)));
            hearingAid.appendChild(price);
        }
        hearingAids.appendChild(hearingAid);
    }
    result.appendChild(hearingAids);
    if (!m_letterCustomer.getText().isEmpty())
    {
        QDomElement letter = m_letterCustomer.toDomElement(d);
        result.appendChild(letter);
    }
    QDomElement physician = d.createElement("physician");
    physician.setAttribute("id", (m_physician >= 0) ? QString::number(m_physician) : "");
    if (!m_letterPhysician.getText().isEmpty())
    {
        QDomElement letter = m_letterPhysician.toDomElement(d);
        physician.appendChild(letter);
    }
    result.appendChild(physician);
    QDomElement insuranceCompany = d.createElement("insuranceCompany");
    insuranceCompany.setAttribute("id", (m_insuranceCompany >= 0) ? QString::number(m_insuranceCompany) : "");
    insuranceCompany.setAttribute("memberNr", m_memberNumber);
    if (!m_letterInsuranceCompany.getText().isEmpty())
    {
        QDomElement letter = m_letterInsuranceCompany.toDomElement(d);
        insuranceCompany.appendChild(letter);
    }
    result.appendChild(insuranceCompany);
    QDomElement audiometry = m_measurements.toDomElement(d);
    result.appendChild(audiometry);
    result.setTagName("file");
    result.setAttribute("id", m_id);
    return result;
}

int File::getNofHearingAids() const
{
    int count = 0;
    if (!m_rightHearingAidBrand.isEmpty() || !m_rightHearingAidType.isEmpty())
        ++count;
    if (!m_leftHearingAidBrand.isEmpty() || !m_leftHearingAidType.isEmpty())
        ++count;
    return count;
}
