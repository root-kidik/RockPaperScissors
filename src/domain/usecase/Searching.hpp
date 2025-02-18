#pragma once

#include <memory>

#include <domain/interface/usecase/Searching.hpp>

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

class Searching final : public interface::usecase::Searching
{
public:
    Searching(protocol::entity::MessageSender&                        message_sender,
              domain::entity::User&                                   user,
              const std::shared_ptr<protocol::interface::Connection>& connection);

    void create_room(std::string room_name) override;
    void connect_to_room(std::string room_name) override;

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
};

} // namespace rps::domain::usecase
