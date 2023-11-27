#pragma once

#include <vector>

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringBuilder>
#include <QThread>

#include "ForwardDeclarations.hpp"

#include "OcrWorker.hpp"

namespace scl
{
    class OcrField : public QObject
    {
        Q_OBJECT

        public:
            OcrField(
                const QString& a_label,
                const QRect& a_bounding_box,
                const QString& a_unit,
                const QString& a_regex_filter,
                const std::vector<std::pair<QString, QString>> a_replacements,
                QObject* a_parent);
            OcrField();
            ~OcrField();

            const QString& getName() const;
            QLabel* getLabel();
            QLineEdit* getValueEdit();
            QLabel* getUnitLabel();
            QLabel* getImageLabel();
            QLabel* getConfidenceLabel();
        
        public slots:
            void onExecute(const QPixmap& a_pixmap);
        
        private slots:
            void onFinished();
        
        signals:
            void execute(const QPixmap& a_cropped_pixmap);
            void finished();
        
        private:
            void updateValue();
            void updateConfidence();

            QThread worker_thread;
            OcrWorker worker;
            QPixmap cropped_pixmap;

            QRegularExpression regex_filter;
            std::vector<std::pair<QString, QString>> replacements;
            QRect bounding_box;

            QString name;
            QLabel label;
            QLineEdit value;
            QLabel unit;
            QLabel source_image;
            QLabel confidence;
    };
}