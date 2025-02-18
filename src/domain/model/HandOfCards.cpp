#include <domain/model/HandOfCards.hpp>

namespace rps::domain::model
{

HandOfCards::HandOfCards() :
is_locked{true},
cards{
#ifndef NDEBUG
    [](const Card& card, std::size_t idx)
    {
        assert(idx < protocol::entity::kMaxCardsPerPlayer && "added too many cards");
        return true;
    },
#else
    nullptr,
#endif
    [this](const Card& card, std::size_t idx) { return !is_locked.get_value(); }}
{
}

} // namespace rps::domain::model
