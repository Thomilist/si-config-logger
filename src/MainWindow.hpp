#pragma once

#include <array>
#include <memory>
#include <vector>

#include <QAction>
#include <QCheckBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIODevice>
#include <QKeySequence>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpinBox>
#include <QString>
#include <QStringBuilder>
#include <QStringList>
#include <QTableView>
#include <QTextStream>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "DeviceData.hpp"
#include "HistoryTableModel.hpp"
#include "OcrField.hpp"
#include "Screenshot.hpp"
#include "Settings.hpp"

namespace scl
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        
        public:
            MainWindow();
            ~MainWindow();
        
        private slots:
            void onActivate();
            void onAccept();
            void onSave();
            void onClear();
            void onFieldFinished();
        
        signals:
            void execute(const QPixmap& a_pixmap);
        
        private:
            void createInstruction();
            void createFields();
            void createControls();
            void createHistory();

            void saveCsv();

            Settings settings;

            QWidget central_widget;
            QHBoxLayout main_layout;
            std::array<QVBoxLayout, 2> layout_columns;
            QAction activate;
            QAction accept;
            QAction save;
            QAction clearData;

            QGroupBox instruction_group;
            QGridLayout instruction_layout;
            QLabel instruction_text;

            QGroupBox field_group;
            QGridLayout field_layout;
            std::vector<std::unique_ptr<OcrField>> fields;
            unsigned int finished_fields;

            QLabel property_header{"Property"};
            QLabel value_header{"Value"};
            QLabel unit_header{"Unit"};
            QLabel source_header{"Source Image"};
            QLabel confidence_header{"Confidence"};

            QGroupBox control_group;
            QGridLayout control_layout;
            QGridLayout button_layout;
            QPushButton activate_button;
            QPushButton accept_button;
            QPushButton save_button;
            QPushButton clear_button;
            QGridLayout options_layout;
            QLabel auto_accept_label;
            QCheckBox auto_accept_option;
            QLabel show_all_label;
            QCheckBox show_all_option;
            QLabel warning_threshold_label;
            QSpinBox warning_threshold_option;

            QGroupBox history_group;
            QGridLayout history_layout;
            std::vector<DeviceData> history_data;
            HistoryTableModel history_table_model;
            QTableView history_table_view;
    };
}