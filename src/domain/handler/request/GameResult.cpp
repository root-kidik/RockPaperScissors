#include <domain/interface/ModeManager.hpp>

#include <domain/model/Room.hpp>

#include <domain/handler/request/GameResult.hpp>

namespace rps::domain::handler::request
{

GameResult::GameResult(interface::ModeManager& mode_manager, model::Room& room_model) :
m_mode_manager{mode_manager},
m_room_model{room_model}
{
}

GameResult::Response GameResult::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    m_room_model.is_winned.set_value(request.is_winned);
    m_mode_manager.activate_mode(entity::Mode::GameResult);

    return response;
}

} // namespace rps::domain::handler::request
