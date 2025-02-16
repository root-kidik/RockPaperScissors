#include <domain/handler/request/CardRaised.hpp>
#include <domain/model/Room.hpp>

namespace rps::domain::handler::request
{

CardRaised::CardRaised(model::Room& room) : m_room{room}
{
}

CardRaised::Response CardRaised::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    return response;
}

} // namespace rps::domain::handler::request
