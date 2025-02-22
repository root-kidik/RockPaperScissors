#include <algorithm>

#include <domain/model/Room.hpp>

#include <domain/handler/request/NewPlayerAdded.hpp>

namespace rps::domain::handler::request
{

NewPlayerAdded::NewPlayerAdded(model::Room& room) : m_room{room}
{
}

NewPlayerAdded::Response NewPlayerAdded::handle(Request&&                                               request,
                                                const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    auto& players = m_room.players;

    auto it = std::find_if(players.begin(),
                           players.end(),
                           [](const util::Property<std::string>& nickname) { return nickname.get_value().empty(); });

    assert(it != players.end() && "added too many players");

    it->set_value(std::move(request.user_nickname));

    return response;
}

} // namespace rps::domain::handler::request
