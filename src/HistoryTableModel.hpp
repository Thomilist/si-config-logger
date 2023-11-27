#pragma once

#include <memory>
#include <vector>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QVariant>

#include "ForwardDeclarations.hpp"

#include "DeviceData.hpp"
#include "OcrField.hpp"

namespace scl
{
    class HistoryTableModel : public QAbstractTableModel
    {
        Q_OBJECT

        public:
            HistoryTableModel(
                std::vector<std::unique_ptr<OcrField>>* a_fields,
                std::vector<DeviceData>* a_data,
                QObject* a_parent = nullptr);
            ~HistoryTableModel();

            int rowCount(const QModelIndex& a_parent = QModelIndex()) const override;
            int columnCount(const QModelIndex& a_parent = QModelIndex()) const override;
            bool insertRows(int a_row, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            bool removeRows(int a_row, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            bool insertColumns(int a_column, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            bool removeColumns(int a_column, int a_count, const QModelIndex& a_parent = QModelIndex()) override;
            QVariant data(const QModelIndex& a_index, int a_role = Qt::DisplayRole) const override;
            QVariant headerData(int a_section, Qt::Orientation a_orientation, int a_role = Qt::DisplayRole) const override;
        
            void addField(std::unique_ptr<OcrField>& a_field);
            void addData(std::vector<std::unique_ptr<OcrField>>& a_fields);

            void clearFields();
            void clearData();

        private:
            std::vector<std::unique_ptr<OcrField>>* fields;
            std::vector<DeviceData>* values;
    };
}