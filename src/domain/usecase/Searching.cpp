#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/ConnectToRoom.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/CreateRoom.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

#include <domain/entity/User.hpp>

#include <domain/model/Room.hpp>

#include <domain/usecase/Searching.hpp>

namespace rps::domain::usecase
{

Searching::Searching(protocol::entity::MessageSender&                        message_sender,
                     domain::entity::User&                                   user,
                     const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection}
{
}

void Searching::create_room(std::string room_name)
{
    protocol::entity::server::request::CreateRoom request;
    request.room_name = room_name;
    request.user_uuid = m_user.uuid;

    m_message_sender.send(std::move(request), m_connection);

    connect_to_room(std::move(room_name));
}

void Searching::connect_to_room(std::string room_name)
{
    protocol::entity::server::request::ConnectToRoom request;
    request.room_name = std::move(room_name);
    request.user_uuid = m_user.uuid;

    m_message_sender.send(std::move(request), m_connection);
}

} // namespace rps::domain::usecase
