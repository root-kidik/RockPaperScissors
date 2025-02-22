#include <algorithm>

#include <domain/model/Room.hpp>

#include <domain/handler/request/CardRaised.hpp>

namespace rps::domain::handler::request
{

CardRaised::CardRaised(model::Room& room) : m_room{room}
{
}

CardRaised::Response CardRaised::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    auto& player_hand_cards = m_room.player_hand_of_cards_model.cards;

    {
        auto it = std::find_if(player_hand_cards.begin(),
                               player_hand_cards.end(),
                               [](const model::HandOfCards::Card& card)
                               { return card.is_raised_in_current_round.get_value(); });

        if (it != player_hand_cards.end())
            it->is_raised_in_current_round.set_value(false);
    }

    {
        auto it = std::find_if(player_hand_cards.begin(),
                               player_hand_cards.end(),
                               [type = request.card](const model::HandOfCards::Card& card)
                               { return card.is_nominated.get_value() || card.is_force_nominated.get_value(); });

        assert(it != player_hand_cards.end() && "nominated or force nominated card must exist");

        it->is_nominated.set_value(false);
        it->is_force_nominated.set_value(false);
        it->is_raised.set_value(true);
        it->is_raised_in_current_round.set_value(true);
    }

    return response;
}

} // namespace rps::domain::handler::request
