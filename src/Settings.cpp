#include "Settings.hpp"



namespace scl
{
    const QString Settings::window_geometry_alias = "geometry";
    
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
    
    void Settings::load()
    {
        const QByteArray geometry = value(window_geometry_alias, QByteArray()).toByteArray();

        if (!geometry.isEmpty())
        {
            main_window->restoreGeometry(geometry);
        }

        return;
    }
    
    void Settings::save()
    {
        setValue(window_geometry_alias, main_window->saveGeometry());
        return;
    }
}