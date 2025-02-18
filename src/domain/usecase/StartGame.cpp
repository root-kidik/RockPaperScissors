#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/StartGame.hpp>

#include <RockPaperScissorsProtocol/interface/Connection.hpp>

#include <domain/entity/User.hpp>

#include <domain/model/Room.hpp>

#include <domain/usecase/StartGame.hpp>

namespace rps::domain::usecase
{

StartGame::StartGame(protocol::entity::MessageSender&                        message_sender,
                     domain::entity::User&                                   user,
                     const std::shared_ptr<protocol::interface::Connection>& connection,
                     model::Room&                                            room_model) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection},
m_room_model{room_model}
{
}

void StartGame::start_game()
{
    assert(!m_room_model.is_game_started.get_value() && "game already started");

    protocol::entity::server::request::StartGame request;
    request.room_name = m_room_model.name.get_value();
    request.user_uuid = m_user.uuid;

    m_message_sender.send(std::move(request), m_connection);
}

} // namespace rps::domain::usecase
