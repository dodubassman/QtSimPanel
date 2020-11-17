#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include "datastore.h"

class UdpClient : public QObject
{
    Q_OBJECT
public:
    UdpClient(DataStore *dataStore, QObject *parent = nullptr);

signals:

public slots:
    void readStream();

private:
    QUdpSocket *m_socket;
    DataStore *m_dataStore;
};

#endif // UDPCLIENT_H
