#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/request/GameResult.hpp>

namespace rps::domain
{
namespace model
{
struct Room;
}

namespace interface
{
class ModeManager;
}
} // namespace rps::domain

namespace rps::domain::handler::request
{

class GameResult final : public protocol::interface::client::handler::request::GameResult
{
public:
    GameResult(interface::ModeManager& mode_manager, model::Room& room_model);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    interface::ModeManager& m_mode_manager;
    model::Room& m_room_model;
};

} // namespace rps::domain::handler::request
