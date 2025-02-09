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

} // namespace rps::domain::model
