#include "udpclient.h"

UdpClient::UdpClient(DataStore *dataStore, QObject *parent) : QObject(parent)
{
    quint16 port = 49000;
    m_dataStore = dataStore;

    // Index of Xplane Data in UDP packets
    // Speeds
    m_dataIndex[3][0] = "kt_ias";
    m_dataIndex[3][5] = "mph_ias";

    m_dataIndex[4][2] = "vertical_speed";

    // Pressure
    m_dataIndex[7][0] = "inhg_baro_pressure";

    // Attitudes
    m_dataIndex[17][0] = "pitch";
    m_dataIndex[17][1] = "roll";
    m_dataIndex[17][2] = "true_heading";
    m_dataIndex[17][3] = "mag_heading";

    // AoA, Sideslip, paths
    m_dataIndex[18][7] = "sideslip";

    // Altitudes
    m_dataIndex[20][5] = "altitude_ind";
    m_dataIndex[24][0] = "altitude_msl";


    m_socket = new QUdpSocket(this);
    m_socket->bind(port);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readStream()));
}

// The first 4 byte are the header. if xplane send data (stuff you selected in the data output) they read, in ASCII : "DATA".
// followed by 1 byte you can ignore
// followed by 4 byte, but only the first of the four is important : it's the index (the stuff in the 1st column)
// followed by 8*4 byte : they are the data. For more inforation also check "show in cockpit" in the preference so you'll now more about what the data are.
// then you have another pack of 4 + 8*4 until the end of the datagram.
// rince, repeat
void UdpClient::readStream()
{
    const qint64 maxLength = 65536;
    char buffer[maxLength];

    unsigned int datagramSize = m_socket->pendingDatagramSize();

    QHostAddress sender;
    quint16 senderPort;

    m_socket->readDatagram(buffer, maxLength, &sender, &senderPort);

    // Segments of data
    unsigned nbSegs = (datagramSize-5)/36;

    // If header "DATA": Xplane is online
    if (buffer[0] == 'D' && buffer[1] == 'A' && buffer[2] == 'T' && buffer[3] == 'A')
    {
        union
        {
            int num;
            float fnum;
        } integerFloatUnion;

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

                    int position = i.key()*4;

                    // Convert parts to integers with "Bitwise And"
                    int a = dataSegment[0+position] & 0xFF;
                    int b = dataSegment[1+position] & 0xFF;
                    int c = dataSegment[2+position] & 0xFF;
                    int d = dataSegment[3+position] & 0xFF;

                    // Rebuild the big endian value with "Bitwise Or"
                    int recontructedHexa = (d<<24) | (c<<16) | (b<<8) | a;

                    // Use union to get ieee 754 single precision float
                    integerFloatUnion.num = recontructedHexa;
                    float value = integerFloatUnion.fnum;

                    // Write value in datastore
                    m_dataStore->writeData(i.value(), value);
//                    qDebug() << i.value() << " : " << value;
                }

            }
        }
    }
}
