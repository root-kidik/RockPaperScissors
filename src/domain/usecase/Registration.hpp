#pragma once

#include <memory>
#include <string>

#include <domain/interface/usecase/Registration.hpp>

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

class Registration final : public interface::usecase::Registration
{
public:
    Registration(protocol::entity::MessageSender&                        message_sender,
                 domain::entity::User&                                   user,
                 const std::shared_ptr<protocol::interface::Connection>& connection);

    void registrate(std::string&& nickname) override;

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
};

} // namespace rps::domain::usecase
