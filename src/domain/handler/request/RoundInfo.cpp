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

    assert(m_room.play_table_hand_of_cards_model.cards.size() == request.raised_cards.size() && "size must be equal");

    m_room.play_table_hand_of_cards_model.is_locked.set_value(false);
    for (std::size_t i = 0; i < request.raised_cards.size(); i++)
        m_room.play_table_hand_of_cards_model.cards.update_value({request.raised_cards[i], false, false, false}, i);
    m_room.play_table_hand_of_cards_model.is_locked.set_value(true);

#ifndef NDEBUG
    if (request.is_winned)
        std::cout << "You winned!\n";
    else
        std::cout << "You losed!\n";
#endif

    return response;
}

} // namespace rps::domain::handler::request
