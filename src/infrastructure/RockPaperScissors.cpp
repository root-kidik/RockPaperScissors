#include <infrastructure/RockPaperScissors.hpp>
#include <infrastructure/widget/MainMenu.hpp>
#include <infrastructure/widget/Registration.hpp>

namespace rps::infrastructure
{

RockPaperScissors::RockPaperScissors(int argc, char* argv[]) : m_app{argc, argv}
{
    m_widget_manager.register_widget<widget::MainMenu>(widget::Type::MainMenu, m_widget_manager);
    m_widget_manager.register_widget<widget::Registration>(widget::Type::Registration);

    m_widget_manager.activate_widget(widget::Type::MainMenu);
}

int RockPaperScissors::run()
{
    return m_app.exec();
}

} // namespace rps::infrastructure
