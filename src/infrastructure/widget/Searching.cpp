#include <infrastructure/widget/Searching.hpp>

#include <infrastructure/util/Constant.hpp>

#include <domain/interface/usecase/Searching.hpp>

#include <domain/model/Room.hpp>

namespace rps::infrastructure::widget
{

Searching::Searching(domain::interface::usecase::Searching& usecase, domain::model::Room& room) :
m_usecase{usecase},
m_room{room},
m_create_room_button{"Создать"},
m_connect_to_room_button{"Присоединиться"}
{
    setLayout(&m_layout);

    m_layout.setAlignment(Qt::AlignCenter);

    m_room_name_input.setPlaceholderText("Введите имя игровой комнаты");

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
            [this]()
            {
                auto name = m_room_name_input.text().toStdString();
                m_usecase.create_room(name);
                m_room.name.set_value(std::move(name));
            });

    connect(&m_connect_to_room_button,
            &QPushButton::pressed,
            [this]()
            {
                auto name = m_room_name_input.text().toStdString();
                m_usecase.connect_to_room(m_room_name_input.text().toStdString());
                m_room.name.set_value(std::move(name));
            });

    m_layout.addWidget(&m_room_name_input);
    m_layout.addWidget(&m_create_room_button);
    m_layout.addWidget(&m_connect_to_room_button);
}

} // namespace rps::infrastructure::widget
