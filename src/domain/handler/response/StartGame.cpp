#include <domain/handler/response/StartGame.hpp>
#include <domain/model/Room.hpp>

namespace rps::domain::handler::response
{

StartGame::StartGame(model::Room& room_model) : m_room_model{room_model}
{
}

void StartGame::handle(Response&& response)
{
    assert(response.is_ok && "Something went wrong");

    // TODO:
}

} // namespace rps::domain::handler::response
