#include "MainWindow.hpp"


namespace scl
{
    MainWindow::MainWindow()
    {
        addAction(&activate);
        activate.setShortcut(QKeySequence{"Ctrl+Space"});
        connect(&activate, &QAction::triggered, this, &MainWindow::onActivate);

        addAction(&accept);
        accept.setShortcut(QKeySequence{"Ctrl+Enter"});
        connect(&accept, &QAction::triggered, this, &MainWindow::onAccept);

        addAction(&save);
        connect(&save, &QAction::triggered, this, &MainWindow::onSave);

        createInstruction();
        createFields();
        createControls();
        createHistory();

        layout_columns.at(0).addWidget(&instruction_group);
        layout_columns.at(0).addWidget(&field_group);
        layout_columns.at(0).addWidget(&control_group);
        
        layout_columns.at(1).addWidget(&history_group);

        for (QVBoxLayout& layout : layout_columns)
        {
            main_layout.addLayout(&layout);
        }

        setCentralWidget(&central_widget);
        central_widget.setLayout(&main_layout);

        show();
    }
    
    MainWindow::~MainWindow()
    {
        for (auto field : fields)
        {
            delete field;
        }
    }
    
    void MainWindow::onActivate()
    {
        emit execute(screenshot());

        return;
    }
    
    void MainWindow::onAccept()
    {
        
    }
    
    void MainWindow::onSave()
    {
        
    }
    
    void MainWindow::onFieldFinished()
    {
        
    }
    
    void MainWindow::createInstruction()
    {
        static bool done{false};
        
        if (done)
        {
            return;
        }

        instruction_text.setTextFormat(Qt::RichText);
        instruction_text.setWordWrap(true);
        instruction_text.setText
        (
            QString()
            % "<p>Follow these steps to load information from SPORTident Config+:</p>"
            % "<ol>"
            % "<li>Open SPORTident Config+ and place it maximised on the first screen</li>"
            % "<li>Read device in SPORTident Config+ and (optionally) set its time</li>"
            % "<li>Run a scan with si-config-logger (this program)</li>"
            % "<li>Check scanned values, correct if necessary and accept</li>"
            % "<li>Repeat from step 2 with the next device</li>"
            % "</ol>"
            % "<p>Tested with SPORTident Config+ v2.11.0 on 1920x1080 resolution. "
            % "Performance may be improved by setting the environment variable OMP_THREAD_LIMIT to 1.</p>"
        );

        instruction_layout.addWidget(&instruction_text, 0, 0);
        
        instruction_group.setLayout(&instruction_layout);
        done = true;
        return;
    }
    
    void MainWindow::createFields()
    {
        static bool done{false};
        
        if (done)
        {
            return;
        }

        int row = 0;
        int column = 0;

        field_layout.addWidget(&property_header, row, column++);
        field_layout.addWidget(&value_header, row, column++);
        field_layout.addWidget(&unit_header, row, column++);
        field_layout.addWidget(&source_header, row, column++, Qt::AlignCenter);
        field_layout.addWidget(&confidence_header, row, column++);

        property_header.setStyleSheet("font-weight: bold;");
        value_header.setStyleSheet("font-weight: bold;");
        unit_header.setStyleSheet("font-weight: bold;");
        source_header.setStyleSheet("font-weight: bold;");
        confidence_header.setStyleSheet("font-weight: bold;");

        ++row;

        const std::tuple<QString, QRect, QString, QString, std::vector<std::pair<QString, QString>>> args[] =
        {
            #include "Fields.hpp"
        };

        for (auto& [name, bounding_box, unit, regex, replacements] : args)
        {
            auto field = new OcrField{name, bounding_box, unit, regex, replacements, this};
            fields.push_back(field);

            column = 0;

            field_layout.addWidget(field->getLabel(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getValueEdit(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getUnitLabel(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getImageLabel(), row, column++, Qt::AlignCenter);
            field_layout.addWidget(field->getConfidenceLabel(), row, column++, Qt::AlignVCenter | Qt::AlignRight);
            
            field_layout.setRowMinimumHeight(row++, 40);

            connect(this, &MainWindow::execute, field, &OcrField::onExecute);
            connect(field, &OcrField::finished, this, &MainWindow::onFieldFinished);
        }

        field_group.setLayout(&field_layout);
        done = true;
        return;
    }
    
    void MainWindow::createControls()
    {
        static bool done{false};
        
        if (done)
        {
            return;
        }

        connect(&activate_button, &QPushButton::clicked, &activate, &QAction::trigger);
        connect(&accept_button, &QPushButton::clicked, &accept, &QAction::trigger);
        connect(&save_button, &QPushButton::clicked, &save, &QAction::trigger);

        activate_button.setText("Scan\n(Ctrl + Space)");
        accept_button.setText("Accept\n(Ctrl + Enter)");
        save_button.setText("Save to file");

        int column = 0;

        for (auto* button : {&activate_button, &accept_button, &save_button})
        {
            control_layout.addWidget(button, 0, column++);
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        }

        control_group.setLayout(&control_layout);
        done = true;
        return;
    }
    
    void MainWindow::createHistory()
    {
        static bool done{false};
        
        if (done)
        {
            return;
        }




        history_group.setLayout(&history_layout);
        done = true;
        return;
    }
}