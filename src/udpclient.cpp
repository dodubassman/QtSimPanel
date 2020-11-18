#include "udpclient.h"

UdpClient::UdpClient(DataStore *dataStore, QObject *parent) : QObject(parent)
{
    quint16 port = 49000;
    m_dataStore = dataStore;

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
// todo set online
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

            char dataSegment[24];
            memcpy( dataSegment, &buffer[startIndex+4], 24 );

            // Heading
            if (segmentType == 17)
            {

                // 8*4 byte in each segment
                for (unsigned j = 0; j < 8; j++)
                {

                    int position = j*4;

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
                    switch (position) {
                    case 0:
                        m_dataStore->writeData("pitch", value);
                        break;
                    case 4:
                        m_dataStore->writeData("roll", value);
                        break;
                    case 8:
                        m_dataStore->writeData("true_heading", value);
                        break;
                    case 12:
                        m_dataStore->writeData("mag_heading", value);
                        break;

                    }
                }
            }
        }
    }
}
