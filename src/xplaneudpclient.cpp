#include <cstring>

#include "xplaneudpclient.h"

XplaneUdpClient::XplaneUdpClient(DataStore *dataStore, QObject *parent) : QObject(parent)
{
    quint16 port = 49000;
    m_dataStore = dataStore;

    // Index of Xplane Data in UDP packets (DATA)
    // m_dataIndex[<segment_index>][<data_value_index>] = "<variable_name_in_qtSimPanel>"
    // Exple:
    // m_dataIndex[3][5] = "mph_ias";

    // Index of Xplane DataRefs in UDP packets (DREF)
    // m_dataRefs["<uri_xplane_dataref>"] = "<variable_name_in_qtSimPanel>";
    // Exple:
    // m_dataRefs["sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot"] = "inhg_baro_pressure";

    m_dataRefs["sim/cockpit2/radios/actuators/nav1_course_deg_mag_pilot"] = "nav1_course";
    m_dataRefs["sim/cockpit2/radios/indicators/nav1_flag_from_to_pilot"] = "nav1_from_to_status";
    m_dataRefs["sim/cockpit2/radios/indicators/nav1_flag_glideslope_mech"] = "nav1_glideslope_status";
    m_dataRefs["sim/cockpit2/radios/indicators/nav1_hdef_dots_pilot"] = "nav1_course_deviation";
    m_dataRefs["sim/cockpit2/radios/indicators/nav1_vdef_dots_pilot"] = "nav1_glideslope_deviation";

    m_dataRefs["sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot"] = "inhg_baro_pressure";
    m_dataRefs["sim/cockpit2/gauges/indicators/altitude_ft_pilot"] = "altitude_ind";
    m_dataRefs["sim/cockpit2/gauges/indicators/sideslip_degrees"] = "sideslip";
    m_dataRefs["sim/cockpit2/gauges/indicators/vvi_fpm_pilot"] = "vertical_speed";
    m_dataRefs["sim/cockpit2/gauges/indicators/airspeed_kts_pilot"] = "kt_ias";
    m_dataRefs["sim/cockpit2/gauges/indicators/pitch_vacuum_deg_pilot"] = "pitch";
    m_dataRefs["sim/cockpit2/gauges/indicators/roll_vacuum_deg_pilot"] = "roll";
    m_dataRefs["sim/cockpit2/gauges/indicators/heading_vacuum_deg_mag_pilot"] = "vacuum_heading";

    m_socket = new QUdpSocket(this);
    m_socket->bind(port);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readStream()));


    QTimer *m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(tryRegisterDataRefs()));
    m_timer->start(2000);
}

XplaneUdpClient::~XplaneUdpClient() {
    // Unregister (frequence = 0Hz)
    QMapIterator<QString, QString> i(m_dataRefs);
    uint32_t idCpt = 0;

    while (i.hasNext()) {
        i.next();
        // Frequency to zero to unsubscribe
        registerDataRef(0, idCpt, i.key());
        idCpt++;
    }
}


void XplaneUdpClient::tryRegisterDataRefs()
{

    // Iterate through required dataRefs
    QMapIterator<QString, QString> i(m_dataRefs);
    uint32_t idCpt = 0;

    while (i.hasNext()) {
        i.next();
        registerDataRef(5, idCpt, i.key());
        idCpt++;
    }

}

void XplaneUdpClient::registerDataRef(uint32_t frequency, uint32_t idRef, QString dataRef)
{

    if (!m_b_isConnected or frequency == 0) {

        char name[5] = "RREF";
        uint8_t zero = 0;

        QByteArray data;

        data.append(name);
        data = data.leftJustified(data.length() + 1, zero);
        data.append(frequency);
        data = data.leftJustified(data.length() + 6, zero);
        data.append(idRef);
        data.append(dataRef);
        data = data.leftJustified(data.length() + (400 - dataRef.length()), zero);

        m_socket->writeDatagram(data, QHostAddress("192.168.5.139"), 49000);

    }
}

void XplaneUdpClient::readStream()
{

    const qint64 maxLength = 65536;
    char buffer[maxLength];

    unsigned int datagramSize = m_socket->pendingDatagramSize();

    QHostAddress sender;
    quint16 senderPort;

    m_socket->readDatagram(buffer, maxLength, &sender, &senderPort);

    union { int intValue; float floatValue; } ieee754Union;

    if (strncmp(buffer, "DATA", 4) == 0)
    {
        // Segments of data
        unsigned nbSegs = (datagramSize-5)/36;

        // For each xplane dataset segment
        for (unsigned i = 0; i < nbSegs; i++)
        {
            // Get index
            unsigned startIndex = (5+i*36);
            unsigned  segmentType = buffer[startIndex];

            char dataSegment[32];
            memcpy( dataSegment, &buffer[startIndex+4], 32 );

            // Only handle Segment known by dataIndex
            if (!m_dataIndex[segmentType].isEmpty())
            {
                // Iterate through known values in current segment
                QMapIterator<int, QString> i(m_dataIndex[segmentType]);
                while (i.hasNext()) {
                    i.next();


                    // Convert parts to integers with "Bitwise And"
                    int position = i.key()*4;
                    int a = dataSegment[0+position] & 0xFF;
                    int b = dataSegment[1+position] & 0xFF;
                    int c = dataSegment[2+position] & 0xFF;
                    int d = dataSegment[3+position] & 0xFF;

                    // Rebuild the big endian value with "Bitwise Or"
                    int recontructedHexa = (d<<24) | (c<<16) | (b<<8) | a;

                    // Use union to get ieee 754 single precision float
                    ieee754Union.intValue = recontructedHexa;
                    float value = ieee754Union.floatValue;

                    // Write value in datastore
                    m_dataStore->writeData(i.value(), value);
                }
                m_timer->stop();
            }
        }
    }
    else if (strncmp(buffer, "DREF", 4) == 0)
    {
        char dataSegment[500];
        memcpy( dataSegment, &buffer[9], 500 );

        QString dataRef(dataSegment);

        // Iterate through required dataRefs in current segment
        QMapIterator<QString, QString> i(m_dataRefs);

        while (i.hasNext()) {
            i.next();

            if (i.key() == dataRef) {
                // Convert parts to integers with "Bitwise And"
                int a = buffer[5] & 0xFF;
                int b = buffer[6] & 0xFF;
                int c = buffer[7] & 0xFF;
                int d = buffer[8] & 0xFF;

                // Rebuild the big endian value with "Bitwise Or"
                int recontructedHexa = (d<<24) | (c<<16) | (b<<8) | a;

                // Use union to get ieee 754 single precision float
                ieee754Union.intValue = recontructedHexa;
                float value = ieee754Union.floatValue;

                // Write value in datastore
                m_dataStore->writeData(i.value(), value);
            }
        }
    }
    else if (strncmp(buffer, "RREF", 4) == 0)
    {

        // Segments of data
        unsigned nbDataRefs = (datagramSize-5)/8;

        char data[datagramSize-5];
        memcpy( data, &buffer[5], datagramSize-5 );

        // For each xplane dataRef
        for (unsigned j = 0; j < nbDataRefs; j++)
        {
            int position = j*8;
            int idRef = buffer[position + 8];

            // Parse received Data
            int a = buffer[position + 9] & 0xFF;
            int b = buffer[position + 10] & 0xFF;
            int c = buffer[position + 11] & 0xFF;
            int d = buffer[position + 12] & 0xFF;

            // Rebuild the big endian value with "Bitwise Or"
            int recontructedHexa = (d<<24) | (c<<16) | (b<<8) | a;

            // Use union to get ieee 754 single precision float
            ieee754Union.intValue = recontructedHexa;
            float value = ieee754Union.floatValue;

            int idCpt = 0;

            // Loop through Requested value to match Ids.
            QMapIterator<QString, QString> i(m_dataRefs);
            while (i.hasNext()) {
                i.next();

                if (idCpt == idRef)
                {
                    qDebug() << i.value() << " : " << value;
                    m_dataStore->writeData(i.value(), value);
                }

                idCpt++;
            }

        }
        m_b_isConnected = true;

    }
}
