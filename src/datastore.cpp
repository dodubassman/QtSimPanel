#include "datastore.h"

void DataStore::writeData(std::string const name, float value)
{
    m_data[name] = value;
}

float DataStore::readData(std::string const name)
{
    return m_data[name];
}
