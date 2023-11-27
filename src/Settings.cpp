#include "Settings.hpp"



namespace scl
{
    Settings::Settings(QMainWindow* a_parent)
        : QSettings(a_parent)
        , main_window(a_parent)
    {
        load();
    }
    
    Settings::~Settings()
    {
        save();
    }
    
    void Settings::emitState()
    {
        emit autoAcceptChanged(auto_accept);
        emit showAllChanged(show_all);
        emit confidenceThresholdChanged(confidence_threshold);
        
        return;
    }
    
    QString Settings::getGeometryAlias()
    {
        return "geometry";
    }
    
    QString Settings::getAutoAcceptAlias()
    {
        return "auto_accept";
    }
    
    QString Settings::getShowAllAlias()
    {
        return "show_all";
    }
    
    QString Settings::getConfidenceThresholdAlias()
    {
        return "confidence_threshold";
    }
    
    bool Settings::getAutoAccept() const
    {
        return auto_accept;
    }
    
    bool Settings::getShowAll() const
    {
        return show_all;
    }
    
    int Settings::getConfidenceThreshold() const
    {
        return confidence_threshold;
    }
    
    void Settings::setAutoAccept(bool a_state)
    {
        auto_accept = a_state;
        emit autoAcceptChanged(auto_accept);
        return;
    }
    
    void Settings::setShowAll(bool a_state)
    {
        show_all = a_state;
        emit showAllChanged(show_all);
        return;
    }
    
    void Settings::setConfidenceThreshold(int a_threshold)
    {
        confidence_threshold = a_threshold;
        emit confidenceThresholdChanged(confidence_threshold);
        return;
    }
    
    void Settings::load()
    {
        const QByteArray geometry = value(getGeometryAlias(), QByteArray()).toByteArray();

        if (!geometry.isEmpty())
        {
            main_window->restoreGeometry(geometry);
        }

        setAutoAccept(value(getAutoAcceptAlias(), false).toBool());
        setShowAll(value(getShowAllAlias(), false).toBool());
        setConfidenceThreshold(value(getConfidenceThresholdAlias(), 60).toInt());

        return;
    }
    
    void Settings::save()
    {
        setValue(getGeometryAlias(), main_window->saveGeometry());
        setValue(getAutoAcceptAlias(), getAutoAccept());
        setValue(getShowAllAlias(), getShowAll());
        setValue(getConfidenceThresholdAlias(), getConfidenceThreshold());

        return;
    }
}