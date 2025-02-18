#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/NominateCard.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/StartGame.hpp>

#include <domain/entity/User.hpp>

#include <domain/model/Room.hpp>

namespace rps::domain::model
{

Room::Room(protocol::entity::MessageSender&                        message_sender,
           domain::entity::User&                                   user,
           const std::shared_ptr<protocol::interface::Connection>& connection) :
players{[this](const std::string& nickname)
        {
            if (!m_has_north)
            {
                m_has_north = true;
                generate_full_backface_deck(north_hand_of_cards_model);
                return true;
            }
            else if (!m_has_west)
            {
                m_has_west = true;
                generate_full_backface_deck(west_hand_of_cards_model);
                return true;
            }
            else if (!m_has_east)
            {
                m_has_east = true;
                generate_full_backface_deck(east_hand_of_cards_model);
                return true;
            }

            assert(false && "too many players added");
            return false;
        }},
m_message_sender{message_sender},
m_user{user},
m_connection{connection},
is_game_started{false},
is_room_created{false},
m_has_north{},
m_has_west{},
m_has_east{}
{
    player_hand_of_cards_model.cards.subscribe_on_update(
        [this](const domain::model::HandOfCards::Card& card, std::size_t idx)
        {
            if (!card.is_nominated)
                return;

            protocol::entity::server::request::NominateCard request;
            request.room_name = name.get_value();
            request.user_uuid = m_user.uuid;
            request.card      = card.type;

            m_message_sender.send(std::move(request), m_connection);
        });

    is_game_started.subscribe(
        [this](const bool& is_game_started) { player_hand_of_cards_model.is_locked.set_value(!is_game_started); });

    is_connected_to_room.subscribe(
        [this](const bool& is_connected_to_room)
        {
            if (!is_connected_to_room)
                return;

            generate_full_backface_deck(player_hand_of_cards_model);
        });
}

void Room::generate_full_backface_deck(domain::model::HandOfCards& hand_of_cards_model)
{
    using namespace rps::protocol::entity;

    for (std::uint8_t i = 0; i < protocol::entity::kMaxCardsPerPlayer; i++)
        hand_of_cards_model.cards.set_value({Card::Backface, false}, i);
}

} // namespace rps::domain::model
