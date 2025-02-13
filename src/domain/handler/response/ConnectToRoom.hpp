#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/ConnectToRoom.hpp>

namespace rps::domain
{
namespace model
{
class Room;
}

namespace interface
{
class ModeManager;
}
} // namespace rps::domain::interface

namespace rps::domain::handler::response
{

class ConnectToRoom final : public protocol::interface::client::handler::response::ConnectToRoom
{
public:
    ConnectToRoom(interface::ModeManager& mode_manager, model::Room& model);

    void handle(Response&& response) override;

private:
    interface::ModeManager& m_mode_manager;
    model::Room& m_model;
};

} // namespace rps::domain::handler::response
