#pragma once

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
        bool                   is_raised{};
        bool                   is_force_nominated{};
    };

    HandOfCards();

    util::Property<bool>              is_locked;
    util::Property<bool>              is_backface_hidden;
    util::Property<std::vector<Card>> cards;
};

} // namespace rps::domain::model
