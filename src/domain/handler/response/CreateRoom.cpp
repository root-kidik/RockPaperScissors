#include <domain/handler/response/CreateRoom.hpp>
#include <domain/interface/ModeManager.hpp>

namespace rps::domain::handler::response
{

CreateRoom::CreateRoom(interface::ModeManager& mode_manager) : m_mode_manager{mode_manager}
{
}

void CreateRoom::handle(Response&& response)
{
    if (response.is_ok)
        return;

    // TODO: handle not ok status
}

} // namespace rps::domain::handler::response
