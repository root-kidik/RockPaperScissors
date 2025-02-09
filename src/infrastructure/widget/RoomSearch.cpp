#include <infrastructure/widget/RoomSearch.hpp>

namespace rps::infrastructure::widget
{

RoomSearch::RoomSearch(protocol::entity::MessageSender&                        message_sender,
                       domain::entity::User&                                   user,
                       const std::shared_ptr<protocol::interface::Connection>& connection) :
m_model{message_sender, user, connection},
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
