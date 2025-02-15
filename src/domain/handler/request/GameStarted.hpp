#pragma once

#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/interface/client/handler/request/GameStarted.hpp>

namespace rps::domain::handler::request
{

class GameStarted : public protocol::interface::client::handler::request::GameStarted
{
public:
    GameStarted(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
