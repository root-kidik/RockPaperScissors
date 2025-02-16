#include <domain/handler/request/CardForcedNominated.hpp>
#include <domain/model/Room.hpp>

namespace rps::domain::handler::request
{

CardForcedNominated::CardForcedNominated(model::Room& room) : m_room{room}
{
}

CardForcedNominated::Response CardForcedNominated::handle(Request&& request,
                                                          const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    m_room.force_nominate_card(request.card);

    return response;
}

} // namespace rps::domain::handler::request
