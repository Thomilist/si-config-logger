#pragma once

#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>

#include "ForwardDeclarations.hpp"

namespace scl
{
    QPixmap screenshot(QScreen* a_screen = nullptr);
}