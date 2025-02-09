#include <domain/model/RoomWait.hpp>
#include "RoomWait.hpp"

namespace rps::domain::model
{

RoomWait::RoomWait(protocol::entity::MessageSender&                        message_sender,
                   domain::entity::User&                                   user,
                   const std::shared_ptr<protocol::interface::Connection>& connection) :
m_message_sender{message_sender},
m_user{user},
m_connection{connection}
{
}

} // namespace rps::domain::model
