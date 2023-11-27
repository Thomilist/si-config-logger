#include "DeviceData.hpp"



namespace scl
{
    DeviceData::DeviceData(std::vector<std::unique_ptr<OcrField>>& a_fields)
    {
        setData(a_fields);
    }
    
    DeviceData::DeviceData()
    { }
    
    DeviceData::~DeviceData()
    { }
    
    void DeviceData::setData(std::vector<std::unique_ptr<OcrField>>& a_fields)
    {
        data.clear();

        for (auto iterator = a_fields.begin(); iterator != a_fields.end(); ++iterator)
        {
            data.insert({(*(iterator))->getName(), (*(iterator))->getValueEdit()->text()});
        }

        return;
    }
    
    const std::map<QString, QString>& DeviceData::getData() const
    {
        return data;
    }
}