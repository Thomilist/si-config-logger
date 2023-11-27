#include "HistoryTableModel.hpp"



namespace scl
{
    HistoryTableModel::HistoryTableModel(
        std::vector<std::unique_ptr<OcrField>>* a_fields,
        std::vector<DeviceData>* a_data,
        QObject* a_parent)
        : QAbstractTableModel(a_parent)
        , fields(a_fields)
        , values(a_data)
    {
        
    }
    
    HistoryTableModel::~HistoryTableModel()
    { }
    
    int HistoryTableModel::rowCount(const QModelIndex& /*a_parent*/) const 
    {
        return values->size();
    }
    
    int HistoryTableModel::columnCount(const QModelIndex& /*a_parent*/) const 
    {
        return fields->size();
    }
    
    bool HistoryTableModel::insertRows(int a_row, int a_count, const QModelIndex& a_parent)
    {
        beginInsertRows(a_parent, a_row, a_row + a_count - 1);
        values->insert(values->begin() + a_row, a_count, DeviceData());
        endInsertRows();
        return true;
    }
    
    bool HistoryTableModel::removeRows(int a_row, int a_count, const QModelIndex& a_parent)
    {
        beginRemoveRows(a_parent, a_row, a_row + a_count - 1);
        values->erase(values->begin() + a_row, values->begin() + a_row + a_count);
        endRemoveRows();
        return true;
    }
    
    bool HistoryTableModel::insertColumns(int a_column, int a_count, const QModelIndex& a_parent)
    {
        beginInsertColumns(a_parent, a_column, a_column + a_count - 1);

        for (int i = 0; i < a_count; ++i)
        {
            fields->emplace(fields->begin() + a_column, std::make_unique<OcrField>());
        }

        endInsertColumns();
        return true;
    }
    
    bool HistoryTableModel::removeColumns(int a_column, int a_count, const QModelIndex& a_parent)
    {
        beginRemoveColumns(a_parent, a_column, a_column + a_count - 1);
        fields->erase(fields->begin() + a_column, fields->begin() + a_column + a_count);
        endRemoveColumns();
        return true;
    }
    
    QVariant HistoryTableModel::data(const QModelIndex& a_index, int a_role) const 
    {
        switch (a_role)
        {
            case Qt::DisplayRole:
            {
                if (static_cast<size_t>(a_index.column()) < fields->size())
                {
                    return values->at(a_index.row()).getData().at(fields->at(a_index.column())->getName());
                }
                
                break;
            }
            case Qt::TextAlignmentRole:
            {
                break;
            }
            default:
            {
                break;
            }
        }

        return QVariant();
    }
    
    QVariant HistoryTableModel::headerData(int a_section, Qt::Orientation a_orientation, int a_role) const 
    {
        switch (a_orientation)
        {
            case Qt::Orientation::Vertical:
            {
                break;
            }
            case Qt::Orientation::Horizontal:
            {
                switch (a_role)
                {
                    case Qt::DisplayRole:
                    {
                        if (static_cast<size_t>(a_section) < fields->size())
                        {
                            if (fields->at(a_section))
                            {
                                return fields->at(a_section)->getName();
                            }
                        }
                        
                        break;
                    }
                    case Qt::TextAlignmentRole:
                    {
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                
                break;
            }
            default:
            {
                break;
            }
        }

        return QVariant();
    }
    
    void HistoryTableModel::addField(std::unique_ptr<OcrField>& a_field)
    {
        insertColumn(columnCount());
        fields->back() = std::move(a_field);
        emit dataChanged(createIndex(0, columnCount()), createIndex(rowCount(), columnCount()), {Qt::DisplayRole});
        return;
    }
    
    void HistoryTableModel::addData(std::vector<std::unique_ptr<OcrField>>& a_fields)
    {
        insertRow(rowCount());
        values->back().setData(a_fields);
        emit dataChanged(createIndex(rowCount(), 0), createIndex(rowCount(), columnCount()), {Qt::DisplayRole});
        return;
    }
    
    void HistoryTableModel::clearFields()
    {
        removeColumns(0, columnCount());
        return;
    }
    
    void HistoryTableModel::clearData()
    {
        removeRows(0, rowCount());
        return;
    }
}