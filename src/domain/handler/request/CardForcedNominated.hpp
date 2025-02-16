#pragma once

#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/interface/client/handler/request/CardForcedNominated.hpp>

namespace rps::domain::handler::request
{

class CardForcedNominated : public protocol::interface::client::handler::request::CardForcedNominated
{
public:
    CardForcedNominated(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
