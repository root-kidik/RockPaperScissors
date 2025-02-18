#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/request/DealMissingCard.hpp>

namespace rps::domain::model
{
struct Room;
} // namespace rps::domain::model

namespace rps::domain::handler::request
{

class DealMissingCard final : public protocol::interface::client::handler::request::DealMissingCard
{
public:
    DealMissingCard(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
