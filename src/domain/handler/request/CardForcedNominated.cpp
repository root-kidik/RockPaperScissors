#include <algorithm>

#include <domain/model/Room.hpp>

#include <domain/handler/request/CardForcedNominated.hpp>

namespace rps::domain::handler::request
{

CardForcedNominated::CardForcedNominated(model::Room& room) : m_room{room}
{
}

CardForcedNominated::Response CardForcedNominated::handle(Request&& request,
                                                          const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    auto& player_hand_cards = m_room.player_hand_of_cards_model.cards;

    auto it = std::find_if(player_hand_cards.begin(),
                           player_hand_cards.end(),
                           [type = request.card](const model::HandOfCards::Card& card)
                           { return card.type.get_value() == type && !card.is_raised.get_value(); });

    assert(it != player_hand_cards.end() && "force nominated card must exist");

    it->is_force_nominated.set_value(true);

    return response;
}

} // namespace rps::domain::handler::request
