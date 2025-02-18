#include <domain/model/Room.hpp>

#include <domain/handler/request/RoundInfo.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

namespace rps::domain::handler::request
{

RoundInfo::RoundInfo(model::Room& room) : m_room{room}
{
}

RoundInfo::Response RoundInfo::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

#ifndef NDEBUG
    if (request.is_winned)
        std::cout << "You winned!\n";
    else
        std::cout << "You losed!\n";
#endif

    return response;
}

} // namespace rps::domain::handler::request
