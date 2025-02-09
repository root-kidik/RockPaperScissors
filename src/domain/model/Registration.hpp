#pragma once

#include <domain/entity/User.hpp>

#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/interface/Connection.hpp>

namespace rps::domain::model
{

class Registration
{
public:
    Registration(protocol::entity::MessageSender&                        message_sender,
                 domain::entity::User&                                   user,
                 const std::shared_ptr<protocol::interface::Connection>& connection);

    void registrate(std::string&& nickname);

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
};

} // namespace rps::domain::model
