#include <domain/entity/User.hpp>
#include <domain/handler/response/Register.hpp>
#include <domain/interface/ModeManager.hpp>

namespace rps::domain::handler::response
{

Register::Register(domain::entity::User& user, interface::ModeManager& mode_manager) :
m_user{user},
m_mode_manager{mode_manager}
{
}

void Register::handle(Response&& response)
{
    if (response.user_uuid.empty())
        return;

    m_user.uuid = std::move(response.user_uuid);
    m_mode_manager.activate_mode(entity::Mode::RoomSearch);
}

} // namespace rps::domain::handler::response
