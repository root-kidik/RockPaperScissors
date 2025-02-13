#include <infrastructure/util/Constant.hpp>
#include <infrastructure/widget/Searching.hpp>

namespace rps::infrastructure::widget
{

Searching::Searching(domain::model::Searching& model) :
m_model{model},
m_room_name_input{"Введите имя комнаты"},
m_create_room_button{"Создать"},
m_connect_to_room_button{"Присоединиться"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_room_name_input.setStyleSheet(util::kDefaultLineEditStyle);
    m_create_room_button.setStyleSheet(util::kDefaultGreenButtonStyle);
    m_connect_to_room_button.setStyleSheet(util::kDefaultGreenButtonStyle);

    m_room_name_input.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_create_room_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_connect_to_room_button.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_room_name_input.setMaximumSize(util::kMaxButtonSize);
    m_create_room_button.setMaximumSize(util::kMaxButtonSize);
    m_connect_to_room_button.setMaximumSize(util::kMaxButtonSize);

    connect(&m_create_room_button,
            &QPushButton::pressed,
            [this]() { m_model.create_room(m_room_name_input.text().toStdString()); });

    connect(&m_connect_to_room_button,
            &QPushButton::pressed,
            [this]() { m_model.connect_to_room(m_room_name_input.text().toStdString()); });

    m_layout.addWidget(&m_room_name_input);
    m_layout.addWidget(&m_create_room_button);
    m_layout.addWidget(&m_connect_to_room_button);
}

} // namespace rps::infrastructure::widget
