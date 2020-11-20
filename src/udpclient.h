#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include "datastore.h"

class XplaneUdpClient : public QObject
{
    Q_OBJECT
public:
    XplaneUdpClient(DataStore *dataStore, QObject *parent = nullptr);

signals:

public slots:
    void readStream();

private:
    QUdpSocket *m_socket;
    DataStore *m_dataStore;
    QMap<int, QMap<int, QString>> m_dataIndex;
    QMap<QString, QString> m_dataRefs;
};

#endif // UDPCLIENT_H
