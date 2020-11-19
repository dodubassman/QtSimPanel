#include "datastore.h"

void DataStore::writeData(QString const name, float value)
{
    m_data[name] = value;
}

float DataStore::readData(QString const name)
{
    return m_data[name];
}
