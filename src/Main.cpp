#include <QtPlugin>

#ifdef __linux__
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#elif _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

#include <QApplication>
#include <QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QPushButton  button("Hello, Qt6!");
    button.resize(200, 100);
    button.show();
    return app.exec();
}
