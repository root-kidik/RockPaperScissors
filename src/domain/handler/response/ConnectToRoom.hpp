#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/ConnectToRoom.hpp>

namespace rps::domain::interface
{
class ModeManager;
} // namespace rps::domain::interface

namespace rps::domain::handler::response
{

class ConnectToRoom final : public protocol::interface::client::handler::response::ConnectToRoom
{
public:
    ConnectToRoom(interface::ModeManager& mode_manager);

    void handle(Response&& response) override;

private:
    interface::ModeManager& m_mode_manager;
};

} // namespace rps::domain::handler::response
