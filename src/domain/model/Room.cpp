#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/entity/server/request/NominateCard.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/StartGame.hpp>

namespace rps::domain::model
{

Room::Room(protocol::entity::MessageSender&                        message_sender,
           domain::entity::User&                                   user,
           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection},
is_game_started{false},
is_room_created{false}
{
}

void Room::start_game()
{
    protocol::entity::server::request::StartGame request;
    request.room_name = name.get_value();
    request.user_uuid = m_user.uuid;

    m_message_sender.send(std::move(request), m_connection);
}

void Room::nominate_card(protocol::entity::Card card)
{
    assert(is_game_started.get_value() && "Game must be started!");

    protocol::entity::server::request::NominateCard request;
    request.room_name = name.get_value();
    request.user_uuid = m_user.uuid;
    request.card      = card;

    m_message_sender.send(std::move(request), m_connection);
}

void Room::subscribe_on_force_nominating_card(std::function<void(protocol::entity::Card)> callback)
{
    assert(!m_on_card_force_nominated && "Subcriber already setted!");
    m_on_card_force_nominated = std::move(callback);
}

void Room::force_nominate_card(protocol::entity::Card card)
{
    assert(m_on_card_force_nominated && "Subscriber must be setted!");
    m_on_card_force_nominated(card);
}

} // namespace rps::domain::model
