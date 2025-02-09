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

    m_room.add_new_player(std::move(request.user_nickname));

    return response;
}

} // namespace rps::domain::handler::request
