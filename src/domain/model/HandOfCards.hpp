#pragma once

#include <array>

#include <domain/util/Property.hpp>

#include <RockPaperScissorsProtocol/entity/Card.hpp>

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
