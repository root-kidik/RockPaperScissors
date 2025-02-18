#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/request/RoundInfo.hpp>

namespace rps::domain::model
{
struct Room;
} // namespace rps::domain::model

namespace rps::domain::handler::request
{

class RoundInfo final : public protocol::interface::client::handler::request::RoundInfo
{
public:
    RoundInfo(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
