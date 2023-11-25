#pragma once

#include <QObject>
#include <QPixmap>
#include <QString>

#include "ForwardDeclarations.hpp"

#include "TessApi.hpp"

namespace scl
{
    class OcrWorker : public QObject
    {
        Q_OBJECT

        public:
            OcrWorker(QObject* a_parent = nullptr);
            ~OcrWorker();

            const QString& getText() const;
            float getConfidence() const;
        
        public slots:
            void onExecute(const QPixmap& a_pixmap);
        
        signals:
            void finished();

        private:
            QString text;
            float confidence;
    };
}