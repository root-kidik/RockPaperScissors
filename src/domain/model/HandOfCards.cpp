#include <domain/model/HandOfCards.hpp>

namespace rps::domain::model
{

HandOfCards::HandOfCards() :
is_locked{true},
cards{nullptr, [this](const Card& card) { return !is_locked.get_value(); }}
{
}

} // namespace rps::domain::model
