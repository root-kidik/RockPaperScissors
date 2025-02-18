#pragma once

#include <memory>

#include <domain/interface/usecase/StartGame.hpp>

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

namespace domain
{

namespace entity
{
struct User;
} // namespace entity

namespace model
{
struct Room;
} // namespace model

} // namespace domain

} // namespace rps

namespace rps::domain::usecase
{

class StartGame final : public interface::usecase::StartGame
{
public:
    StartGame(protocol::entity::MessageSender&                        message_sender,
              domain::entity::User&                                   user,
              const std::shared_ptr<protocol::interface::Connection>& connection,
              model::Room&                                            room_model);

    void start_game() override;

private:
    protocol::entity::MessageSender&                        m_message_sender;
    domain::entity::User&                                   m_user;
    const std::shared_ptr<protocol::interface::Connection>& m_connection;
    model::Room&                                            m_room_model;
};

} // namespace rps::domain::usecase
