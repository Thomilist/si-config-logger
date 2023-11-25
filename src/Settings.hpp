#pragma once

#include <QByteArray>
#include <QMainWindow>
#include <QSettings>

#include "ForwardDeclarations.hpp"

namespace scl
{
    class Settings : public QSettings
    {
        public:
            Settings(QMainWindow* a_parent = nullptr);
            ~Settings();
        
        private:
            void load();
            void save();

            static const QString window_geometry_alias;

            QMainWindow* main_window;
    };
}