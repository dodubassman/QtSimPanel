#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include "datastore.h"

class XplaneUdpClient : public QObject
{
    Q_OBJECT
public:
    XplaneUdpClient(DataStore *dataStore, QObject *parent = nullptr);
    ~XplaneUdpClient();

signals:

public slots:
    void readStream();
    void tryRegisterDataRefs();

private:
    QUdpSocket *m_socket;
    DataStore *m_dataStore;
    QMap<int, QMap<int, QString>> m_dataIndex;
    QMap<QString, QString> m_dataRefs;
    void registerDataRef(uint32_t frequency, uint32_t idRef, QString dataRef);
    bool m_b_isConnected = false;
    QTimer *m_timer;
};



#endif // UDPCLIENT_H
