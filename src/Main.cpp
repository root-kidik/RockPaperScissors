#include <QtPlugin>

#ifdef _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#else
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
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
