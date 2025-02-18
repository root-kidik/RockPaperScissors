#pragma once

#include <memory>
#include <string>

namespace rps
{

namespace protocol
{

namespace entity
{
class MessageSender;
} // namespace entity

namespace interface
{
class Connection;
} // namespace interface

} // namespace protocol

namespace domain::entity
{
struct User;
} // namespace domain::entity

} // namespace rps

namespace rps::domain::usecase
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

} // namespace rps::domain::usecase
