#include <QtPlugin>

#ifdef __linux__
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#elif _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

#include <QApplication>

#include <infrastructure/widget/MainMenuWidget.hpp>
#include <infrastructure/client/Client.hpp>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    rps::infrastructure::widget::MainMenuWidget main_menu;
    main_menu.show();

    rps::infrastructure::client::Client client;

    return app.exec();
}
