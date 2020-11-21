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

    if (buffer[0] == 'D' && buffer[1] == 'A' && buffer[2] == 'T' && buffer[3] == 'A') // Handle XPlane DATA
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
            }
        }
    }
    else if (buffer[0] == 'D' && buffer[1] == 'R' && buffer[2] == 'E' && buffer[3] == 'F') // Handle XPlane DREF
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
                //qDebug() << i.value() << " : " << value;
                m_dataStore->writeData(i.value(), value);
            }
        }
    }
}
