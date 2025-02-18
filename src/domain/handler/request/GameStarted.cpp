#include <domain/model/HandOfCards.hpp>
#include <domain/model/Room.hpp>

#include <domain/handler/request/GameStarted.hpp>

namespace rps::domain::handler::request
{

GameStarted::GameStarted(model::Room& room_model) : m_room_model{room_model}
{
}

GameStarted::Response GameStarted::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    m_room_model.is_game_started.set_value(true);

    for (std::size_t i = 0; i < request.cards.size(); i++)
        m_room_model.player_hand_of_cards_model.cards.update_value({request.cards[i], false}, i);

    return response;
}

} // namespace rps::domain::handler::request
