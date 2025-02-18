#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/request/GameStarted.hpp>

namespace rps::domain::model
{
class Room;
} // namespace rps::domain::model

namespace rps::domain::handler::request
{

class GameStarted final : public protocol::interface::client::handler::request::GameStarted
{
public:
    GameStarted(model::Room& room_model);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room_model;
};

} // namespace rps::domain::handler::request
