#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/StartGame.hpp>

namespace rps::domain::model
{
class Room;
} // namespace rps::domain::model

namespace rps::domain::handler::response
{

class StartGame final : public protocol::interface::client::handler::response::StartGame
{
public:
    StartGame(model::Room& room_model);

    void handle(Response&& response) override;

private:
    model::Room& m_room_model;
};

} // namespace rps::domain::handler::response
