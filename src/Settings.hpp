#pragma once

#include <QByteArray>
#include <QMainWindow>
#include <QSettings>
#include <QStandardPaths>

#include "ForwardDeclarations.hpp"

namespace scl
{
    class Settings : public QSettings
    {
        Q_OBJECT

        public:
            Settings(QMainWindow* a_parent = nullptr);
            ~Settings();

            void emitState();

            static QString getGeometryAlias();
            static QString getAutoAcceptAlias();
            static QString getShowAllAlias();
            static QString getConfidenceThresholdAlias();
            static QString getSaveLocationAlias();

            bool getAutoAccept() const;
            bool getShowAll() const;
            int getConfidenceThreshold() const;
            const QString& getSaveLocation() const;

        public slots:
            void setAutoAccept(bool a_state);
            void setShowAll(bool a_state);
            void setConfidenceThreshold(int a_threshold);
            void setSaveLocation(const QString& a_location);
        
        signals:
            void autoAcceptChanged(bool a_state);
            void showAllChanged(bool a_state);
            void confidenceThresholdChanged(int a_threshold);
            void saveLocationChanged(const QString& a_location);
        
        private:
            void load();
            void save();

            QMainWindow* main_window;

            bool auto_accept;
            bool show_all;
            int confidence_threshold;
            QString save_location;
    };
}