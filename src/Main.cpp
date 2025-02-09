#include <QtPlugin>

#ifdef __linux__
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#elif _WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

#include <infrastructure/RockPaperScissors.hpp>

int main(int argc, char* argv[])
{
    using namespace rps::infrastructure;

    RockPaperScissors app{argc, argv};

    return app.run();
}
