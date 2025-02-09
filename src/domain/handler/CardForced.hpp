#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/CardForcedNominated.hpp>

namespace rps::domain::handler
{

class CardForced : public protocol::interface::client::handler::CardForcedNominated
{
public:
    protocol::entity::client::response::Status handle(protocol::entity::client::request::CardForcedNominated&& request,
                                                      const std::shared_ptr<protocol::interface::Connection>& connection) override;
};

} // namespace rps::domain::handler
