#pragma once

#include <QBuffer>
#include <QByteArray>
#include <QImage>
#include <QIODevice>
#include <QPixmap>
#include <QString>
#include <QStringBuilder>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "ForwardDeclarations.hpp"

namespace scl
{
    class TessApi
    {
        public:
            TessApi(const QPixmap& a_pixmap);
            ~TessApi();

            const QString getText();
            float getConfidence();
        
        private:
            [[nodiscard]] Pix* loadPixmap(const QPixmap& a_pixmap);

            Pix* pix;
            tesseract::TessBaseAPI* tess_api;
    };
}