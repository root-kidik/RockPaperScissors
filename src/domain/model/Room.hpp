#pragma once

#include <functional>
#include <vector>

#include <domain/entity/User.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::model
{

class Room
{
public:
    Room(protocol::entity::MessageSender&                        message_sender,
         domain::entity::User&                                   user,
         const std::shared_ptr<protocol::interface::Connection>& connection);

    void subsribe_on_new_player_addition(std::function<void(std::string&&)> callback);
    void add_new_player(std::string&& player_nickname);

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
    std::function<void(std::string&&)>                      m_on_new_player_added;

    std::vector<std::string> m_players;
};

} // namespace rps::domain::model
