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
    
    const QString DeviceData::toCsv(std::vector<std::unique_ptr<OcrField>>& a_fields) const
    {
        QStringList values;

        for (auto iterator = a_fields.begin(); iterator != a_fields.end(); ++iterator)
        {
            values.push_back(data.at((*(iterator))->getName()));
        }

        for (auto& value : values)
        {
            value.replace(";", "%3B");
        }

        return values.join(";") % "\n";
    }
}