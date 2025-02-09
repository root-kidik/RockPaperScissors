#include <domain/handler/CardForced.hpp>

namespace rps::domain::handler
{

protocol::entity::client::response::Status CardForced::handle(
    protocol::entity::client::request::CardForcedNominated&& request,
    const std::shared_ptr<protocol::interface::Connection>&  connection)
{
    return protocol::entity::client::response::Status();
}

} // namespace rps::domain::handler
