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

    auto& player_hand = m_room.player_hand_of_cards_model;

    for (std::size_t i = 0; i < player_hand.cards.size(); i++)
        if (const auto& value = player_hand.cards.get_value(i); value.type == request.card && value.is_nominated)
        {
            player_hand.cards.update_value({protocol::entity::Card::Backface, false}, i);
            break;
        }

    return response;
}

} // namespace rps::domain::handler::request
