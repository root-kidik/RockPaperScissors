#include <RockPaperScissorsProtocol/entity/MessageSender.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/NominateCard.hpp>
#include <RockPaperScissorsProtocol/entity/server/request/StartGame.hpp>

#include <domain/entity/User.hpp>

#include <domain/model/Room.hpp>

#include <domain/util/Util.hpp>

namespace rps::domain::model
{

Room::Room(protocol::entity::MessageSender&                        message_sender,
           domain::entity::User&                                   user,
           const std::shared_ptr<protocol::interface::Connection>& connection) :
players{[this](const std::string& nickname, std::size_t idx)
        {
            if (!m_has_north)
            {
                m_has_north = true;
                util::generate_full_backface_deck(north_hand_of_cards_model);
                return true;
            }
            else if (!m_has_west)
            {
                m_has_west = true;
                util::generate_full_backface_deck(west_hand_of_cards_model);
                return true;
            }
            else if (!m_has_east)
            {
                m_has_east = true;
                util::generate_full_backface_deck(east_hand_of_cards_model);
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

            assert(card.type != protocol::entity::Card::Backface && "Card::Backface can not be nominated");
            assert(!card.is_force_nominated && "Card already force nominated");

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

            util::generate_full_backface_deck(player_hand_of_cards_model);

            play_table_hand_of_cards_model.is_locked.set_value(false);
            play_table_hand_of_cards_model.is_backface_hidden.set_value(true);
            util::generate_full_backface_deck(play_table_hand_of_cards_model);
            play_table_hand_of_cards_model.is_locked.set_value(true);
        });
}

} // namespace rps::domain::model
