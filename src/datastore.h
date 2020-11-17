#ifndef DATASTORE_H
#define DATASTORE_H
#include <map>
#include <string>


class DataStore
{
public:
    void writeData(std::string const, float);
    float readData(std::string const);
private:
    std::map<std::string, float> m_data;
};

#endif // DATASTORE_H
