#pragma once

#include <domain/model/Room.hpp>

#include <RockPaperScissorsProtocol/interface/client/handler/request/NewPlayerAdded.hpp>

namespace rps::domain::handler::request
{

class NewPlayerAdded : public protocol::interface::client::handler::request::NewPlayerAdded
{
public:
    NewPlayerAdded(model::Room& room);

    Response handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection) override;

private:
    model::Room& m_room;
};

} // namespace rps::domain::handler::request
