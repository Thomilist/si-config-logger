#include "TessApi.hpp"



namespace scl
{
    TessApi::TessApi(const QPixmap& a_pixmap)
    {
        pix = loadPixmap(a_pixmap);
        tess_api = new tesseract::TessBaseAPI();

        if (tess_api->Init("resources/tessdata", "eng"))
        {
            throw std::runtime_error{"Tesseract OCR init failed"};
        }

        tess_api->SetImage(pix);
        tess_api->SetPageSegMode(tesseract::PageSegMode::PSM_SINGLE_LINE);
        tess_api->Recognize(nullptr);
    }
    
    TessApi::~TessApi()
    {
        tess_api->End();
        delete tess_api;

        pixDestroy(&pix);
    }
    
    const QString TessApi::getText()
    {
        return tess_api->GetUTF8Text();
    }
    
    float TessApi::getConfidence()
    {
        auto result_iterator = tess_api->GetIterator();
        return result_iterator ? result_iterator->Confidence(tesseract::PageIteratorLevel::RIL_BLOCK) : 0;
    }
    
    Pix* TessApi::loadPixmap(const QPixmap& a_pixmap)
    {
        QImage image = a_pixmap.toImage();

        if (image.isNull())
        {
            throw std::runtime_error{"Pixmap conversion failed"};
        }

        QByteArray data;
        QBuffer buffer{&data};

        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "BMP");

        return pixReadMemBmp(reinterpret_cast<const l_uint8*>(data.constData()), data.size());
    }
}