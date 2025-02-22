#include <algorithm>

#include <domain/model/Room.hpp>

#include <domain/handler/request/RoundInfo.hpp>

#ifndef NDEBUG
#include <iostream>
#endif

namespace rps::domain::handler::request
{

RoundInfo::RoundInfo(model::Room& room) : m_room{room}
{
}

RoundInfo::Response RoundInfo::handle(Request&& request, const std::shared_ptr<protocol::interface::Connection>& connection)
{
    Response response;
    response.is_ok = true;

    auto& play_table_cards = m_room.play_table_hand_of_cards_model.cards;

    assert(play_table_cards.size() == request.raised_cards.size() && "size must be equal");

    for (std::size_t i = 0; i < play_table_cards.size(); i++)
    {
        auto& card = play_table_cards[i];
        card.type.set_value(request.raised_cards[i]);
        card.raise_status.set_value(model::HandOfCards::Card::RaiseStatus::NotChoosen);
    }

    auto& player_hand_cards = m_room.player_hand_of_cards_model.cards;

    auto player_card_it = std::find_if(player_hand_cards.begin(),
                                       player_hand_cards.end(),
                                       [](const model::HandOfCards::Card& card)
                                       { return card.is_raised_in_current_round.get_value(); });

    assert(player_card_it != player_hand_cards.end() && "raised card must be exist");

    auto raised_card_type = player_card_it->type.get_value();

    auto play_table_card_it = std::find_if(play_table_cards.begin(),
                                           play_table_cards.end(),
                                           [raised_card_type](const model::HandOfCards::Card& card)
                                           { return card.type.get_value() == raised_card_type; });

    assert(play_table_card_it != play_table_cards.end() && "such card must be exist on table");

    play_table_card_it->raise_status.set_value(
        request.is_winned ? model::HandOfCards::Card::RaiseStatus::Win : model::HandOfCards::Card::RaiseStatus::Loss);

#ifndef NDEBUG
    if (request.is_winned)
        std::cout << "You winned!\n";
    else
        std::cout << "You losed!\n";
#endif

    return response;
}

} // namespace rps::domain::handler::request
