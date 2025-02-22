#include <domain/model/HandOfCards.hpp>

namespace rps::domain::model
{

HandOfCards::Card::Card(const HandOfCards& hand) :
type{protocol::entity::Card::Backface},
is_nominated{false, [&hand](const bool& value) { return !hand.is_nominating_locked.get_value(); }},
is_raised{false},
is_force_nominated{false}
{
}

HandOfCards::HandOfCards() :
is_visible{false},
is_nominating_locked{true},
is_backface_hidden{false},
cards{Card{*this}, Card{*this}, Card{*this}, Card{*this}}
{
}

} // namespace rps::domain::model
