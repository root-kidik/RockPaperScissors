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
players{std::string{""}, std::string{""}, std::string{""}},
is_game_started{false},
is_room_created{false}
{
    play_table_hand_of_cards_model.is_backface_hidden.set_value(true);

    players[0].subscribe([this](const std::string& nickname) { north_hand_of_cards_model.is_visible.set_value(true); });
    players[1].subscribe([this](const std::string& nickname) { west_hand_of_cards_model.is_visible.set_value(true); });
    players[2].subscribe([this](const std::string& nickname) { east_hand_of_cards_model.is_visible.set_value(true); });

    for (auto& card : player_hand_of_cards_model.cards)
        card.is_nominated.subscribe(
            [this, &card, &user, &connection, &message_sender](const bool& is_nominated)
            {
                if (!is_nominated)
                    return;

                protocol::entity::server::request::NominateCard request;
                request.room_name = name.get_value();
                request.user_uuid = user.uuid;
                request.card      = card.type.get_value();

                message_sender.send(std::move(request), connection);
            });

    is_game_started.subscribe([this](const bool& is_game_started)
                              { player_hand_of_cards_model.is_nominating_locked.set_value(!is_game_started); });

    is_connected_to_room.subscribe(
        [this](const bool& is_connected_to_room)
        {
            if (!is_connected_to_room)
                return;

            player_hand_of_cards_model.is_visible.set_value(true);
        });
}

} // namespace rps::domain::model
