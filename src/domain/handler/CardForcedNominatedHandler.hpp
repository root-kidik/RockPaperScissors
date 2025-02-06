#pragma once

#include <RockPaperScissorsProtocol/interface/CardForcedNominatedHandlerBase.hpp>

namespace rps::domain::handler
{

class CardForcedNominatedHandler : public protocol::interface::CardForcedNominatedHandlerBase
{
public:
    protocol::entity::client::StatusResponse handle(protocol::entity::client::CardForcedNominatedRequest&& request,
                                                    const std::shared_ptr<protocol::interface::Connection>& connection) override;
};

} // namespace rps::domain::handler
