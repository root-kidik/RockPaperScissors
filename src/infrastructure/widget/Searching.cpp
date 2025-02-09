#include <infrastructure/widget/Searching.hpp>

namespace rps::infrastructure::widget
{

Searching::Searching(domain::model::Searching& model) :
m_model{model},
m_room_name_input{"Введите имя комнаты"},
m_create_room_button{"Создать"}
{
    setLayout(&m_layout);

    connect(&m_create_room_button,
            &QPushButton::pressed,
            [this]() { m_model.create_room(m_room_name_input.text().toStdString()); });

    m_layout.addWidget(&m_room_name_input);
    m_layout.addWidget(&m_create_room_button);
}

} // namespace rps::infrastructure::widget
