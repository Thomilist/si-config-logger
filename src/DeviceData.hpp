#pragma once

#include <map>
#include <vector>

#include <QString>

#include "ForwardDeclarations.hpp"

#include "OcrField.hpp"

namespace scl
{
    class DeviceData
    {
        public:
            DeviceData(std::vector<std::unique_ptr<OcrField>>& a_fields);
            DeviceData();
            ~DeviceData();

            void setData(std::vector<std::unique_ptr<OcrField>>& a_fields);
            const std::map<QString, QString>& getData() const;
        
        private:
            std::map<QString, QString> data;
    };
}