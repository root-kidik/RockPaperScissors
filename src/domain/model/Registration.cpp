#include <domain/model/Registration.hpp>

#include <RockPaperScissorsProtocol/entity/server/request/Register.hpp>

namespace rps::domain::model
{

Registration::Registration(protocol::entity::MessageSender&                        message_sender,
                           domain::entity::User&                                   user,
                           const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection}
{
}

void Registration::registrate(std::string&& nickname)
{
    m_user.nickname = std::move(nickname);

    protocol::entity::server::request::Register request;
    request.user_nickname = m_user.nickname;

    m_message_sender.send(std::move(request), m_connection);
}

} // namespace rps::domain::model
