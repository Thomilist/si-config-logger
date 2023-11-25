#pragma once

#include <array>
#include <vector>

#include <QAction>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QStringBuilder>
#include <QThread>
#include <QVBoxLayout>
#include <QWidget>

#include "ForwardDeclarations.hpp"

#include "OcrField.hpp"
#include "Screenshot.hpp"

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
            void onFieldFinished();
        
        signals:
            void execute(const QPixmap& a_pixmap);
        
        private:
            void createInstruction();
            void createFields();
            void createControls();
            void createHistory();

            QWidget central_widget;
            QHBoxLayout main_layout;
            std::array<QVBoxLayout, 2> layout_columns;
            QAction activate;
            QAction accept;
            QAction save;

            QGroupBox instruction_group;
            QGridLayout instruction_layout;
            QLabel instruction_text;

            QGroupBox field_group;
            QGridLayout field_layout;
            std::vector<OcrField*> fields;

            QLabel property_header{"Property"};
            QLabel value_header{"Value"};
            QLabel unit_header{"Unit"};
            QLabel source_header{"Source Image"};
            QLabel confidence_header{"Confidence"};

            QGroupBox control_group;
            QGridLayout control_layout;
            QPushButton activate_button;
            QPushButton accept_button;
            QPushButton save_button;

            QGroupBox history_group;
            QGridLayout history_layout;
    };
}