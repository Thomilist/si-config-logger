#include "OcrField.hpp"



namespace scl
{
    OcrField::OcrField(
        const QString& a_label,
        const QRect& a_bounding_box,
        const QString& a_unit,
        const QString& a_regex_filter,
        const std::vector<std::pair<QString, QString>> a_replacements,
        QObject* a_parent)
        : QObject(a_parent)
        , worker_thread(this)
        , regex_filter(a_regex_filter)
        , replacements(a_replacements)
        , bounding_box(a_bounding_box)
        , name(a_label)
        , label(a_label % ":")
        , unit(a_unit)
    {
        value.setAlignment(Qt::AlignRight);
        value.setMinimumWidth(150);
        value.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        source_image.setAlignment(Qt::AlignCenter);
        source_image.setMinimumWidth(250);

        replacements.push_back({"\n", " "});

        connect(this, &OcrField::execute, &worker, &OcrWorker::onExecute);
        connect(&worker, &OcrWorker::finished, this, &OcrField::onFinished);

        worker.moveToThread(&worker_thread);
        worker_thread.start();
    }
    
    OcrField::OcrField()
    { }
    
    OcrField::~OcrField()
    {
        worker_thread.quit();
        worker_thread.wait();
    }
    
    const QString& OcrField::getName() const
    {
        return name;
    }
    
    QLabel* OcrField::getLabel()
    {
        return &label;
    }
    
    QLineEdit* OcrField::getValueEdit()
    {
        return &value;
    }
    
    QLabel* OcrField::getUnitLabel()
    {
        return &unit;
    }
    
    QLabel* OcrField::getImageLabel()
    {
        return &source_image;
    }
    
    QLabel* OcrField::getConfidenceLabel()
    {
        return &confidence;
    }
    
    void OcrField::onExecute(const QPixmap& a_pixmap)
    {
        value.setEnabled(false);

        value.clear();
        confidence.clear();
        
        cropped_pixmap = a_pixmap.copy(bounding_box);
        source_image.setPixmap(cropped_pixmap);

        emit execute(cropped_pixmap);
        return;
    }
    
    void OcrField::onFinished()
    {
        updateValue();
        updateConfidence();

        value.setEnabled(true);
        
        emit finished();
        return;
    }
    
    void OcrField::updateValue()
    {
        QString raw_text = worker.getText();
        QString filtered_text;

        for (auto& character : raw_text)
        {
            if (regex_filter.match(character).hasMatch())
            {
                filtered_text.append(character);
            }
        }

        for (auto& replacement : replacements)
        {
            filtered_text.replace(replacement.first, replacement.second);
        }
        
        value.setText(filtered_text.trimmed());
        return;
    }
    
    void OcrField::updateConfidence()
    {
        float value = worker.getConfidence();
        QString formatted_value = QString::number(value, 'f', 1) % " %";

        if (value < 60)
        {
            confidence.setStyleSheet("color: maroon;");
            formatted_value = "⚠️ " % formatted_value;
        }
        else
        {
            confidence.setStyleSheet("color: initial;");
        }

        confidence.setText(formatted_value);
        return;
    }
}