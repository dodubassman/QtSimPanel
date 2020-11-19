#ifndef DATASTORE_H
#define DATASTORE_H
#include <map>
#include <QString>


class DataStore
{
public:
    void writeData(QString const, float);
    float readData(QString const);
private:
    std::map<QString, float> m_data;
};

#endif // DATASTORE_H
