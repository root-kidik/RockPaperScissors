#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/CreateRoom.hpp>

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

namespace rps::domain::handler::response
{

class CreateRoom final : public protocol::interface::client::handler::response::CreateRoom
{
public:
    CreateRoom(interface::ModeManager& mode_manager, model::Room& model);

    void handle(Response&& response) override;

private:
    interface::ModeManager& m_mode_manager;
    model::Room&            m_model;
};

} // namespace rps::domain::handler::response
