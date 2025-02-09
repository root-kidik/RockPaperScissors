#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/CardForcedNominated.hpp>

namespace rps::domain::handler
{

class CardForced : public protocol::interface::client::handler::CardForcedNominated
{
public:
    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;
};

} // namespace rps::domain::handler
