#include <domain/handler/request/CardForced.hpp>

namespace rps::domain::handler
{

CardForced::Response CardForced::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    return Response();
}

} // namespace rps::domain::handler
