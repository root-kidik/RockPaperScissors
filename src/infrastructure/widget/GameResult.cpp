#include <QApplication>

#include <infrastructure/widget/GameResult.hpp>
#include <infrastructure/widget/Manager.hpp>

#include <infrastructure/util/Constant.hpp>

#include <domain/model/Room.hpp>

namespace rps::infrastructure::widget
{

GameResult::GameResult(domain::model::Room& room) : m_text{}, m_quit_button{"Выйти"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_quit_button.setStyleSheet(util::kDefaultRedButtonStyle);

    m_text.setAlignment(Qt::AlignCenter);

    m_text.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_quit_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_text.setMaximumSize(util::kMaxButtonSize);
    m_quit_button.setMaximumSize(util::kMaxButtonSize);

    connect(&m_quit_button, &QPushButton::pressed, [this]() { QApplication::quit(); });

    m_layout.addWidget(&m_text);
    m_layout.addWidget(&m_quit_button);

    room.is_winned.subscribe(
        [this](const bool& is_winned)
        {
            m_text.setText(is_winned ? "Вы победили" : "Вы проиграли");
            m_text.setStyleSheet(is_winned ? util::kDefaultGreenLabelStyle : util::kDefaultRedLabelStyle);
        });
}

} // namespace rps::infrastructure::widget
