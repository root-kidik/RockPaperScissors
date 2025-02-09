#pragma once

#include <RockPaperScissorsProtocol/interface/client/handler/response/Register.hpp>

namespace rps::domain
{

namespace interface
{
class ModeManager;
} // namespace interface

namespace entity
{
struct User;
} // namespace entity

} // namespace rps::domain

namespace rps::domain::handler::response
{

class Register final : public protocol::interface::client::handler::response::Register
{
public:
    Register(domain::entity::User& user, interface::ModeManager& mode_manager);

    void handle(Response&& response) override;

private:
    domain::entity::User&   m_user;
    interface::ModeManager& m_mode_manager;
};

} // namespace rps::domain::handler::response
