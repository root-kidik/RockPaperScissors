#pragma once

#include <array>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

#include <domain/util/Property.hpp>

namespace rps::domain::model
{

struct HandOfCards
{
    struct Card
    {
        protocol::entity::Card type{protocol::entity::Card::Backface};
        bool                   is_nominated{};
    };

    HandOfCards();

    util::Property<bool>                                                   is_locked;
    util::Property<std::array<Card, protocol::entity::kMaxCardsPerPlayer>> cards;
};

} // namespace rps::domain::model
