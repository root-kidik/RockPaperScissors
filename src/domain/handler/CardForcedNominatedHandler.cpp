#include <domain/handler/CardForcedNominatedHandler.hpp>

namespace rps::domain::handler
{

protocol::entity::client::StatusResponse CardForcedNominatedHandler::handle(
    protocol::entity::client::CardForcedNominatedRequest&&  request,
    const std::shared_ptr<protocol::interface::Connection>& connection)
{
    return protocol::entity::client::StatusResponse();
}

} // namespace rps::domain::handler
