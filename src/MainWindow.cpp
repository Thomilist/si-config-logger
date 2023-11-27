#include "MainWindow.hpp"


namespace scl
{
    MainWindow::MainWindow()
        : settings(this)
        , history_table_model(&fields, &history_data, this)
    {
        addAction(&activate);
        activate.setShortcut(QKeySequence{"Ctrl+Space"});
        connect(&activate, &QAction::triggered, this, &MainWindow::onActivate);

        addAction(&accept);
        accept.setShortcuts({QKeySequence{"Ctrl+Enter"}, QKeySequence{"Ctrl+Return"}});
        connect(&accept, &QAction::triggered, this, &MainWindow::onAccept);

        addAction(&save);
        connect(&save, &QAction::triggered, this, &MainWindow::onSave);

        addAction(&clearData);
        connect(&clearData, &QAction::triggered, this, &MainWindow::onClear);

        history_table_view.setModel(&history_table_model);
        connect(&history_table_model, &QAbstractTableModel::dataChanged, &history_table_view, &QTableView::resizeColumnsToContents);

        createInstruction();
        createFields();
        createControls();
        createHistory();

        instruction_group.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        field_group.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        control_group.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        history_group.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        layout_columns.at(0).addWidget(&instruction_group);
        layout_columns.at(0).addWidget(&field_group);
        layout_columns.at(0).addWidget(&control_group);
        
        layout_columns.at(1).addWidget(&history_group);

        for (QVBoxLayout& layout : layout_columns)
        {
            main_layout.addLayout(&layout);
        }

        main_layout.setStretchFactor(&layout_columns.at(1), 1);

        setCentralWidget(&central_widget);
        central_widget.setLayout(&main_layout);

        settings.emitState();

        show();
    }
    
    MainWindow::~MainWindow()
    { }
    
    void MainWindow::onActivate()
    {
        activate_button.setEnabled(false);
        activate.setEnabled(false);
        accept_button.setEnabled(false);
        accept.setEnabled(false);
        finished_fields = 0;
        emit execute(screenshot());
        return;
    }
    
    void MainWindow::onAccept()
    {
        history_table_model.addData(fields);
        return;
    }
    
    void MainWindow::onSave()
    {
        
    }
    
    void MainWindow::onClear()
    {
        QMessageBox::StandardButton response = QMessageBox::No;

        response = QMessageBox::warning
        (
            this,
            "Clear log",
            "Are you sure you wish to clear the log? This cannot be undone.",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );

        if (response == QMessageBox::Yes)
        {
            history_table_model.clearData();
        }
        
        return;
    }
    
    void MainWindow::onFieldFinished()
    {
        if (++finished_fields < fields.size())
        {
            return;
        }

        activate_button.setEnabled(true);
        activate.setEnabled(true);
        accept_button.setEnabled(true);
        accept.setEnabled(true);

        if (settings.getAutoAccept())
        {
            accept.trigger();
        }

        return;
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
            auto field = std::make_unique<OcrField>(name, bounding_box, unit, regex, replacements, this);

            column = 0;

            field_layout.addWidget(field->getLabel(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getValueEdit(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getUnitLabel(), row, column++, Qt::AlignVCenter);
            field_layout.addWidget(field->getImageLabel(), row, column++, Qt::AlignCenter);
            field_layout.addWidget(field->getConfidenceLabel(), row, column++, Qt::AlignVCenter | Qt::AlignRight);
            
            field_layout.setRowMinimumHeight(row++, 40);

            connect(this, &MainWindow::execute, field.get(), &OcrField::onExecute);
            connect(field.get(), &OcrField::finished, this, &MainWindow::onFieldFinished);
            connect(&settings, &Settings::confidenceThresholdChanged, field.get(), &OcrField::onConfidenceThresholdChanged);
            
            history_table_model.addField(field);
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

        // Buttons

        connect(&activate_button, &QPushButton::clicked, &activate, &QAction::trigger);
        connect(&accept_button, &QPushButton::clicked, &accept, &QAction::trigger);
        connect(&save_button, &QPushButton::clicked, &save, &QAction::trigger);
        connect(&clear_button, &QPushButton::clicked, &clearData, &QAction::trigger);

        activate_button.setText("Scan\n(Ctrl + Space)");
        accept_button.setText("Accept\n(Ctrl + Enter)");
        save_button.setText("Save to file");
        clear_button.setText("Clear log");

        for (auto* button : {&activate_button, &accept_button, &save_button, &clear_button})
        {
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        }

        button_layout.addWidget(&activate_button, 0, 0);
        button_layout.addWidget(&accept_button, 1, 0);
        button_layout.addWidget(&save_button, 0, 1);
        button_layout.addWidget(&clear_button, 1, 1);

        // Options

        auto_accept_label.setText("Auto accept:");
        show_all_label.setText("Show all:");
        warning_threshold_label.setText("Confidence warning threshold:");

        auto_accept_label.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        show_all_label.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        warning_threshold_label.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        auto_accept_option.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        show_all_option.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        warning_threshold_option.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        warning_threshold_option.setMinimum(0);
        warning_threshold_option.setMaximum(100);
        warning_threshold_option.setSuffix(" %");

        auto_accept_option.setChecked(settings.getAutoAccept());
        show_all_option.setChecked(settings.getShowAll());
        warning_threshold_option.setValue(settings.getConfidenceThreshold());

        connect(&auto_accept_option, &QCheckBox::stateChanged, &settings, &Settings::setAutoAccept);
        connect(&show_all_option, &QCheckBox::stateChanged, &settings, &Settings::setShowAll);
        connect(&warning_threshold_option, &QSpinBox::valueChanged, &settings, &Settings::setConfidenceThreshold);

        int row = 0;

        options_layout.addWidget(&auto_accept_label, row, 0);
        options_layout.addWidget(&auto_accept_option, row++, 1, Qt::AlignRight);
        options_layout.addWidget(&show_all_label, row, 0);
        options_layout.addWidget(&show_all_option, row++, 1, Qt::AlignRight);

        options_layout.addWidget(&warning_threshold_label, row, 0);
        options_layout.addWidget(&warning_threshold_option, row++, 1, Qt::AlignRight);

        // Overall layout

        control_layout.addLayout(&button_layout, 0, 0);
        control_layout.addLayout(&options_layout, 0, 2);

        control_layout.setColumnStretch(1, 1);

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

        history_table_view.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        history_layout.addWidget(&history_table_view, 0, 0);

        history_group.setLayout(&history_layout);
        done = true;
        return;
    }
}