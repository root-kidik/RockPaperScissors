#include <domain/handler/request/GameStarted.hpp>

namespace rps::domain::handler::request
{

GameStarted::GameStarted(model::Room& room) : m_room{room}
{
}

GameStarted::Response GameStarted::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    m_room.set_user_cards(request.cards);

    return response;
}

} // namespace rps::domain::handler::request
