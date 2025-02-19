#pragma once

#include <domain/model/HandOfCards.hpp>

namespace rps::domain::util
{

void generate_full_backface_deck(model::HandOfCards& hand_of_cards_model)
{
    using namespace rps::protocol::entity;

    for (std::uint8_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        hand_of_cards_model.cards.add_value({Card::Backface, false, false, false});
}

} // namespace rps::domain::util
