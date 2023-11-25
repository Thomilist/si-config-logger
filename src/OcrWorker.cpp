#include "OcrWorker.hpp"



namespace scl
{
    OcrWorker::OcrWorker(QObject* a_parent)
        : QObject(a_parent)
    {
        
    }
    
    OcrWorker::~OcrWorker()
    { }
    
    const QString& OcrWorker::getText() const
    {
        return text;
    }
    
    float OcrWorker::getConfidence() const
    {
        return confidence;
    }
    
    void OcrWorker::onExecute(const QPixmap& a_pixmap)
    {
        auto tess_api = TessApi(a_pixmap);
        text = tess_api.getText();
        confidence = tess_api.getConfidence();
        emit finished();
        return;
    }
}