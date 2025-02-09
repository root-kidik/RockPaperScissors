#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/CreateRoom.hpp>

namespace rps::domain::interface
{
class ModeManager;
} // namespace rps::domain::interface

namespace rps::domain::handler::response
{

class CreateRoom final : public protocol::interface::client::handler::response::CreateRoom
{
public:
    CreateRoom(interface::ModeManager& mode_manager);

    void handle(Response&& response) override;

private:
    interface::ModeManager& m_mode_manager;
};

} // namespace rps::domain::handler::response
