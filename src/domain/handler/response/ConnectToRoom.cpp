#include <domain/handler/response/ConnectToRoom.hpp>
#include <domain/interface/ModeManager.hpp>

namespace rps::domain::handler::response
{

ConnectToRoom::ConnectToRoom(interface::ModeManager& mode_manager) : m_mode_manager{mode_manager}
{
}

void ConnectToRoom::handle(Response&& response)
{
    if (!response.is_ok)
        return;

    m_mode_manager.activate_mode(entity::Mode::RoomWait);
}

} // namespace rps::domain::handler::response
