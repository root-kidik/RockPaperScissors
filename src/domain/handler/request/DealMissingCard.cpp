#include <algorithm>

#include <domain/model/Room.hpp>

#include <domain/handler/request/DealMissingCard.hpp>

namespace rps::domain::handler::request
{

DealMissingCard::DealMissingCard(model::Room& room) : m_room{room}
{
}

DealMissingCard::Response DealMissingCard::handle(Request&&                                               request,
                                                  const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    auto& player_hand_cards = m_room.player_hand_of_cards_model.cards;

    auto it = std::find_if(player_hand_cards.begin(),
                           player_hand_cards.end(),
                           [type = request.card](const model::HandOfCards::Card& card)
                           { return card.is_raised.get_value(); });

    assert(it != player_hand_cards.end() && "raised card must exist");

    it->is_raised.set_value(false);
    it->type.set_value(request.card);

    return response;
}

} // namespace rps::domain::handler::request
