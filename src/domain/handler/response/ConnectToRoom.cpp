#include <domain/handler/response/ConnectToRoom.hpp>
#include <domain/interface/ModeManager.hpp>
#include <domain/model/Room.hpp>

namespace rps::domain::handler::response
{

ConnectToRoom::ConnectToRoom(interface::ModeManager& mode_manager, model::Room& model) :
m_mode_manager{mode_manager},
m_model{model}
{
}

void ConnectToRoom::handle(Response&& response)
{
    if (!response.is_ok)
        return;

    for (auto&& nickname : response.existed_players)
        if (!nickname.empty())
            m_model.players.add_value(std::move(nickname));

    m_model.is_connected_to_room.set_value(true);
    m_mode_manager.activate_mode(entity::Mode::Room);
}

} // namespace rps::domain::handler::response
