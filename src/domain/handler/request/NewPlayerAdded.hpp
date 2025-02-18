#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/request/NewPlayerAdded.hpp>

namespace rps::domain::model
{
struct Room;
} // namespace rps::domain::model

namespace rps::domain::handler::request
{

class NewPlayerAdded final : public protocol::interface::client::handler::request::NewPlayerAdded
{
public:
    NewPlayerAdded(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
