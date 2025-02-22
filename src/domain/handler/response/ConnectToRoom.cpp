#include <algorithm>

#include <domain/interface/ModeManager.hpp>

#include <domain/model/Room.hpp>

#include <domain/handler/response/ConnectToRoom.hpp>

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

    auto& players = m_model.players;

    for (auto&& nickname : response.existed_players)
        if (!nickname.empty())
        {
            auto it = std::find_if(players.begin(),
                                   players.end(),
                                   [](const util::Property<std::string>& nickname) { return nickname.get_value().empty(); });

            assert(it != players.end() && "added too many players");

            it->set_value(std::move(nickname));
        }

    m_model.is_connected_to_room.set_value(true);
    m_mode_manager.activate_mode(entity::Mode::Room);
}

} // namespace rps::domain::handler::response
