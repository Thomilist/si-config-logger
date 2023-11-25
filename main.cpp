#include <QApplication>
#include <QCoreApplication>

#include "src/ForwardDeclarations.hpp"

#include "src/MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication application{argc, argv};

    QCoreApplication::setOrganizationName("Thomilist");
    QCoreApplication::setApplicationName("si-config-logger");

    scl::MainWindow main_window{};

    return application.exec();
}