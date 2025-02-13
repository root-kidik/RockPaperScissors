#include <QApplication>

#include <infrastructure/util/Constant.hpp>
#include <infrastructure/widget/MainMenu.hpp>
#include <infrastructure/widget/Manager.hpp>

namespace rps::infrastructure::widget
{

MainMenu::MainMenu(widget::Manager& widget_manager) :
m_widget_manager{widget_manager},
m_start_game_button{"Начать игру"},
m_quit_button{"Выйти"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_start_game_button.setStyleSheet(util::kDefaultGreenButtonStyle);
    m_quit_button.setStyleSheet(util::kDefaultRedButtonStyle);

    m_start_game_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_quit_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_start_game_button.setMaximumSize(util::kMaxButtonSize);
    m_quit_button.setMaximumSize(util::kMaxButtonSize);

    connect(&m_start_game_button,
            &QPushButton::pressed,
            [this]() { m_widget_manager.activate_mode(domain::entity::Mode::Registration); });
    connect(&m_quit_button, &QPushButton::pressed, [this]() { QApplication::quit(); });

    m_layout.addWidget(&m_start_game_button);
    m_layout.addWidget(&m_quit_button);
}

} // namespace rps::infrastructure::widget
