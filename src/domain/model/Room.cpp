#include "Room.hpp"

#include <domain/model/Room.hpp>

namespace rps::domain::model
{

Room::Room(protocol::entity::MessageSender&                        message_sender,
           domain::entity::User&                                   user,
           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection}
{
}

void Room::subsribe_on_new_player_addition(std::function<void(std::string&&)> callback)
{
    assert(!m_on_new_player_added && "Subcriber already setted!");
    m_on_new_player_added = std::move(callback);
}

void Room::add_new_player(std::string&& player_nickname)
{
    m_players.push_back(player_nickname);

    assert(m_on_new_player_added && "Subcriber must be setted!");
    m_on_new_player_added(std::move(player_nickname));
}

} // namespace rps::domain::model
