#include "Screenshot.hpp"


namespace scl
{
    QPixmap screenshot(QScreen* a_screen)
    {
        QScreen* screen;
        
        if (a_screen == nullptr)
        {
            screen = QGuiApplication::primaryScreen();
        }
        else
        {
            screen = a_screen;
        }

        if (screen == nullptr)
        {
            throw std::runtime_error{"No screen found"};
        }

        return screen->grabWindow(0);
    }
}