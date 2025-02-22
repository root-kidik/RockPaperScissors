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
        Card(const HandOfCards& hand);

        util::Property<protocol::entity::Card> type;

        util::Property<bool> is_nominated;
        util::Property<bool> is_raised;
        util::Property<bool> is_force_nominated;

        enum class RaiseStatus
        {
            NotChoosen,
            Win,
            Loss,
        };
        
        util::Property<bool> is_raised_in_current_round;
        util::Property<RaiseStatus> raise_status;
    };

    HandOfCards();

    util::Property<bool>                                   is_visible;
    util::Property<bool>                                   is_nominating_locked;
    util::Property<bool>                                   is_backface_hidden;
    std::array<Card, protocol::entity::kMaxCardsPerPlayer> cards;
};

} // namespace rps::domain::model
