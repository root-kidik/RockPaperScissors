#include <domain/handler/response/CreateRoom.hpp>
#include <domain/interface/ModeManager.hpp>
#include <domain/model/Room.hpp>

namespace rps::domain::handler::response
{

CreateRoom::CreateRoom(interface::ModeManager& mode_manager, model::Room& model) :
m_mode_manager{mode_manager},
m_model{model}
{
}

void CreateRoom::handle(Response&& response)
{
    if (!response.is_ok)
        return;

    m_model.create_room();
}

} // namespace rps::domain::handler::response
